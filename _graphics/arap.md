---
title: "ARAP Deformation"
excerpt: "Rigid Surface Editing"
header:
  teaser: /assets/images/graphicsCaptures/arap/armadillo.gif
sidebar:
  - title: "Tools"
    image: "/assets/images/graphicsCaptures/arap/sphere.png"
    text: "C++, OpenGL"
  - title: "Responsiblities"
    text: >-
        Design and implement solvers and employ parallelization techniques for
        deformation to be calculated in realtime.

gallery:
  - url: /assets/images/graphicsCaptures/arap/bean.gif
    image_path: /assets/images/graphicsCaptures/arap/bean.gif
  - url: /assets/images/graphicsCaptures/arap/sphere.gif
    image_path: /assets/images/graphicsCaptures/arap/sphere.gif
  - url: /assets/images/graphicsCaptures/arap/armadillo.gif
    image_path: /assets/images/graphicsCaptures/arap/armadillo.gif

gallery2:
  - url: /assets/images/graphicsCaptures/arap/teapot.gif
    image_path: /assets/images/graphicsCaptures/arap/teapot.gif
  - url: /assets/images/graphicsCaptures/arap/peter.gif
    image_path: /assets/images/graphicsCaptures/arap/peter.gif
  - url: /assets/images/graphicsCaptures/arap/tetrahedron.gif
    image_path: /assets/images/graphicsCaptures/arap/tetrahedron.gif
---
  <!-- overlay_color: "#000" -->
  <!-- overlay_filter: "0.8" -->
  <!-- overlay_image: /assets/images/graphicsCaptures/arap/sphere.png -->

{% include gallery %}

I spent a week implementing this [paper](https://igl.ethz.ch/projects/ARAP/arap_web.pdf) from the Eurgraphics Symposium on Geometry Processing in C++ and OpenGL.
The goal is to be able to transform meshes while keeping deformations as rigid (so as close to the original mesh) as possible.
Users can anchor certain vertices in place, and move others with the mesh responding to the changes in realtime.

{% include gallery id="gallery2"%}