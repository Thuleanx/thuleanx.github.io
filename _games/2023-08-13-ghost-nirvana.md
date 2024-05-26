---
layout: post
title: "Ghost Nirvana"
image: 
    thumbnail: /assets/images/gameCaptures/ghost-nirvana/many_enemies.gif
sidebar:
  - text: >-

        **Jam Project**<br>
        **Team:** 2 <br>
        **Tools:** Unity, FMOD<br>
        **Duration:** 6 weeks<br>
        **Platforms:** WebGL, Windows, Mac<br>

        <hr>
    image: /assets/images/gameCaptures/ghost-nirvana/title.png
  - text: >-
        - **Object pooling system** to handle hundreds of bullets running stably on WebGL

        - **Decoupled combat, UI, and upgrade system** with the MVVM pattern using scriptable objects

        - AI with Finite State Machine

        - FMOD Audio mixing and concurrency settings

        - **Online leaderboard system**

        - UI tweening

        <hr>
    links:
      - title: "Itch"
        url: "https://thuleanx.itch.io/ghost-nirvana"
        icon: "fab fa-gamepad fa"
      - title: "Github"
        url: "https://github.com/Thuleanx/GhostNirvana"
        icon: "fab fa-fw fa-github"
permalink: /games/ghost-nirvana/
no_masthead: true

gallery1:
  - image_path: /assets/images/gameCaptures/ghost-nirvana/candy.gif
  - image_path: /assets/images/gameCaptures/ghost-nirvana/levelup.gif

gallery2:
  - image_path: /assets/images/gameCaptures/ghost-nirvana/reload.gif
  - image_path: /assets/images/gameCaptures/ghost-nirvana/boss_appear.gif
  - image_path: /assets/images/gameCaptures/ghost-nirvana/saltsplosion.gif

gallery3: 
  - image_path: /assets/images/gameCaptures/ghost-nirvana/many_enemies.gif

---

