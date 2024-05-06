---
layout: post
title: "Doomolish"
image: 
    thumbnail: /assets/images/gameCaptures/doomolish/round2.gif
sidebar:
  - text: >-

        **Jam Project**<br>
        **Tools:** Rust, Vulkan, Bevy_ecs, Blender, Aseprite, Jummbus<br>
        **Duration:** 2 weeks<br>
        **Platforms:** Windows<br>

        <hr>
    image: /assets/images/gameCaptures/doomolish/logo.png
  - text: >-
        - **Vulkan renderer** in Rust with vulkanalia and winit

        - 2D **continuous collision detection** supporting circles and line segments

        - Integration with **Bevy ECS**

        - Camera controller, input manager, and simple enemy AI

        - **Audio manager with Kira**

        <hr>
    links:
      - title: "Itch"
        url: "https://thuleanx.itch.io/doomolish"
        icon: "fab fa-gamepad fa"
      - title: "Github"
        url: "https://github.com/Thuleanx/Saga"
        icon: "fab fa-fw fa-github"
permalink: /games/doomolish/
no_masthead: true

gallery1:
  - image_path: /assets/images/gameCaptures/doomolish/round2.gif
  - image_path: /assets/images/gameCaptures/doomolish/round3.gif

---

Doomolish is my solo Doom-inspired pixel fps made over the course of a 2 week game jam.
The game was made with my Vulkan engine written in Rust over the same time duration, baring some Vulkan boilerplate.
With this entry, I set out to create a game from scratch by myself, from engine to modeling, spritework, and music.

{% include gallery id="gallery1" %}

<br>

# What I Learnt

Vulkan is significantly different from OpenGL, not only in verbosity but also in design.
One huge difference is that the graphics pipeline is immutable; this forced me to
plan the engine architecture around identifying and minimizing 
when the pipeline or command buffers need to be regenerated.
What makes it more of a fun challenge is programming this in Rust with bevy_ecs, 
since I had to restrict mutable access to the graphics layer as much as possible to maximize concurrency.

# Code Snippets

Below are some code snippets of the engine.

## Continous Collision Detection
I've written a blog detailing the derivation of Doomolish's collision detection 
[here](/math/continuous-collision/2024/03/24/doomolish-collision-detection.html).
It supports **2D continuous collision** between static line-segments and dynamic circles, 
and boils down two functions, each using only **1 square root operation**.

```rust
fn penetration_time_circle_line(
    circle: Circle, 
    line_segment: LineSegment, 
    direction: Vector2<f32>
) -> Option<f32> {

    if direction.is_zero() {
        return None;
    }

    let normal_direction = line_segment.get_normal_scaled(circle.position);

    // this means the circle is moving perpendicular or away from the line segment
    // we can skip computation
    let moving_away = cgmath::dot(normal_direction, direction) >= 0.0;
    if moving_away {
        return None;
    }

    let end_position = direction + circle.position;

    // Let a = circle.position
    // Let b = circle.position + direction
    // Let c = line.0
    // Let d = line.1
    let badc = saga_utils::cross_2d(
        end_position - circle.position,
        line_segment.1 - line_segment.0,
    );
    let acdc = saga_utils::cross_2d(
        circle.position - line_segment.0,
        line_segment.1 - line_segment.0,
    );

    let quadratic_formula_a = badc * badc;
    let quadratic_formula_b = 2.0 * badc * acdc;
    let quadratic_formula_c = acdc * acdc - circle.radius * circle.radius * line_segment.len2();

    let is_solution_valid = |t: f32| {
        // checks if the intersection is in the part of the line we care about
        let p = direction * t + circle.position;
        let projection_onto_line =
            cgmath::dot(p - line_segment.0, line_segment.direction());

        let ray_intersects_capsule_segment =
            projection_onto_line >= 0.0 && projection_onto_line <= line_segment.len2();

        ray_intersects_capsule_segment
    };

    if let Ok(solutions) = saga_utils::solve_quadratic(quadratic_formula_a, quadratic_formula_b, quadratic_formula_c) {
        let does_solutions_has_both_signs = solutions.iter().fold(1.0, |a,b| a*b) <= 0.0;
        let is_first_solution_valid = solutions.iter().map(|&t| is_solution_valid(t)).nth(0).unwrap_or(false);

        let is_already_penetrating = does_solutions_has_both_signs && is_first_solution_valid;
        if is_already_penetrating {
            return Some(0.0);
        }

        return solutions.iter().find(|&&t| is_solution_valid(t) && t >= 0.0).map(|x| x.to_owned());
    }

    None
}
```

## Camera System

Below is my implementation of DOOMolish's camera system with strafe tilting and
camera shake.

