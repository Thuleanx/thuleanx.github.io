---
title: "Phi"
excerpt: "2D Platformer"
header:
  teaser: /assets/images/gameCaptures/phi/phi2.gif
sidebar:
  - title: "Links"
    image: "/assets/images/gameCaptures/phi/cover.png"
    text: >-
        [Itch.io](https://thuleanx.itch.io/phi)
  - title: "Responsiblities"
    text: >-
        - Design and program state machine character, raycast-based movement, and level progression.

        - Produce art assets in aseprite, and create particles for dust and watermelon collection.

        - Compose 2 music tracks for the main theme and end level.
        
  - title: "Tools"
    text: "Unity, FMOD Studio, Beepbox, Aseprite"

display:
  - url: /assets/images/gameCaptures/phi/phi1.gif
    image_path: /assets/images/gameCaptures/phi/phi1.gif
  - url: /assets/images/gameCaptures/phi/phi2.gif
    image_path: /assets/images/gameCaptures/phi/phi2.gif
  - url: /assets/images/gameCaptures/phi/phi3.gif
    image_path: /assets/images/gameCaptures/phi/phi3.gif

mechanics:
  - url: /assets/images/gameCaptures/phi/raycast.png
    image_path: /assets/images/gameCaptures/phi/raycast.png
  - url: /assets/images/gameCaptures/phi/ledgeGrab.gif
    image_path: /assets/images/gameCaptures/phi/ledgeGrab.gif

juice:
  - url: /assets/images/gameCaptures/phi/phi2.gif
    image_path: /assets/images/gameCaptures/phi/phi2.gif
  - url: /assets/images/gameCaptures/phi/phi3.gif
    image_path: /assets/images/gameCaptures/phi/phi3.gif

assets:
  - url: /assets/images/gameCaptures/phi/asset_bench.png
    image_path: /assets/images/gameCaptures/phi/asset_bench.png
  - url: /assets/images/gameCaptures/phi/asset_house.png
    image_path: /assets/images/gameCaptures/phi/asset_house.png
  - url: /assets/images/gameCaptures/phi/asset_tilemap.png
    image_path: /assets/images/gameCaptures/phi/asset_tilemap.png

---

Phi is a solo project I created for the Weekly Game Jam 204, and won 1st out of 31 entries.
For the project, I wanted to touch on all aspects of creating a small but unique platformer,
including programming physics, creating art assets, and composing music.

{% include gallery id="display"%}
{% include figure image_path="/assets/images/gameCaptures/phi/banner.png" alt="gameplay image" %}

Phi's character controller was created with a state machine inspired by Celeste's player controller. 
I used raycasting for collision detection to precisely interact with the umbrella and implement ledge correction.

{% include gallery id="mechanics"%}

To emphasize her bounciness, I added procedural squash and stretch and particle effects to both Phi and the umbrella.

{% include gallery id="juice"%}

{% include gallery id="assets" caption="All pixel art assets are made in aseprite."%}
