---
layout: post
permalink: /graphics/inprograss/
title: "Inprograss"
excerpt: "Interactive Procedural Grass"
image:
  thumbnail: /assets/images/graphicsCaptures/inprograss/showcase.gif
sidebar:
  - text: >-
        **Personal project**<br>
        **Tools:** C++, OpenGL, Qt Creator<br>
        **Duration:** 1 week<br>
        **Platform:** Windows<br>

        <hr>
    image: "/assets/images/graphicsCaptures/inprograss/palette4alt.png"
  - text: >-
        - GLSL compute shader generates **100,000+ curved grass meshes**

        - GLSL compute shader to draw to a packed velocity / displacement texture
        that governs how much **grass sways**

        - **Post processing FXAA** to remove jagged artifacts on the top of grass blades

        - **3rd person camera controller**

        <hr>
    links:
      - title: "Github"
        url: "https://github.com/Thuleanx/Grass"
        icon: "fab fa-fw fa-github"
no_masthead: true
---
  <!-- overlay_color: "#000" -->
  <!-- overlay_filter: "0.1" -->
  <!-- overlay_image: /assets/images/graphicsCaptures/inprograss/banner.png -->

Inprograss is a realtime grass generator I created as my week-long final project for Brown's computer graphics class.
All the grass are generated using a compute shader and lives entirely on the GPU, which allows for 10 million unique blades of grass to be 
generated and rendered without dips in frame rate.

I've seen others achieved this before, so to take it a step further I also added 
in grass interactivity. The grass blades responds to both wind and displacement 
caused by an arbitrary number of agents moving around in the field.

{% include video id="4m8hVsHC-9Q" provider="youtube" %}

<br>

This is achieved via a packed velocity(RG)-displacement(BA) texture that stores how
much the grass should displace.
Moving agents draw to this texture, and it is then simulated similar to a 
spring-mass-damper system to gradually slow the displacement down to 0.
The result is that for a few second after an agent has moved over a patch
of grass, the grass still "remembers" the agent stepping over it.
