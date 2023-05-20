---
title: "Magic Muralist"
excerpt: "2.5 Magic Painting Game"
header:
  overlay_color: "#000"
  overlay_filter: "0.1"
  overlay_image: /assets/images/gameCaptures/magic-muralist/painting5.png
  teaser: /assets/images/gameCaptures/magic-muralist/icon.gif
sidebar:
  - title: "Role"
    image: "/assets/images/gameCaptures/magic-muralist/logo.png"
    text: "Sole Programmer"
  - title: "Tools"
    text: "Unity, FMOD Studio, Aseprite"
  - title: "Responsiblities"
    text: >-
        Develop, prototype, and implement gameplay systems.
        This includes dialogue, drawing mechanic, drawing request encounters, and sound integration.
  - title: "Links"
    text: >-
        [Itch.io](https://valkoy.itch.io/magic-muralist) /
        [Repository](https://github.com/Thuleanx/GMTK2022/tree/main/GMTK22/Assets/Scripts)

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
