---
layout: post
title: "Portal Knight"
image:
  thumbnail: /assets/images/gameCaptures/portal-knight/swordVFX.gif
sidebar:
    text: >-
        - Statemachine character controller

        - Melee combat system + animation

        - AI navigation with NavMesh

        - Camera occlusion system, screenspace outline, and screenwipe

        - Audio integration with FMOD

        - Portal and death particles with VFX Graph

    image: /assets/images/gameCaptures/portal-knight/splash.png
    team: 2
    tools: Unity, FMOD, Yarn Spinner
    platforms: Webgl, Windows, Mac
    links:
      - title: "Itch"
        url: "https://thuleanx.itch.io/portal-knight"
        icon: "fab fa-gamepad fa"
      - title: "Github"
        url: "https://github.com/Thuleanx/PortalKnight"
        icon: "fa fa-github-alt"
permalink: /games/portal-knight/
no_masthead: true

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

screenWipeShaderTwirl:
  - url: /assets/images/gameCaptures/portal-knight/twirlMaskShader.png
    image_path: /assets/images/gameCaptures/portal-knight/twirlMaskShader.png

screenWipeShaderCombine:
  - url: /assets/images/gameCaptures/portal-knight/screenWipeShaderCombine.png
    image_path: /assets/images/gameCaptures/portal-knight/screenWipeShaderCombine.png
    
toc: true
toc_sticky: true
toc_label: "Featured Systems"

---
  <!-- overlay_color: "#000" -->
  <!-- overlay_filter: "0.1" -->
  <!-- overlay_image: /assets/images/gameCaptures/portal-knight/bannerv5.png -->
Portal Knight is a 3D isometric hack and slash game created by a team of 2 as a submission for 
[A Game By Its Cover Jam](https://itch.io/jam/a-game-by-its-cover-2022/entries) 
over the month of November 2022.
I was in charge of programming, audio, and a portion of the VFX.

{% include gallery %}
{% include figure image_path="/assets/images/gameCaptures/portal-knight/longFight.gif" alt="gameplay image" %}

<br>

## State Machine (for players and enemies)


![Shadow Enemies](/assets/images/gameCaptures/portal-knight/aitest.gif){:.align-right}
I developed a simple finite state machine that can be applied to player and AI.

The statemachine is a component that features a list of states with events for entering, exiting, and update, as
well as the ability for each state to specify a coroutine to run on entrance. 
The code lives in a separate assembly definition and does not contribute to compilation time.

<p class="clearfix">
</p>


{::options parse_block_html="true" /}
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
            
            if (_currentState >= 0)
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
The state runs a coroutine that waits for the enemy's windup animation, 
then spawning the projectiles, then waits for a recovery period.

<div class="clearfix"/>

```c++
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
```
</details>
{::options parse_block_html="false" /}

<br>

## Character States and Animation

I implemented all gameplay features for the main character Fawn, 
alongside her animation state machine and its transitions.

| Dash | Attack | Special |
| --- | --- | --- |
| ![dash_animation](/assets/images/gameCaptures/portal-knight/dashing.gif) | ![dash_animation](/assets/images/gameCaptures/portal-knight/attack.gif) |![dash_animation](/assets/images/gameCaptures/portal-knight/swordVFX.gif) |
| Fawn's main movement / evasive option, which grants iframes and can be used to cancel attacks and recovery animations. | Fawn has a two-combo attack that knocks enemies backwards. |  Fawn charges light energy by hitting enemies, and can release it as a massive AOE attack. |

<br>

## Navigation with NavMesh

![AI Move Slope](/assets/images/gameCaptures/portal-knight/playerWalkSlope.gif){:.align-right}
Portal Knight's AI uses both a combination of two independent Unity's systems: Character Controller and Navigation mesh.
I made the game's entities move while respecting both systems, and accurately adjust to slopes.

Below is code snippet of movement inside of the Movable class, which both enemy and player agents inherit from.
The code first adjusts the agent's velocity to the slope it's currently on, 
then snap its next position to the closest nav mesh cell.

{::options parse_block_html="true" /}
<details><summary markdown="span">Code Snippet - Movement </summary>

```c++
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

// Apply slope friction if slope is not walkable. The returned value
// is the velocity adjusted to the slope.
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
```

</details>
{::options parse_block_html="false" /}

<br>

## Camera Occlusion System
I implemented a system that occludes objects that obstructs the player's view.

{% include gallery id="occlusion" %}

{::options parse_block_html="true" /}
<details><summary markdown="span">Shader Graph - Occlusion System </summary>

The following is the shader graph for occlusion of opaque objects. 
It determines alpha clipping from a sphere mask around the player, but also making sure that objects behind the player and 
pixels near the player's feet are not occluded.

{::options parse_block_html="false" /}
{% include gallery id="occlusionShader" caption="Shader graph for occlusion system."%}
{::options parse_block_html="true" /}

</details>
{::options parse_block_html="false" /}

<br>

## Death VFX
![death effect](/assets/images/gameCaptures/portal-knight/ingameDeathCropped.gif){:.align-right}
With VFX Graph and Unity's shader graph, I designed and implemented VFX for death and screen wipe. 

- Lock player into the idle animation and dissolve away with a shader.
- GPU-based particles are emitted on the player mesh's surface.
- A material on a screen-wide texture is procedurally animated to produce the screen wipe effect with a shader and DoTween.

{::options parse_block_html="true" /}
<details><summary markdown="span">Shader Graph - Twirl Effect </summary>

![death effect](/assets/images/gameCaptures/portal-knight/deathVFXCropped.gif){:.align-left}

{::options parse_block_html="false" /}
{% include figure image_path="/assets/images/gameCaptures/portal-knight/twirlMaskShader.png" 
caption="Shader graph for twirl and sphere mask around player." %}
![death effect](/assets/images/gameCaptures/portal-knight/deathCropped.png){:.align-right}
{% include figure image_path="/assets/images/gameCaptures/portal-knight/screenWipeShaderCombine.png" 
caption="Shader Graph for coloring twirl and combining with sphere mask."%}
{::options parse_block_html="true" /}

</details>

<details><summary markdown="span">Code Snippet - Twirl Effect </summary>

The following is a snippet for code for screen wipe using DoTween. 
To animate the screen wipe, it manipulates parameters of a material of a 
screen-wide overlayed image.
```c++
/* Trigger death wipe effect. Should only be run if transitioning is false*/
IEnumerator _deathWipe(string sceneName) {
    SetEnableWipeEffect(true);
    // zoom in to player
    currentTween = DOVirtual.Float(maxRange, focusRange, fadeOutDuration.x, 
        SetMaskRange).SetEase(easeFocus);
    yield return currentTween.WaitForCompletion();
    yield return new WaitForSeconds(focusWait);
    currentTween?.Kill();

    // totally occlude screen
    float fadeOutDurationTail = fadeOutDuration.y - fadeOutDuration.x;
    currentTween = DOVirtual.Float(focusRange, minRange, fadeOutDurationTail,
        SetMaskRange).SetEase(easeOut);
    yield return currentTween.WaitForCompletion();
    App.instance.RequestLoad(sceneName);
    transitioning = false;	
}

/* Set spherical cutout range. */
public void SetMaskRange(float value) => BlockoutImage.material.SetFloat("_Radius", value);

/* Use to enable/disable the effect. */
public void SetEnableWipeEffect(bool enabled) => BlockoutImage.material.SetFloat("_Enabled", enabled ? 1 : 0);
```
</details>
{::options parse_block_html="false" /}
