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
permalink: "/graphicsHome"

feature_row:
  - image_path: /assets/images/graphicsCaptures/inprograss/showcase.gif
    title: "Procedural Grass"
    excerpt: >-
        <span class="btn btn--danger">C++</span> <span class="btn btn--success">OpenGL</span> <br>

        GPU-based Interactive Procedural Grass using compute shader.
    url: "/graphics/inprograss"
    btn_label: "Read More"
    btn_class: "btn--inverse"
  - image_path: /assets/images/graphicsCaptures/saga/starCollection.gif
    title: "Saga Game Engine"
    excerpt: >-
        <span class="btn btn--danger">C++</span> <span class="btn btn--success">OpenGL</span> <span class="btn btn--primary">gamedev</span> <br>
        
        3D Entity-Component-System Game Engine made from scratch over half a year.
    url: "/graphics/saga"
    btn_label: "Read More"
    btn_class: "btn--inverse"
  - image_path: /assets/images/graphicsCaptures/waterwavelet/waterWaveletIntroduce.gif
    title: "Water Surface Wavelet"
    excerpt: >-
        <span class="btn btn--danger">C++</span> <span class="btn btn--success">OpenGL</span> <br>

        Realtime water surface simulation with boundary reflection and localized interactions.
    url: "/graphics/waves"
    btn_label: "Read More"
    btn_class: "btn--inverse"
---

{% include feature_row %}
