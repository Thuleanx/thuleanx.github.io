---
layout: page
title:  "2D Continuous Collision"
categories: math continuous-collision
excerpt: Fast circle line-segment collision for [DOOMolish](/games/doomolish)
image: 
    thumbnail: /assets/images/gameCaptures/doomolish/thumbnail.gif
no_masthead: true
---

This article describes my implementation of fast circle-line-segment intersection 
for my game [DOOMolish](/games/doomolish), a doom clone made with rust, Vulkan,
and Bevy ECS for a 2 week game jam.

# Setup

For this Jam, I needed to detect and resolve collisions between a lot of entities 
and a static environment of hallways and rooms.

3D collisions were out of the table. 
I didn't want to spend the entire two weeks on debugging if something had gone wrong.
Implementing discrete collisions was an option, but could prove complicated if the 
player somehow ends up squished between different enemies.
In the end, I chose to model movable entities as circles and the hallway walls as line segments, and go with reliable continuous collision detection.

# Implementation

{::options parse_block_html="true" /}
<details><summary markdown="span">Code Snippet - Circle-LineSegment Intersection</summary>

```rust
fn penetration_time_circle_line(circle: Circle, line_segment: LineSegment, direction: Vector2<f32>) -> Option<f32> {
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
</details>


<details><summary markdown="span">Code Snippet - Circle-Point Intersection </summary>

```rust
fn penetration_time_circle_point(circle: Circle, point: Vector2<f32>, direction: Vector2<f32>) -> Option<f32> {
    let circle_to_point = point - circle.position;

    // We ignore collisions if ray goes away from circle
    if cgmath::dot(circle_to_point, direction) <= 0.0 {
        return None;
    }

    if circle_to_point.magnitude2() <= circle.radius * circle.radius {
        return Some(0.0);
    }

    let quadratic_formula_a = cgmath::dot(direction, direction);
    let quadratic_formula_b = -2.0 * cgmath::dot(direction, circle_to_point);
    let quadratic_formula_c =
        cgmath::dot(circle_to_point, circle_to_point) - circle.radius * circle.radius;

    let quadratic_solutions = saga_utils::solve_quadratic(
        quadratic_formula_a,
        quadratic_formula_b,
        quadratic_formula_c,
    );

    if let Ok(quadratic_solutions) = quadratic_solutions {
        return quadratic_solutions.iter().cloned().find(|&t| t >= 0.0);
    }

    None
}
```
</details>
{::options parse_block_html="false" /}
<br>

# Strategy

As with most things collision-detection, we want to first enumerate all the cases we have to deal with:
1. Collision between two moving circles.
2. Collision between a moving point and a circle (for raycasting).
3. Collision between a moving circle and a line segment.
4. Collision between a moving point and a line segment (for raycasting).

(4) is a well-studied case that's analoguous to line-segment intersection. 
If you are careful, it is possible to do this without using any square root operation.

Case (1) can actually be reduced to an instance of case (2). 
If we have two moving circles $A$ and $B$, then the time $t$ at which $A$ and $B$ collides is the same as that of a collision 
between $C$, a point moving at $A$ and $B$'s combined velocity, and $D$, a static circle of $A$ and $B$'s combined radius.
Therefore, let us focus on the cases (2) and (3). Below, I outlined my solution which uses 1 square root operation for case (2) and (3).

# Case 2: Circle Point Collision

Problem statement: Find the time $t$ at which a circle at position $\vec{p}$ of radius $C$ moving at velocity $\vec{v}$
intersects with point $\vec{q}$.

We know that at time $t$, position $p$ and $q$ are exactly $C$ apart:

$$
\begin{align}
|\vec{p} + t * \vec{v} - \vec{q}| &= C \\
\Rightarrow |\vec{p} + t * \vec{v} - \vec{q}|^2 &= C^2
\end{align}
$$

This can be solved with quadratic formula costing only 1 square root operation with:

$$
\begin{align}
    a &= |\vec{v}|^2 \\
    b &= 2 \vec{v} \cdot (\vec{p} - \vec{q}) \\
    c &= |\vec{p} - \vec{q}|^2 - C^2
\end{align}
$$

There are possibly two solutions for $t$, and we want to take the lowest positive solution
should one exist.
This would be the end of the story if we want to only find the intersection time.
However, since we want to detect only meaningful collisions, we need to add the following checks:

1. If the circle is heading away from the point, we can short-circuit the entire computation altogether.
2. Otherwise if the point is already in the circle's radius we return a collision time $t = 0$ to prevent further penetration.

The first case can be done by projecting $\vec{v}$ onto $\vec{p} - \vec{q}$ and checking the sign.
The second case can be done with a distance check, although we test $|\vec{p} - \vec{q}|^2$ against $C^2$ to avoid using square root.

# Case 3: Circle Line-Segment Collision

Problem statement: Find the time $t$ at which a circle at position $\vec{p}$ of radius $C$ moving at velocity $\vec{v}$ intersects with the line segment between points $\vec{c}$ and $\vec{d}$.

The approach I took is a degenerate version of the 3D problem of sphere line-segment collision that I implemented as part of 
my previous game engine [Saga](/graphics/saga-engine/).
The key is to have line segment borrow the circle's radius, effectively turning it into a capsule.

We can capture collisions with the top and bottom of the capsule with the algorithm we developed for case 2.
For the midsection, we can use the fact that a point $\vec{P}$ is distance $d$ away from a line segment $\vec{pq}$ 
if the paralellogram defined by $\vec{P}$, $\vec{p}$, and $\vec{q}$ has the same area as the rectangle 
formed by $\vec{p}$, $\vec{q}$, and the normal vector to $\vec{pq}$ with length $d$.

This gives us the following equality:

$$
\begin{align}
    |(\vec{d} - \vec{c}) \times (\vec{p} + \vec{v} t - \vec{c})| &= C |\vec{q} - \vec{p}| \\
    \Rightarrow |(\vec{d} - \vec{c}) \times (\vec{p} - \vec{c}) + \vec{v} t)|^2 &= C |\vec{q} - \vec{p}|^2 \\
    \Rightarrow |(\vec{d} - \vec{c}) \times (\vec{p} - \vec{c}) + (\vec{d} - \vec{c}) \times \vec{v}t|^2 &= C |\vec{q} - \vec{p}|^2 & (\text{distributive cross product}) \\
\end{align}
$$

Which can be solved with quadratic formula yet again costing only 1 square root operation with:

$$
\begin{align}
    a &= [(\vec{d} - \vec{c}) \times \vec{v}]^2 \\
    b &= 2 [(\vec{d} - \vec{c}) \times (\vec{p} - \vec{c})] ((\vec{d} - \vec{c}) \times \vec{v}) \\
    c &= [(\vec{d} - \vec{c}) \times (\vec{p} - \vec{c})]^2 - C |\vec{q} - \vec{p}|^2
\end{align}
$$

This only gives you values for $t$ where the circle collides with the line $\vec{pq}$, but we need to find collisions only with the line segment from $\vec{p}$ to $\vec{q}$.
One way is to compute the point $\vec{P} = \vec{v} t + \vec{p}$, then project it onto the line $\vec{pq}$ and check if it is between $\vec{p}$ and $\vec{q}$.
Since the three points are colinear, we can use the sign of the dot product $(\vec{p} - \vec{P}) \cdot (\vec{q} - \vec{P})$.
