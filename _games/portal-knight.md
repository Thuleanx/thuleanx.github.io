---
title: "Portal Knight"
excerpt: "3D isometric hack and slash"
header:
  teaser: /assets/images/gameCaptures/portal-knight/swordVFX.gif
sidebar:
  - title: "Links"
    image: "/assets/images/gameCaptures/portal-knight/splash.png"
    text: >-
        [Itch.io](https://thuleanx.itch.io/portal-knight) /
        [Repository](https://github.com/Thuleanx/PortalKnight)
  - title: "Roles"
    text: "Programmer, Audio Designer"
  - title: "Responsiblities"
    text: >-
        - Statemachine character controller

        - Melee combat system + animation integration

        - AI navigation with NavMesh

        - Camera occlusion system, screenspace outline, and screenwipe

        - Audio integration with FMOD.

        - Portal and death particles with VFX Graph.
  - title: "Tools"
    text: "Unity, FMOD Studio"

gallery:
  - url: /assets/images/gameCaptures/portal-knight/initial_enter.png
    image_path: /assets/images/gameCaptures/portal-knight/initial_enter.png
  - url: /assets/images/gameCaptures/portal-knight/go forth.png
    image_path: /assets/images/gameCaptures/portal-knight/go forth.png
  - url: /assets/images/gameCaptures/portal-knight/light.png
    image_path: /assets/images/gameCaptures/portal-knight/light.png

occlusion:
  - url: /assets/images/gameCaptures/portal-knight/ingameOcclusion.gif
    image_path: /assets/images/gameCaptures/portal-knight/ingameOcclusion.gif
  - url: /assets/images/gameCaptures/portal-knight/earlyOcclusionCropped.gif
    image_path: /assets/images/gameCaptures/portal-knight/earlyOcclusionCropped.gif

occlusionShader:
  - url: /assets/images/gameCaptures/portal-knight/occlusionShader.png
    image_path: /assets/images/gameCaptures/portal-knight/occlusionShader.png

---
  <!-- overlay_color: "#000" -->
  <!-- overlay_filter: "0.1" -->
  <!-- overlay_image: /assets/images/gameCaptures/portal-knight/bannerv5.png -->

Portal Knight is a 3D isometric hack and slash game created by a team of 2 as a submission for 
[A Game By Its Cover Jam](https://itch.io/jam/a-game-by-its-cover-2022/entries) 
over the month of November 2022. 
I was in charge of programming, audio, and part of the VFX.

{% include gallery %}
{% include figure image_path="/assets/images/gameCaptures/portal-knight/longFight.gif" alt="gameplay image" %}

{::options parse_block_html="true" /}

<details><summary markdown="span">State Machine (for player and enemies)</summary>

I developed a simple finite state machine that can be applied to player and AI.

The statemachine is a component that features a list of states with events for entering, exiting, and update. 
It lives on a separate assembly definition as the main game code, and is therefore portable to other projects and does not drag down compile time.

<details><summary markdown="span">Code Snippet - State Machine</summary>

```c++
using System.Collections;
using UnityEngine;

namespace Thuleanx.AI.FSM {

// Generic State Machine.
// Needs to be initialized with number of states by running ConstructMachine, 
// AssignState to assign all the states, then Init to initilaize the first state.
// By default, state 0 is the state the machine starts in.
public abstract class StateMachine<Agent> : MonoBehaviour {
    const int STAY_AT_SAME_STATE = -1;

    Agent agent;
    State<Agent>[] States;
    Coroutine stateCoroutine;

    int _currentState = -1; // This -1 prevents End to be run on State 
                            // the first time it's assigned

    // Wrapper around real state. Ensure functions like End and Begin
    // are being called. 
    public int State { 
        get => _currentState; 
        private set {
            // No need to run start and end if transition to the same state. 
            if (value == _currentState || value == STAY_AT_SAME_STATE)
                return;

            if (stateCoroutine != null) 
                StopCoroutine(currentCoroutine);
            
            if (_currentState > 0)
                States[_currentState]?.End(agent);

            _currentState = value;
            States[_currentState]?.Begin(agent);

            IEnumerator sequenceToRun = States[_currentState]?.Coroutine(agent);
            if (sequenceToRun != null) currentCoroutine = StartCoroutine(sequenceToRun);
        }
    }

    public void ConstructMachine(Agent agent, int numberOfStates) {
        this.agent = agent;
        States = new State<Agent>[numberOfStates];
    }

    public void Init() => State = 0;

    public void AssignState(int index, State<Agent> state) {
        States[index] = state;
        state.SetStateMachine(this);
    }
    public void SetState(int index) => State = index;

    // The update functions returns an state index of the state
    // to transition to.
    public void Update() => SetState(States[State].Update(agent));
    public void FixedUpdate() => SetState(States[State].FixUpdate(agent));
}}
```
</details>


<details><summary markdown="span">Code Snippet - Enemy Shoot Projectile </summary>

![shadow-enemy-attack](/assets/images/gameCaptures/portal-knight/earlyRigZoom.gif){:.align-right}
The following code is for the enemy's special attack that spawns multiple projectiles.
It features a coroutine that gets run automatically by the State Machine.
The coroutine responsible for waiting for the enemy's windup animation, 
then spawning the projectiles, then waiting for a recovery.


```c++
// ...
public class ShadowAttackState : State<ShadowEnemy> {
    Timer onCooldown; // internal cooldown timer for attack

    void spawnAttackProjectiles() {
        for (int i = 0; i < monster.attackCount; i++) {
            float offsetPhi = Mathx.RandomRange(monster.attackEmissionPhi.x,
                monster.attackEmissionPhi.y) * Mathf.Deg2Rad;
            float offsetTheta = 360.0 * i / monster.attackCount * Mathf.Deg2Rad;
            float offsetDistance = monster.attackEmissionDistance;

            Vector3 spawnOffset = Calc.ToSpherical(offsetDistance, offsetTheta, offsetPhi);
            Vector3 startSpeed = spawnOffset.normalized * monster.attackSpeed;

            // Call to object pooler to borrow a projectile
            // This prevents frequent initialization of gameobjects / memory which can
            // be slow
            ShadowProjectile projectile = monster.attackBulletPool.BorrowTyped
            <ShadowProjectile>(
                monster.gameObject.scene, 
                monster.gameObject.transform.position + spawnOffset
            );

            projectile.Initialize(startSpeed);
        }
    }

    public override bool CanEnter(ShadowEnemy monster) => !onCooldown 
        && InAttackRange(monster);

    public override IEnumerator Coroutine(ShadowEnemy monster) {
        monster.Drag = monster.deccelerationAlpha;
        
        // monster windup animation happens here
        monster.Anim.SetTrigger(monster.attackTrigger);
        yield return monster.waitForTrigger();

        spawnAttackProjectiles();

        // wait for attack rewind animation
        yield return monster.waitForTrigger();
        yield return new WaitForSeconds(monster.attackRecovery);

        onCooldown = Mathx.RandomRange(monster.attackCooldown.x, monster.attackCooldown.y);

        monster.Drag = 0;
        SetState((int) ShadowEnemy.State.Aggro);
    }

    bool InAttackRange(ShadowEnemy monster) 
        => (monster.transform.position - monster.player.transform.position).sqrMagnitude 
            <= monster.attackRange * monster.attackRange;
}
//...
```
</details>

</details>

<details><summary markdown="span">AI Navigation with NavMesh</summary>

![AI Move Slope](/assets/images/gameCaptures/portal-knight/playerWalkSlope.gif){:.align-right}
Portal Knight's AI uses both a combination of two independent Unity's systems: Character Controller and Navigation mesh.
The former deals with collisions with dynamic and static objects and is used for steering, while the later for pathfinding.
I made the game's entities move while respecting both systems, and accurately adjust to slopes.

Below is code snippet of movement inside of the Movable class, which both enemy and player agents inherit from.

<details><summary markdown="span">Code Snippet - Movement </summary>

```c++
// ...

/// Move agent by a displacement vector, respective slopes and 
/// stay inside the navmesh when possible
protected override void Move(Vector3 displacement) {
    if (displacement.sqrMagnitude <= 1e-6) return;

    displacement = adjustVelocityToSlope(displacement, Controller.slopeLimit);
    Vector3 nxtPos = displacement + transform.position;

    if (FindClosestNavPoint(nxtPos, out Vector3 adjustedNxtPos)) {
        Controller.Move(adjustedNxtPos - transform.position);
    } else {
        // We move the character down, in case it somehow ended up airborne
        // Or starts out airborne due to bad placement
        Controller.Move(Physics.gravity * Time.deltaTime + displacement);
    }
}

/// Find closest point on the navmesh to input point in a small radius
/// If none is found, then return value is the original point.
bool findClosestNavPoint(Vector3 pos, out Vector3 resPos) {
    resPos = pos;
    if (NavMesh.SamplePosition(pos, out NavMeshHit hit, STANDARD_RAY_DISTANCE, NavMesh.AllAreas)) {
        resPos = hit.position;
        return true;
    }
    return false;
}

protected Vector3 adjustVelocityToSlope(Vector3 velocity, float slopeLimit) {
    var ray = new Ray(transform.position + Vector3.down * STANDARD_RAY_DISTANCE, Vector3.down);
    RaycastHit hitGround;
    // no ground found
    if (!Physics.Raycast(ray, out hitGround)) 
        return velocity;

    Vector3 groundNormal = hitGround.normal;
    bool canWalkSlope = (Vector3.Angle(Vector3.up, groundNormal) <= slopeLimit);

    if (!canWalkSlope) {
        // slide if slope is unwalkable
        velocity.x += (1f - groundNormal.y) * groundNormal.x * slideFriction;
        velocity.z += (1f - groundNormal.y) * groundNormal.z * slideFriction;
    }

    return velocity;
}

//...
```

</details>

</details>

<details><summary markdown="span">Camera Occlusion System</summary>
I implemented a system that occludes objects that obstructs the player's view.
It works creating a sphere mask around the player, and using that to determine the alpha clipping inside a fragment shader (with Unity's shader graph).

{::options parse_block_html="false" /}
{% include gallery id="occlusion" %}
{::options parse_block_html="true" /}

<details><summary markdown="span">Shader Graph - Occlusion System </summary>

The following is the shader graph for occlusion of opaque objects. 
It determines alpha clipping from a sphere mask around the player, but also making sure that objects behind the player and 
pixels near the player's feet does not get occluded (upper block).


{::options parse_block_html="false" /}
{% include gallery id="occlusionShader" caption="Shader graph for occlusion system."%}
{::options parse_block_html="true" /}

</details>

</details>

{::options parse_block_html="false" /}



