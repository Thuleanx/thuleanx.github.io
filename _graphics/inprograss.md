---
title: "Inprograss"
excerpt: "Interactive Procedural Grass"
header:
  teaser: /assets/images/graphicsCaptures/inprograss/showcase.gif
sidebar:
  - title: "Role"
    image: "/assets/images/graphicsCaptures/inprograss/palette4alt.png"
    text: "Programmer"
  - title: "Tools"
    text: "C++, OpenGL, Qt Creator"
  - title: "Responsiblities"
    text: >-
        Setup rendering pipeline, implement procedural grass system, and create editor tools to customize
        the grass's features.
  - title: "Links"
    text: >-
        [Repository](https://github.com/Thuleanx/Grass)
---
  <!-- overlay_color: "#000" -->
  <!-- overlay_filter: "0.1" -->
  <!-- overlay_image: /assets/images/graphicsCaptures/inprograss/banner.png -->

Inprograss is a realtime grass generator I created as my week-long final project for Brown's computer graphics class.
All the grass are generated using a compute shader and lives entirely on the GPU, which allows for 10 million unique blades of grass to be 
generated and rendered without dips in frame rate.

The grass blades respond to wind and any object walking around the environment, and support an arbitrary amount of interactible 
object.

{% include video id="4m8hVsHC-9Q" provider="youtube" %}

Under the hood, a packed velocity-displacement texture stores how much the grass should bend, and updates each frame 
similar to a spring mass damper system. Agents write a displacement mask to this texture to simulate interacting with the grass.
