---
title: "Saga Engine"
excerpt: "3D game engine"
header:
  overlay_color: "#000"
  overlay_filter: "0.1"
  overlay_image: /assets/images/gameCaptures/saga/post processing.png
  teaser: /assets/images/gameCaptures/saga/starCollection.gif
sidebar:
  - title: "Role"
    image: "/assets/images/gameCaptures/portal-knight/post processing.png"
    text: "Programmer"
  - title: "Tools"
    text: "C++, FMOD Studio, OpenGL"
  - title: "Responsiblities"
    text: >-
        Architecture, program, and document the engine.
        Created sound effects in FMOD Studio and models in Blender as assets in the game engine demo.
  - title: "Links"
    text: >-
        [Repository](https://github.com/Thuleanx/SagaEngine) /
        [Documentation](https://thuleanx.vercel.app/saga/index.html)

gallery:
  - url: /assets/images/gameCaptures/saga/dof.png
    image_path: /assets/images/gameCaptures/saga/dof.png
    title: "depth of field"
  - url: /assets/images/gameCaptures/saga/shadow.png
    image_path: /assets/images/gameCaptures/saga/shadow.png
    title: "shadow mapping"
  - url: /assets/images/gameCaptures/saga/dense130050TriPlane.png
    image_path: /assets/images/gameCaptures/saga/dense130050TriPlane.png
    title: "dense 100000+ triangles plane"

gallery2:
  - url: /assets/images/gameCaptures/saga/gammaCorrection.png
    image_path: /assets/images/gameCaptures/saga/gammaCorrection.png
    title: "gamma correction"
  - url: /assets/images/gameCaptures/saga/imgui_integration.png
    image_path: /assets/images/gameCaptures/saga/imgui_integration.png
    title: "adjustable fog / other post processing settings with ImGui"
  - url: /assets/images/gameCaptures/saga/navmesh.png
    image_path: /assets/images/gameCaptures/saga/navmesh.png
    title: "NavMesh agents with behaviour tree to follow player."

gallery3:
  - url: /assets/images/gameCaptures/saga/collection.png
    image_path: /assets/images/gameCaptures/saga/collection.png
    title: "collection"
  - url: /assets/images/gameCaptures/saga/saturation.png
    image_path: /assets/images/gameCaptures/saga/saturation.png
    title: "Saturation adjustment"
  - url: /assets/images/gameCaptures/saga/whiteBalance.png
    image_path: /assets/images/gameCaptures/saga/whiteBalance.png
    title: "Applying white balance (tint / temperature)."
---

Saga is an Entity-Component-Systems based game engine made as part of Brown's 3D Game Engine class.

{% include figure image_path="/assets/images/gameCaptures/saga/starCollection.gif" alt="gameplay image" %}

Its features include:
- Continuous collision detection between ellipsoids and arbitrary meshes, optimized with a boundary volume hierarchy datastructure.
Accurate and smooth collisions with 100,000+ triangles even with the post processing stack enabled.
- Navigation mesh support as well as a behaviour tree system for writing AI.
- Shadow Mapping for directional light with PCF that automatically adjusts to the view frustum.
- A post processing stack, with support for bloom, fog, depth of field, and color adjustment 
effects such as ACES tone mapping, contrast, saturation, or white balance.
- FMOD Studio integration that allows for 3D sounds as well as parameter setting for adaptive audio.
- A particle system capable of rendering particles as camera-facing quads and 3D meshes, and respond accurately to FOG and other depth-based post processing effects.
- ImGui integration for quick and easy editor UI.
- Documentation for engine methods viewable [online](https://thuleanx.vercel.app/saga/index.html).

{% include gallery %}
{% include gallery id="gallery2" %}
{% include gallery id="gallery3" %}

