---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: collection
entries_layout: grid
show_excerpts: true

feature_row:
  - title: "Ghost Nirvana"
    excerpt: >-
        3D isometric bullet heaven developed Unity for a 6 weeks

    url: "/games/ghost-nirvana"
    image: 
        thumbnail: /assets/images/gameCaptures/ghost-nirvana/many_enemies.gif
  - title: "DOOMolish"
    excerpt: >-
      Doom clone made with Vulkan, rust, and bevy_ecs for a solo 14 day game jam
    url: "/games/doomolish"
    image: 
        thumbnail: /assets/images/gameCaptures/doomolish/round2.gif
  - title: "Procedural Grass"
    excerpt: >-
      <!-- <span style="pointer-events: none" class="btn btn--danger">C++</span> -->
      <!-- <span style="pointer-events: none" class="btn btn--success">OpenGL</span> -->
      <!-- <br> -->
    
      GPU-based Interactive Procedural Grass using compute shader in C++ and OpenGL.
    url: "/graphics/inprograss"
    image: 
        thumbnail: /assets/images/graphicsCaptures/inprograss/showcase.gif

---

{% include feature_row id="feature_row" %}
