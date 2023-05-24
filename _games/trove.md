---
title: "Radioactive Trove"
excerpt: "Atmospheric sidescroller"
header:
  teaser: /assets/images/gameCaptures/trove/battleCropped.gif
sidebar:
  - title: "Links"
    image: "/assets/images/gameCaptures/trove/logo.png"
    text: >-
        [Itch.io](https://valkoy.itch.io/radioactive-trove) /
        [Repository](https://github.com/Thuleanx/einclair/tree/main/Assets/Scripts)
  - title: "Role"
    text: "Programmer, Audio Designer"
  - title: "Responsiblities"
    text: >-
        - Design and implement statemachine enemy AI, combat system, and level progression. 

        - Write post processing effects in Shader Graph and HLSL. 
        Designed and implement particle systems.
        Modified URP lightning pass to get Darkwood vision cone.

        - Implement adaptive 3D audio with proper concurrency stealing.
  - title: "Tools"
    text: "Unity, FMOD Studio"

setup:
  - url: /assets/images/gameCaptures/trove/titleCropped.gif
    image_path: /assets/images/gameCaptures/trove/titleCropped.gif
  - url: /assets/images/gameCaptures/trove/envi2.gif
    image_path: /assets/images/gameCaptures/trove/envi2.gif
  - url: /assets/images/gameCaptures/trove/battleCropped.gif
    image_path: /assets/images/gameCaptures/trove/battleCropped.gif

darkwoodVision:
  - url: /assets/images/gameCaptures/trove/lightningDarkwoodTest.gif
    image_path: /assets/images/gameCaptures/trove/lightningDarkwoodTest.gif
  - url: /assets/images/gameCaptures/trove/shadows.png
    image_path: /assets/images/gameCaptures/trove/shadows.png

postProcessing:
  - url: /assets/images/gameCaptures/trove/noPP.gif
    image_path: /assets/images/gameCaptures/trove/noPP.gif
  - url: /assets/images/gameCaptures/trove/hasPP.gif
    image_path: /assets/images/gameCaptures/trove/hasPP.gif

hammer:
  - url: /assets/images/gameCaptures/trove/slamAttacks.gif
    image_path: /assets/images/gameCaptures/trove/slamAttacks.gif
  - url: /assets/images/gameCaptures/trove/slamSingle.gif
    image_path: /assets/images/gameCaptures/trove/slamSingle.gif

combat:
  - url: /assets/images/gameCaptures/trove/intenseCombat.gif
    image_path: /assets/images/gameCaptures/trove/intenseCombat.gif
  - url: /assets/images/gameCaptures/trove/death.gif
    image_path: /assets/images/gameCaptures/trove/death.gif
  - url: /assets/images/gameCaptures/trove/battle.gif
    image_path: /assets/images/gameCaptures/trove/battle.gif

---

Radioactive trove is a short, atmospheric sidescroller made in 8 days as an entry in the [Deep Sea Game Jam](https://itch.io/jam/dreadxp-dredge-the-depths-jam).
As the sole programmer and audio designer, I was in charge of designing and implementing the core gameplay mechanics.
I also explored how a combination of post processing effects, 
particle systems, and sound effects can convey a dreary atmosphere.

{% include gallery id="setup"%}

I added a Darkwood-esque vision cone by adding a special light channel, and altering the URP lighting pass so that the emitted light affects objects' alpha instead of illuminating them.
I also added shadow casters to objects to create the illusion of a 3D scene.

{% include gallery id="darkwoodVision"%}

For post processing, I applied a tiling noise function to emulate flowing water, and added some bloom and vignette to decrease vision at the edges of the screen. 
As you take damage, the screen cracks and makes vision even more restricted.

{% include gallery id="postProcessing" caption="Comparison with and without post processing."%}

The hammer's impact is accompanied with a shockwave post processing effect and some particles.

{% include gallery id="hammer" %}

To add a visceral feel to combat, I added blood smears, hit particles, and screen shake. 
The sound effects were made to be directional and faintly audible even when enemies are not in sight.

{% include gallery id="combat" %}

