---
title: "Ray"
excerpt: "Optimized C++ RayTracer"
header:
  overlay_color: "#000"
  overlay_filter: "0.0"
  overlay_image: /assets/images/graphicsCaptures/ray/raykiller.png
  teaser: /assets/images/graphicsCaptures/ray/recursiveSphere8.png
sidebar:
  - title: "Tools"
    image: "/assets/images/graphicsCaptures/ray/shadow_test.png"
    text: "C++, Qt Creator"
  - title: "Responsiblities"
    text: >-
        Design and implement rendering features, including shadow, texture mapping, reflection, refraction, and depth of field.

gallery:
  - url: /assets/images/graphicsCaptures/ray/cone.png
    image_path: /assets/images/graphicsCaptures/ray/cone.png
  - url: /assets/images/graphicsCaptures/ray/cube.png
    image_path: /assets/images/graphicsCaptures/ray/cube.png
  - url: /assets/images/graphicsCaptures/ray/cylinder.png
    image_path: /assets/images/graphicsCaptures/ray/cylinder.png

gallery2:
  - url: /assets/images/graphicsCaptures/ray/recursiveSphere3.png
    image_path: /assets/images/graphicsCaptures/ray/recursiveSphere3.png
  - url: /assets/images/graphicsCaptures/ray/recursiveSphere4.png
    image_path: /assets/images/graphicsCaptures/ray/recursiveSphere4.png
  - url: /assets/images/graphicsCaptures/ray/recursiveSphere8.png
    image_path: /assets/images/graphicsCaptures/ray/recursiveSphere8.png
  - url: /assets/images/graphicsCaptures/ray/recursiveSphere10reflections.png
    image_path: /assets/images/graphicsCaptures/ray/recursiveSphere10reflections.png
  - url: /assets/images/graphicsCaptures/ray/raykiller.png
    image_path: /assets/images/graphicsCaptures/ray/raykiller.png
  - url: /assets/images/graphicsCaptures/ray/noTexRecursiveRay.png
    image_path: /assets/images/graphicsCaptures/ray/noTexRecursiveRay.png

gallery3:
  - url: /assets/images/graphicsCaptures/ray/test_dof_dof.png
    image_path: /assets/images/graphicsCaptures/ray/test_dof_dof.png
  - url: /assets/images/graphicsCaptures/ray/texture_cheese.png
    image_path: /assets/images/graphicsCaptures/ray/texture_cheese.png
  - url: /assets/images/graphicsCaptures/ray/reflection.png
    image_path: /assets/images/graphicsCaptures/ray/reflection.png
  - url: /assets/images/graphicsCaptures/ray/refract.png
    image_path: /assets/images/graphicsCaptures/ray/refract.png
  - url: /assets/images/graphicsCaptures/ray/refract-whitted.png
    image_path: /assets/images/graphicsCaptures/ray/refract-whitted.png
  - url: /assets/images/graphicsCaptures/ray/refraction.png
    image_path: /assets/images/graphicsCaptures/ray/refraction.png

---

As a month-long project for Brown's computer graphics class, I made this raycaster using C++, OpenGL, and Qt.
It supports shadow, texture mapping, reflection, refraction, and depth of field.

The raytracer operates on 4 elementary objects defined by implicit equations and solving their intersection with the ray.

{% include gallery %}

To render complex shapes, I implemented space-partitioning data structures including Kd-Tree, BVH tree, and Quad tree. 
The ray tracer traverses these tree to look for intersections, and prune unnecessary traversals by the bounding volume of each node.

{% include gallery id="gallery2" %}

With recursive raytracing and multi-sampling, I also implemented shadows, depth of field, reflection, and refraction.

{% include gallery id="gallery3" %}
