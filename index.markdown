---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

title: "An Nguyen"
layout: splash
<!-- author_profile: true -->
header:
  overlay_color: "#000"
  overlay_filter: "0.5"
  overlay_image: /assets/images/gameCaptures/portal-knight/longFight.gif
excerpt: "Game / Graphics Programmer"

graphics_row:
  - image_path: /assets/images/graphicsCaptures/inprograss/showcase.gif
    title: "Procedural Grass"
    excerpt: >-
        <span style="pointer-events: none" class="btn btn--danger">C++</span>
        <span style="pointer-events: none" class="btn btn--success">OpenGL</span>
        <br>

        GPU-based Interactive Procedural Grass using compute shader.
    url: "/graphics/inprograss"
    btn_label: "Read More"
    btn_class: "btn--inverse"
  - image_path: /assets/images/graphicsCaptures/saga/starCollection.gif
    title: "Saga Game Engine"
    excerpt: >-
        <span style="pointer-events: none" class="btn btn--danger">C++</span>
        <span style="pointer-events: none" class="btn btn--success">OpenGL</span>
        <span style="pointer-events: none" class="btn btn--primary">gamedev</span>
        <br>
        
        3D Entity-Component-System Game Engine made from scratch over half a year.
    url: "/graphics/saga"
    btn_label: "Read More"
    btn_class: "btn--inverse"
  - image_path: /assets/images/graphicsCaptures/waterwavelet/waterWaveletIntroduce.gif
    title: "Water Surface Wavelet"
    excerpt: >-
        <span style="pointer-events: none" class="btn btn--danger">C++</span>
        <span style="pointer-events: none" class="btn btn--success">OpenGL</span>
        <br>

        Realtime water surface simulation with boundary reflection and localized interactions.
    url: "/graphics/waves"
    btn_label: "Read More"
    btn_class: "btn--inverse"

games_row:
  - image_path: /assets/images/gameCaptures/demigod-daycare/b0.gif
    title: "Demigod Daycare"
    excerpt: >-
        <span style="pointer-events: none" class="btn btn--inverse">Unity</span> 
        <span style="pointer-events: none" class="btn btn--success">MassDigi Studio</span>
        <span style="pointer-events: none" class="btn btn--info">Android/IOS</span>
        <br>
        
        Super Auto Pets-inspired Autobattler

        - Turn-based combat system

        - Modular unit creation system

        - JSON and binary save system

        - UI tweening polish and foliage shader

        - Establish coding standards, held code review sessions, and introduce new programmers to Unity.
    url: "/games/demigod-daycare"
    btn_label: "Read More"
    btn_class: "btn--inverse"
  - image_path: /assets/images/gameCaptures/enter/laserChase.gif
    title: "Enter"
    excerpt: >-
        <span style="pointer-events: none" class="btn btn--inverse">Unity</span>
        <span style="pointer-events: none" class="btn btn--danger">C#</span>
        <span style="pointer-events: none" class="btn btn--success">university</span>
        <br>

        2D Puzzle Platformer

        - Raycast-based character controller

        - Laser visuals and code

        - Majority of particle systems

        - Scene transition system

        - Glitch effect with Shader Graph & Custom URP render passes

        - Adaptive audio with FMOD
    url: "/games/enter"
    btn_label: "Read More"
    btn_class: "btn--inverse"
  - image_path: /assets/images/gameCaptures/portal-knight/swordVFX.gif
    title: "Portal Knight"
    excerpt: >-
        <span style="pointer-events: none" class="btn btn--inverse">Unity</span>
        <span style="pointer-events: none" class="btn btn--danger">C#</span>
        <span style="pointer-events: none" class="btn btn--success">game jam</span>
        <br>

        3D isometric hack and slash

        - Statemachine character controller

        - Melee combat system + animation integration

        - AI navigation with NavMesh

        - Camera occlusion system, screenspace outline, and screenwipe

        - Audio integration with FMOD.

        - Portal and death particles with VFX Graph.
    url: "/games/portal-knight"
    btn_label: "Read More"
    btn_class: "btn--inverse"
---

{% include feature_row id="games_row"%}
{% include feature_row id="graphics_row"%}
