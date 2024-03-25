---
image:
  thumbnail: /assets/images/gameCaptures/safe-haven/climax2.gif
sidebar:
  - title: "Links"
    image: "/assets/images/gameCaptures/safe-haven/proceduralHair.gif"
    text: >-
        [Itch.io](https://dylandavis.itch.io/save-haven) /
        [Repository](https://github.com/Thuleanx/NarrativeGameJam3/tree/main/HorrorNarrative/Assets/All/Programming)
  - title: "Role"
    text: "Sole Technical Developer, Artist"
  - title: "Responsiblities"
    text: >-
        - Design and implement core game mechanics. 

        - Produce all art assets in Aseprite, Krita, and Blender.

        - Chart the beatmap and produce tools for bullet pattern creation.
  - title: "Tools"
    text: "Unity, FMOD Studio, Aseprite, Krita"
permalink: /games/safe-haven/
no_masthead: true

gallery:
  - url: /assets/images/gameCaptures/safe-haven/dialogue.png
    image_path: /assets/images/gameCaptures/safe-haven/dialogue.png
  - url: /assets/images/gameCaptures/safe-haven/climax.gif
    image_path: /assets/images/gameCaptures/safe-haven/climax.gif
  - url: /assets/images/gameCaptures/safe-haven/climax2.gif
    image_path: /assets/images/gameCaptures/safe-haven/climax2.gif

gallery2:
  - url: /assets/images/gameCaptures/safe-haven/pat1.gif
    image_path: /assets/images/gameCaptures/safe-haven/pat1.gif
  - url: /assets/images/gameCaptures/safe-haven/pat2.gif
    image_path: /assets/images/gameCaptures/safe-haven/pat2.gif
  - url: /assets/images/gameCaptures/safe-haven/pat3.gif
    image_path: /assets/images/gameCaptures/safe-haven/pat3.gif
  - url: /assets/images/gameCaptures/safe-haven/pat1Graph.png
    image_path: /assets/images/gameCaptures/safe-haven/pat1Graph.png
  - url: /assets/images/gameCaptures/safe-haven/pat2Graph.png
    image_path: /assets/images/gameCaptures/safe-haven/pat2Graph.png
  - url: /assets/images/gameCaptures/safe-haven/pat3Graph.png
    image_path: /assets/images/gameCaptures/safe-haven/pat3Graph.png

demonLook:
  - url: /assets/images/gameCaptures/safe-haven/proceduralHairMove.gif
    image_path: /assets/images/gameCaptures/safe-haven/proceduralHairMove.gif
  - url: /assets/images/gameCaptures/safe-haven/smear.gif
    image_path: /assets/images/gameCaptures/safe-haven/smear.gif
  - url: /assets/images/gameCaptures/safe-haven/vfxgraph.gif
    image_path: /assets/images/gameCaptures/safe-haven/vfxgraph.gif

yarn:
  - url: /assets/images/gameCaptures/safe-haven/dialogueCode.png
    image_path: /assets/images/gameCaptures/safe-haven/dialogueCode.png
  - url: /assets/images/gameCaptures/safe-haven/opening scene.gif
    image_path: /assets/images/gameCaptures/safe-haven/opening scene.gif

---

Safe Haven was creatd in 18 days as a submission to [OST Jam Volume 6](https://itch.io/jam/ost-jam-v6).
I was the sole technical developer and artist, and collaborated with another developer who did writing and sound effects.

{% include figure image_path="/assets/images/gameCaptures/safe-haven/crispGameplay.gif" alt="gameplay image" %}
{% include gallery %}

Using the xNode package, I created a graphical tool in Unity for quickly generating complex bullet patterns. 
I also added object pooling so barrages of bullets won't substantially affect performance.

{% include gallery id="gallery2"%}

The demon's look was achieved using a combination of Unity's VFX Graph, smear + fresnel shader, and procedural animation for hair. 
The eyes and bodies each have their own state machine that cycles between idle and various attacks.

{% include gallery id="demonLook"%}

Finally, I implemented the dialogue for the game and as well as sequencing logic with Yarn Spinner.
FMOD was used for sound effects and to modulate the pitches of repetitive sounds.

{% include gallery id="yarn"%}
