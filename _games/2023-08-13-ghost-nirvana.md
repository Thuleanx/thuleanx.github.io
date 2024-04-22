---
layout: post
title: "Ghost Nirvana"
image: 
    thumbnail: /assets/images/gameCaptures/ghost-nirvana/many_enemies.gif
sidebar:
  - text: >-

        **Jam Project**<br>
        **Team:** 2 <br>
        **Tools:** Unity, FMOD<br>
        **Duration:** 6 weeks<br>
        **Platforms:** WebGL, Windows, Mac<br>

        <hr>
    image: /assets/images/gameCaptures/ghost-nirvana/title.png
  - text: >-
        - **Object pooling system** to handle hundreds of bullets running stably on WebGL

        - **Decoupled combat, UI, and upgrade system** with the MVVM pattern using scriptable objects

        - AI with Finite State Machine

        - FMOD Audio mixing and concurrency settings

        - **Online leaderboard system**

        - UI tweening

        <hr>
    links:
      - title: "Itch"
        url: "https://thuleanx.itch.io/ghost-nirvana"
        icon: "fab fa-gamepad fa"
      - title: "Github"
        url: "https://github.com/Thuleanx/GhostNirvana"
        icon: "fab fa-fw fa-github"
permalink: /games/ghost-nirvana/
no_masthead: true

gallery1:
  - image_path: /assets/images/gameCaptures/ghost-nirvana/candy.gif
  - image_path: /assets/images/gameCaptures/ghost-nirvana/levelup.gif

gallery2:
  - image_path: /assets/images/gameCaptures/ghost-nirvana/reload.gif
  - image_path: /assets/images/gameCaptures/ghost-nirvana/boss_appear.gif
  - image_path: /assets/images/gameCaptures/ghost-nirvana/saltsplosion.gif

gallery3: 
  - image_path: /assets/images/gameCaptures/ghost-nirvana/many_enemies.gif

---

Ghost Nirvana is a 3D roguelike bullet heaven I developed alongside [Allison Yeh](https://allisonkyeh.com/) for A Game By Its Cover 2023, a 6 week game jam.
You play as a part-time worker for a salt company whose job is exorcising ghosts haunting abandoned appliances.

{% include gallery id="gallery1" %}
{% include gallery id="gallery2" %}
{% include gallery id="gallery3" %}

<!-- ## Code Snippets -->

<!-- {::options parse_block_html="true" /} -->

<!-- <details><summary markdown="span">Decoupled combat, UI, and upgrade system</summary> -->

<!-- The Model View View-Model pattern is famous in software for decoupling front end --> 
<!-- UI and the logic that updates said UI. -->
<!-- The core idea is that systems communicates data through a View-Model, which is just a --> 
<!-- fancy name for a collection of data with delegates that fires when specific pieces of the --> 
<!-- data updates. -->

<!-- Inspired by [a Unity article on scriptable objects](https://unity.com/how-to/architect-game-code-scriptable-objects), --> 
<!-- I made a similar system in Unity for handling information that Ghost Nirvana's combat, --> 
<!-- UI, AI, and upgrade systems use. -->

<!-- ```csharp -->

<!-- ``` -->

<!-- </details> -->

<!-- {::options parse_block_html="false" /} -->


----