Ghost Nirvana is a 3D roguelike bullet heaven I developed alongside [Allison Yeh](https://allisonkyeh.com/) for A Game By Its Cover 2023, a 6 week game jam.
You play as a part-time worker for a salt company whose job is exorcising ghosts haunting abandoned appliances.

{% include gallery id="gallery1" %}
{% include gallery id="gallery2" %}
{% include gallery id="gallery3" %}

----

# Code Snippets

Below are some code snippets of the game. The codebase is also released publicly on [github](https://github.com/Thuleanx/GhostNirvana).

## Object Pooling

I implemented an object pooling system in order to manage the huge number of 
bullets and other elements on screen.
Entities borrowed from the pool are automatically tagged with a `Bubble` component, 
which returns them to the queue upon disposal.
The pool persists and maintains its members even across scene transitions.

```csharp
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
using Base;

namespace Optimization {
    public partial class ObjectPoolManager : MonoBehaviour {
        public class Bubble : MonoBehaviour {
            public bool InQueue {get; private set; } = true;
            public UnityEvent<Bubble> DisposalEvent = new UnityEvent<Bubble>();

            public void OnSpawn() => InQueue = false;

            public void RequestDisposal() {
                if (InQueue) return;
                DisposalEvent?.Invoke(this);
                InQueue = true;
            }
        }

        public class Pool<T> where T : Component {
            public T Prefab;
            public Queue<T> content;
            public int NumBubbles = 0;

            public void Expand(int amount) {
                NumBubbles += amount;
                while (amount-- > 0) {
                    bool prefabIsActive = Prefab.gameObject.activeSelf;

                    // Important: this prevents any OnEnables from running
                    Prefab.gameObject.SetActive(false);

                    GameObject obj = Instantiate(Prefab.gameObject);
                    Prefab.gameObject.SetActive(prefabIsActive);

                    // Grant immortality
                    DontDestroyOnLoad(obj);

                    Bubble bubble = obj.GetComponent<Bubble>();
                    if (!bubble) bubble = obj.AddComponent<Bubble>();
                    bubble.DisposalEvent.AddListener(Collect);

                    content.Enqueue( obj.GetComponent<T>() );
                }
            }

            public void Collect(Bubble bubble) {
                // give up collecting the bubble, someone illegally borrowed it
                if (bubble.transform.parent != null) {
                    Destroy(bubble.gameObject);
                    return;
                }
                content.Enqueue(bubble.GetComponent<T>());
                bubble.gameObject.SetActive(false);
            }
        }
    }

    [DisallowMultipleComponent]
    public partial class ObjectPoolManager : MonoBehaviour {
        public static ObjectPoolManager Instance;

        const int BaseExpansionRate = 1;
        Hashtable pools;
        Dictionary<Scene, HashSet<Bubble>> sceneToBubbleMapping;

        void Awake() {
            if (Instance) Debug.LogError("Multiple Instances of Object Pool Manager!!!");
            Instance = this;

            pools = new Hashtable();
            sceneToBubbleMapping = new Dictionary<Scene, HashSet<Bubble>>();
        }

        void Start() {
            App.BeforeSceneUnload.AddListener(OnSceneUnloaded);
        }

        void OnDestroy() {
            App.BeforeSceneUnload.RemoveListener(OnSceneUnloaded);
        }

        public T Borrow<T>(Scene scene, T Prefab,
            Vector3? position = null, Quaternion? rotation = null) where T : Component {

            if (!Prefab) return null;

            Entity prefabEntity = Prefab.GetComponent<Entity>() ?? Prefab.GetComponentInParent<Entity>();

            if (!(prefabEntity is PoolableEntity))
                Debug.LogError("Entity spawned with the object pool system must be a PoolableEntity.");

            int prefabID = Prefab.GetInstanceID();

            Pool<T> pool = null;
            if (!pools.ContainsKey(prefabID)) {
                pool = new Pool<T>{
                    Prefab = Prefab,
                    content = new Queue<T>()
                };
                pools.Add(prefabID, pool);
            } else {
                pool = pools[prefabID] as Pool<T>;
            }

            if (pool.content.Count == 0)
                pool.Expand(Mathf.Max(pool.NumBubbles, BaseExpansionRate));

            T instantiatedObject = pool.content.Dequeue();

            instantiatedObject.gameObject.transform.SetPositionAndRotation(
                position ?? Vector3.zero,
                rotation ?? Quaternion.identity
            );
            instantiatedObject.gameObject.SetActive(true);

            Bubble bubble = instantiatedObject.GetComponent<Bubble>();
            if (!bubble) Debug.LogError("Bubble not found on pooled object. Maybe a script has destroyed it");
            bubble.OnSpawn();

            if (!sceneToBubbleMapping.ContainsKey(scene))
                sceneToBubbleMapping[scene] = new HashSet<Bubble>();

            sceneToBubbleMapping[scene].Add( bubble );

            return instantiatedObject;
        }

        void OnSceneUnloaded(Scene scene) {
            if (!sceneToBubbleMapping.ContainsKey(scene)) return;

            foreach (Bubble bubble in sceneToBubbleMapping[scene])
                bubble.RequestDisposal();

            sceneToBubbleMapping.Remove(scene);
        }
    }
}
```

## Decoupling with Scriptable Object

One of the reasons why we managed to develop the game so quickly was thanks to 
the data-oriented Model-View-ViewModel pattern commonly used in web development 
to decouple UI and the backend.
Inspired by a [a Unity article on scriptable objects](https://unity.com/how-to/architect-game-code-scriptable-objects),
I tried using scriptable object as data containers that multiple systems can access and modify.

As an example, below is the update function for Miyu, the protagonist of the game. 

```csharp
public class MiyuGrounded : State<Miyu, Miyu.States> {
    public override Miyu.States? Update(StateMachine<Miyu, Miyu.States> stateMachine, Miyu miyu) {
        Vector3 desiredVelocity = miyu.input.desiredMovement * miyu.movementSpeed.Value;

        miyu.Velocity = Mathx.Damp(Vector3.Lerp, miyu.Velocity, desiredVelocity,
                                    (miyu.Velocity.sqrMagnitude > desiredVelocity.sqrMagnitude) ? miyu.deccelerationAlpha : miyu.accelerationAlpha, Time.deltaTime);


        float lastAttackTime = (float) (stateMachine.Blackboard["lastAttackTime"] ?? 0.0f);
        float timeSinceLastAttack = (Time.time - lastAttackTime);

        bool outOfBullets = miyu.magazine.Value <= 0;
        bool canAttack = !outOfBullets && timeSinceLastAttack * miyu.attackSpeed.Value > 1 && miyu.input.shoot;

        if (canAttack) {
            stateMachine.Blackboard["lastAttackTime"] = Time.time;

            Vector3 targetPos = miyu.input.targetPositionWS;
            if (targetPos == miyu.transform.position)
                targetPos = miyu.transform.position + miyu.transform.forward;

            miyu.ShootProjectile(miyu.input.targetPositionWS);
            miyu.magazine.Value--;

        } else if (outOfBullets){
            float timeLeftUntilReload = (float) (stateMachine.Blackboard["timeLeftUntilReload"] ?? 0.0f);

            // this was from previous reload or first reload
            if (timeLeftUntilReload <= 0)
                timeLeftUntilReload = 1 / miyu.reloadRate.Value;

            timeLeftUntilReload -= Time.deltaTime;

            // reload completed
            if (timeLeftUntilReload <= 0)
                miyu.magazine.Value = miyu.magazine.Limiter;

            stateMachine.Blackboard["timeLeftUntilReload"] = timeLeftUntilReload;
        }

        return null;
    }
}
```

For movement, this references the float `miyu.movementSpeed.Value`.
On Miyu herself, `miyu.movementSpeed` is actually a non-serialized scriptable object 
representing a stat value that can scale additively and multiplicatively.

```csharp
public partial class Miyu : PossessableAgent<Miyu.Input>, IHurtable, IHurtResponder, IHitResponder {
    ...
    [BoxGroup("Movement"), SerializeField, Expandable] LinearFloat movementSpeed;
    ...
}

public class LinearFloat : ISerializationCallbackReceiver, ILinearlyScalable<float> {
    public float BaseValue = 0;
    [NonSerialized] public float AdditiveScale;
    [NonSerialized] public float MultiplicativeScale;

    [NonSerialized] public float Value;

    public virtual void OnAfterDeserialize() {
        AdditiveScale = 0;
        MultiplicativeScale = 1;
        Recompute();
    }

    /// Need to be called every time either additive or multiplicative scale is changed.
    public virtual void Recompute() {
        Value = (BaseValue + AdditiveScale) * MultiplicativeScale;
    }
}
```

The perk of doing it this way is the upgrade system and UI does not need to know
anything about the gameplay code.
Below is code for an upgrade:

```csharp
[CreateAssetMenu(fileName = "Buff",
                 menuName = "~/Stats/Buff", order = 1)]
public class Buff : ScriptableObject {
    [System.Serializable]
    struct LinearBuff<T, ST> where T : ScriptableObject, ILinearlyScalable<ST> {
        [field:SerializeField, Expandable]
        public T Stat { get; private set; }
        [field:SerializeField]
        public float AdditiveAmount {get; private set; }
        [field:SerializeField]
        public float MultiplicativeAmount {get; private set; }
    };

    ...
    [SerializeField, ReorderableList] List<LinearBuff<LinearFloat, float>> floatBuffs;
    ...

    public virtual void Apply() {
        foreach (LinearBuff<LinearFloat, float> buff in floatBuffs) {
            ILinearlyScalable<float> stat = buff.Stat;
            stat.AdditiveScale += buff.AdditiveAmount;
            stat.MultiplicativeScale *= buff.MultiplicativeAmount;
            stat.Recompute();
        }
    }
}
```

----

