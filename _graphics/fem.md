---
title: "Soft Body Simulation"
excerpt: "Finite Element Method"
header:
  overlay_color: "#000"
  overlay_filter: "0.5"
  overlay_image: /assets/images/graphicsCaptures/fem/banner.png
  teaser: /assets/images/graphicsCaptures/fem/meshroom x sphere.gif
sidebar:
  - title: "Tools"
    image: "/assets/images/graphicsCaptures/fem/logo.png"
    text: "C++, Qt Creator"
  - title: "Responsiblities"
    text: >-
        Implement FEM based soft body simulation based on tetrahedral mesh.
  - title: "Links"
    text: >-
        [Itch.io](https://brownrisdgraphicss.itch.io/fem) /
        [Repository](https://github.com/Thuleanx/PortalKnight)

gallery:
  - url: /assets/images/graphicsCaptures/fem/cone.gif
    image_path: /assets/images/graphicsCaptures/fem/cone.gif
  - url: /assets/images/graphicsCaptures/fem/sphere.gif
    image_path: /assets/images/graphicsCaptures/fem/sphere.gif
  - url: /assets/images/graphicsCaptures/fem/ellipsoid.gif
    image_path: /assets/images/graphicsCaptures/fem/ellipsoid.gif

gallery2:
  - url: /assets/images/graphicsCaptures/fem/meshroom x sphere.gif
    image_path: /assets/images/graphicsCaptures/fem/meshroom x sphere.gif
  - url: /assets/images/graphicsCaptures/fem/sphereSphere.gif
    image_path: /assets/images/graphicsCaptures/fem/sphereSphere.gif

gallery3:
  - url: /assets/images/graphicsCaptures/fem/spherecubeHitEdge.gif
    image_path: /assets/images/graphicsCaptures/fem/spherecubeHitEdge.gif
  - url: /assets/images/graphicsCaptures/fem/spherecubeHitFace.gif
    image_path: /assets/images/graphicsCaptures/fem/spherecubeHitFace.gif
  - url: /assets/images/graphicsCaptures/fem/spherecubeHitVertex.gif
    image_path: /assets/images/graphicsCaptures/fem/spherecubeHitVertex.gif

gallery4:
  - url: /assets/images/graphicsCaptures/fem/sphereSphere.gif
    image_path: /assets/images/graphicsCaptures/fem/sphereSphere.gif
    title: "Regular 5000 simulation frames per second."
  - url: /assets/images/graphicsCaptures/fem/adaptiveStepping.gif
    image_path: /assets/images/graphicsCaptures/fem/adaptiveStepping.gif
    title: "Adaptive 60 simulation frames per second on average."

---

Following this [1997 Siggraph course](https://www.cs.cmu.edu/~baraff/sigcourse/) and [1999 paper](http://graphics.berkeley.edu/papers/Obrien-GMA-1999-08/Obrien-GMA-1999-08.pdf), 
I implemented realistic physics simulation over two weeks in C++ and OpenGL utilizing the Finite Element Method.

{% include gallery %}

The simulation takes in an input tetrahedral mesh from an obj file, and performs calculations for forces such as
gravity, stress, strain, and internal viscous damping. 

{% include gallery id="gallery2" %}

The program uses the RK4-5 iterative method to simulate each timestep and runs in realtime.
Collisions are discrete and involves pushing the tetrahedron away from the other object along the collision's normal vector.

{% include gallery id="gallery3" %}

When objects are not being deformed, we don't need to simulate them too precisely. 
I implemented adaptive stepsizing to adjust my timestep to ensure that the simulation uses the largest 
possible timestep while staying under an error threshold. 

{% include gallery id="gallery4" %}


