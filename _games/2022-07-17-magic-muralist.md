---
image:
  thumbnail: /assets/images/gameCaptures/magic-muralist/icon.gif
sidebar:
    image: "/assets/images/gameCaptures/magic-muralist/painting5.png"
    text: >-
        - Prototype main mechanic of blitting particle collisions 
        onto a render texture

        - Implement shader to draw colored texture over original painting

        - Developed quest and conversation system

        - Designed and programmed system for evaluating how close a painting is 
        to desired colors by a least squared error approach

        - Implement sounds with FMOD
    team: 3
    tools: Unity, FMOD Studio
    duration: 3 days
    platforms: WebGL, Windows, Mac
    links:
      - title: "Itch"
        url: "https://valkoy.itch.io/magic-muralist"
        icon: "fab fa-gamepad fa"
      - title: "Github"
        url: "https://github.com/Thuleanx/GMTK2022/tree/main/GMTK22/Assets/Scripts"
        icon: "fa fa-github-alt"
permalink: /games/magic-muralist/
no_masthead: true

gallery:
  - url: /assets/images/gameCaptures/magic-muralist/evaluation.gif
    image_path: /assets/images/gameCaptures/magic-muralist/evaluation.gif
  - url: /assets/images/gameCaptures/magic-muralist/painting.gif
    image_path: /assets/images/gameCaptures/magic-muralist/painting.gif
  - url: /assets/images/gameCaptures/magic-muralist/painting5.gif
    image_path: /assets/images/gameCaptures/magic-muralist/painting5.gif

gallery2:
  - url: /assets/images/gameCaptures/magic-muralist/FrancisRequestZoomed.png
    image_path: /assets/images/gameCaptures/magic-muralist/FrancisRequestZoomed.png
  - url: /assets/images/gameCaptures/magic-muralist/FrancisRequestRequest.gif
    image_path: /assets/images/gameCaptures/magic-muralist/FrancisRequest.gif

gallery3:
  - url: /assets/images/gameCaptures/magic-muralist/hop.gif
    image_path: /assets/images/gameCaptures/magic-muralist/hop.gif
  - url: /assets/images/gameCaptures/magic-muralist/reques1.gif
    image_path: /assets/images/gameCaptures/magic-muralist/reques1.gif
  - url: /assets/images/gameCaptures/magic-muralist/request2.gif
    image_path: /assets/images/gameCaptures/magic-muralist/request2.gif
  - url: /assets/images/gameCaptures/magic-muralist/request3.gif
    image_path: /assets/images/gameCaptures/magic-muralist/request3.gif
  - url: /assets/images/gameCaptures/magic-muralist/request4.gif
    image_path: /assets/images/gameCaptures/magic-muralist/request4.gif
  - url: /assets/images/gameCaptures/magic-muralist/requestSO.png
    image_path: /assets/images/gameCaptures/magic-muralist/requestSOCloseup3.png
---
  <!-- overlay_color: "#000" -->
  <!-- overlay_filter: "0.1" -->
  <!-- overlay_image: /assets/images/gameCaptures/magic-muralist/painting5.png -->

Magic Muralist is a 2.5D Drawing Game for PC and Mac, developed in Unity as a 3-day game jam project.
I was responsible for all technical implementation, and worked closely alongside two artists.

{% include gallery %}
{% include figure image_path="/assets/images/gameCaptures/magic-muralist/gameplay.gif" alt="gameplay image" %}

For the painting mechanic, I made the canvas register particle collisions, 
and blit the hit onto a render texture. 
This render texture was displayed and used to compare against a reference painting.

{% include gallery id="gallery2" %}
{% include figure image_path="/assets/images/gameCaptures/magic-muralist/FrancisRequestCode.png" alt="gameplay image" %}

I used Yarn Spinner, a node-based dialogue system, to handle the cutscenes and NPC interactions.

{% include gallery id="gallery3" %}

Painting requests in the game are modeled as scriptable objects that reference the 
Yarn nodes so new scenarios can be added without additional programming. 
Additionally, I added a hopping animation using DoTween as NPCs enter.
