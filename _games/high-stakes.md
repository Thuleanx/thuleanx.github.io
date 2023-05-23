---
title: "High Stakes"
excerpt: "2.5D turn-based puzzle game"
header:
  teaser: /assets/images/gameCaptures/high-stakes/round01.gif
sidebar:
  - title: "Links"
    image: "/assets/images/gameCaptures/high-stakes/title.png"
    text: >-
        [Itch.io](https://brownrisdgames.itch.io/highstakes) /
        [Repository](https://github.com/PolyMarsDev/High-Stakes)
  - title: "Role"
    text: "Lead Programmer"
  - title: "Responsiblities"
    text: >-
        Develop turn-based movement system, camera panning, UI, audio, and animation implementation.
  - title: "Tools"
    text: "Unity, FMOD Studio"

gallery:
  - url: /assets/images/gameCaptures/high-stakes/camRotate.gif
    image_path: /assets/images/gameCaptures/high-stakes/camRotate.gif
  - url: /assets/images/gameCaptures/high-stakes/camRotateWithChar.gif
    image_path: /assets/images/gameCaptures/high-stakes/camRotateWithChar.gif

gallery2:
  - url: /assets/images/gameCaptures/high-stakes/test01.png
    image_path: /assets/images/gameCaptures/high-stakes/test01.png
    title: "Basic movement testing scene"
  - url: /assets/images/gameCaptures/high-stakes/test02.png
    image_path: /assets/images/gameCaptures/high-stakes/test02.png
    title: "AI testing scene."
  - url: /assets/images/gameCaptures/high-stakes/ai_movement.gif
    image_path: /assets/images/gameCaptures/high-stakes/ai_movement.gif
    title: "AI implemeneted into final game."

gallery3:
  - url: /assets/images/gameCaptures/high-stakes/demo_deathAnimation.gif
    image_path: /assets/images/gameCaptures/high-stakes/demo_deathAnimation.gif
  - url: /assets/images/gameCaptures/high-stakes/demo_keyanimation.gif
    image_path: /assets/images/gameCaptures/high-stakes/demo_keyanimation.gif
  - url: /assets/images/gameCaptures/high-stakes/demo_moveIndicator.gif
    image_path: /assets/images/gameCaptures/high-stakes/demo_moveIndicator.gif

---
  <!-- overlay_color: "#000" -->
  <!-- overlay_filter: "0.1" -->
  <!-- overlay_image: /assets/images/gameCaptures/high-stakes/lookToPlatform.png -->
High Stakes is a 2.5D turn-based, grid-based puzzle game developed in Unity for PC and MacOS.
My focus was programming movement withing the grid, implementing camera movement, and filling gaps in the team such as UI, audio, and animation implementation.

{% include figure image_path="/assets/images/gameCaptures/high-stakes/round01.gif" alt="gameplay image" %}
{% include gallery %}

I also implemented asymptotic averaging to smooth out the camera rotation while keeping it responsive.

{% include gallery id="gallery2"%}

Since the team consisted of programmers unfamiliar with the engine, 
I laid out the grid system and enemy AI so they could be programmed separatedly from any Unity component. 
I also set up test scenes for other programmers.

![image-left](/assets/images/gameCaptures/high-stakes/dragDropLiceCap.gif){: .align-left}
For the designer's convenience, I also made units snap and automatically register to the grid when placed on top of it.

{% include gallery id="gallery3"%}

As polish, I added animation on the key, smooth sprite movement on the grid, a bouncy death animation, and a diamond turn indicator.

