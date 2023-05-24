---
title: "Override"
excerpt: "Twin-stick shooter"
header:
  teaser: /assets/images/gameCaptures/override/overrideAnimation.gif
sidebar:
  - title: "Links"
    image: "/assets/images/gameCaptures/override/logo.png"
    text: >-
        [Itch.io](https://rainydey.itch.io/override)
  - title: "Role"
    text: "Programmer, VFX Artist"
  - title: "Responsiblities"
    text: >-
        - Design and implement ship variants system, player movement and firing, as well as override system.

        - Write shaders, create particle systems, polish UI, and implement audio.
  - title: "Tools"
    text: "Unity, FMOD Studio"

setup:
  - url: /assets/images/gameCaptures/override/singleGunning.gif
    image_path: /assets/images/gameCaptures/override/singleGunning.gif
  - url: /assets/images/gameCaptures/override/title.gif
    image_path: /assets/images/gameCaptures/override/title.gif
  - url: /assets/images/gameCaptures/override/blastShotsCropped.gif
    image_path: /assets/images/gameCaptures/override/blastShotsCropped.gif

overrideProgression:
  - url: /assets/images/gameCaptures/override/overrideDraft.gif
    image_path: /assets/images/gameCaptures/override/overrideDraft.gif
  - url: /assets/images/gameCaptures/override/better.gif
    image_path: /assets/images/gameCaptures/override/better.gif
  - url: /assets/images/gameCaptures/override/betterwithnoisentrail.gif
    image_path: /assets/images/gameCaptures/override/betterwithnoisentrail.gif
  - url: /assets/images/gameCaptures/override/finalenight.gif
    image_path: /assets/images/gameCaptures/override/finalenight.gif
  - url: /assets/images/gameCaptures/override/hijack.gif
    image_path: /assets/images/gameCaptures/override/hijack.gif
  - url: /assets/images/gameCaptures/override/overrideAnimation.gif
    image_path: /assets/images/gameCaptures/override/overrideAnimation.gif

ui:
  - url: /assets/images/gameCaptures/override/gameOver.gif
    image_path: /assets/images/gameCaptures/override/gameOver.gif
  - url: /assets/images/gameCaptures/override/instructions.gif
    image_path: /assets/images/gameCaptures/override/instructions.gif
  - url: /assets/images/gameCaptures/override/credits.gif
    image_path: /assets/images/gameCaptures/override/credits.gif
  - url: /assets/images/gameCaptures/override/title.gif
    image_path: /assets/images/gameCaptures/override/title.gif
  - url: /assets/images/gameCaptures/override/helth.gif
    image_path: /assets/images/gameCaptures/override/helth.gif
  - url: /assets/images/gameCaptures/override/paused.gif
    image_path: /assets/images/gameCaptures/override/paused.gif

---

I was a programmer and VFX artist on this semester long project involving a team of more than 20 artists and programmers. 
My main focus was on particle effects, shaders, UI implementation and polish, and audio implementation.

{% include gallery id="setup"%}

I started with the artists' sketches, recreated them in the engine using particle systems and iterated with artists. 

{% include gallery id="overrideProgression" caption="Progression from artist's draft to effect implemented in game."%}

{% include embed-audio.html src="/assets/images/gameCaptures/override/override.mp3" %}{: .align-right}
I layered different sound assets using FMOD to create the sound effects. 
The pitches of repetitive sounds were modulated and I applied a lo-pass filter on the entire music channel when the player is hit for more of an impact.

For implementation of different UI elements, I made use of post processing, particle effects, and animating the text mesh to create dynamism in these otherwise static screens.

{% include gallery id="ui"%}