```rust
fn system_animate_camera(
    time: Res<Time>,
    mut trauma: ResMut<Trauma>,
    perlin: Local<Perlin>,
    button_input: Res<ButtonInput>,
    mut camera_z_rotation: Local<f32>,
    mut camera: Query<(&mut Position, &mut Rotation), With<Camera>>,
    player: Query<(&Position, &Rotation), (With<Player>, Without<Camera>)>,
) {
    const ROTATIONAL_SMOOTHING: f32 = 0.005;
    const TILT_SCALE: f32 = 0.5;
    const TRAUMA_DECAY_RATE_PER_SECOND: f32 = 3.0;
    const SHAKE_NOISE_SCROLL_SPEED : f32 = 50.0;
    let shake_scale = Vector3::new(10.0, 10.0, 5.0);

    if player.is_empty() || camera.is_empty() {
        return;
    }

    let (player_position, player_rotation) = player.single();
    let (mut camera_position, mut camera_rotation) = camera.single_mut();

    let movement_a = if button_input.is_key_down(Key::A) { 1 } else { 0 };
    let movement_d = if button_input.is_key_down(Key::D) { 1 } else { 0 };
    let horizontal_movement = (movement_d - movement_a) as f32;

    // frame rate independent lerp
    let smoothing_power = 1.0 - ROTATIONAL_SMOOTHING.powf(time.delta_seconds());
    let desired_rotation = TILT_SCALE * horizontal_movement;

    *camera_z_rotation =
        *camera_z_rotation * (1.0 - smoothing_power) + desired_rotation * smoothing_power;

    let tilt_rotation: Quat = Quaternion::from(Euler {
        x: Deg(0.0),
        y: Deg(0.0),
        z: Deg(*camera_z_rotation),
    });

    // screen shake calculation
    trauma.0 = (trauma.0 - time.delta_seconds() * TRAUMA_DECAY_RATE_PER_SECOND)
        .clamp(0.0, 1.0);

    let noise_sample = time.elapsed_seconds_f64() * SHAKE_NOISE_SCROLL_SPEED;

    let noise_x = perlin.get([0.0, noise_sample, 3.0]);
    let noise_y = perlin.get([100.0, noise_sample, 3.0]);
    let noise_z = perlin.get([200.0, noise_sample, 3.0]);

    let shake_intensity = trauma.0 * trauma.0;
    let shake = Vector3::new(
        noise_x as f32 * shake_scale.x,
        noise_y as f32 * shake_scale.y,
        noise_z as f32 * shake_scale.z,
    ) * shake_intensity;

    let shake_rotation: Quat = Quaternion::from(Euler {
        x: Deg(shake.x),
        y: Deg(shake.y),
        z: Deg(shake.z),
    });

    camera_position.0 = player_position.0;
    camera_rotation.0 = player_rotation.0 * tilt_rotation * shake_rotation;
}
```

## Health System

Applying damage and registering death are event-driven, meaning other systems 
need not have mutable access to Health to apply a damaging effect.
Additionally, processing deaths also involves removing meshes' draw calls from the 
command buffer and rebuilding it, so it makes sense to handle this event only when the
graphics device is idle.

```rust
#[derive(Component)]
pub struct Health {
    pub current_health: u32,
    pub max_health: u32,
}

#[derive(Event)]
pub struct DamageEvent {
    pub damage: u32,
    pub target: Entity,
    pub source: Entity,
}

#[derive(Event)]
pub struct DeathEvent {
    pub target: Entity,
}

fn system_register_damage(
    mut damage_events: EventReader<DamageEvent>,
    mut death_event_invoker: EventWriter<DeathEvent>,
    mut entities_with_health: Query<&mut Health>,
) {
    for damage_event in damage_events.read() {
        let health_query = entities_with_health.get_mut(damage_event.target);

        let mut health = match health_query {
            Ok(health) => health,
            Err(_) => continue,
        };

        let already_dead = health.current_health == 0;
        if already_dead {
            continue;
        }

        // Decrement health
        health.current_health = if health.current_health > damage_event.damage {
            health.current_health - damage_event.damage
        } else {
            death_event_invoker.send(DeathEvent {
                target: damage_event.target,
            });
            0
        };
    }
}

fn system_on_entity_death(
    mut graphics: ResMut<Graphics>,
    mut death_event_reader: EventReader<DeathEvent>,
    mut rebuild_command_writer: EventWriter<RebuildCommand>,
    entities_with_mesh: Query<
        (
            Entity,
            &Position,
            Option<&Mesh>,
            Option<&MainTexture>,
            Option<&MeshRenderingInfo>,
        ),
        Without<Player>,
    >,
    mut commands: Commands,
) {
    log::trace!("Cleaning up dead target");
    let all_dead_targets: HashSet<Entity> = death_event_reader
        .read()
        .map(|death_event| death_event.target)
        .collect();
    // We wait for device idle because we need to remove 
    // meshes from the pipeline
    unsafe {
        graphics.device_wait_idle().unwrap();
    }
    entities_with_mesh
        .iter()
        .filter(|(entity, _, _, _, _)| all_dead_targets.contains(entity))
        .for_each(
            |(entity, position, mesh, main_texture, mesh_rendering_info)| {
                if let (Some(mesh), Some(main_texture), Some(mesh_rendering_info)) =
                    (mesh, main_texture, mesh_rendering_info)
                {
                    saga_renderer::remove_mesh(
                        graphics.as_ref(),
                        mesh,
                        main_texture,
                        mesh_rendering_info,
                    );
                }
                commands.entity(entity).despawn();
                spawn_blood_pool(&mut graphics, &mut commands, position.0);
            },
        );
    rebuild_command_writer.send(RebuildCommand);
}
```

----

