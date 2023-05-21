---
title: "Realtime"
excerpt: "OpenGL Realtime Renderer"
header:
  overlay_color: "#000"
  overlay_filter: "0.0"
  overlay_image: /assets/images/graphicsCaptures/realtime/chess.png
  teaser: /assets/images/graphicsCaptures/realtime/brightChessSSAO.png
sidebar:
  - title: "Tools"
    image: "/assets/images/graphicsCaptures/realtime/chess.png"
    text: "C++, Qt Creator, OpenGL"
  - title: "Responsiblities"
    text: >-
        Implement object loading, tesselation, and shading. 
        Write glsl shaders for lighting and screen space ambient occlusion.

gallery:
  - url: /assets/images/graphicsCaptures/realtime/phongTotal.png
    image_path: /assets/images/graphicsCaptures/realtime/phongTotal.png
  - url: /assets/images/graphicsCaptures/realtime/recursiveSphere.png
    image_path: /assets/images/graphicsCaptures/realtime/recursiveSphere.png
  - url: /assets/images/graphicsCaptures/realtime/snowman.png
    image_path: /assets/images/graphicsCaptures/realtime/snowman.png

gallery2:
  - url: /assets/images/graphicsCaptures/realtime/classroomSSAO.png
    image_path: /assets/images/graphicsCaptures/realtime/classroomSSAO.png
  - url: /assets/images/graphicsCaptures/realtime/tesselation.gif
    image_path: /assets/images/graphicsCaptures/realtime/tesselation.gif
  - url: /assets/images/graphicsCaptures/realtime/distanceLOD.gif
    image_path: /assets/images/graphicsCaptures/realtime/distanceLOD.gif
  - url: /assets/images/graphicsCaptures/realtime/brightChessSSAO.png
    image_path: /assets/images/graphicsCaptures/realtime/brightChessSSAO.png
  - url: /assets/images/graphicsCaptures/realtime/brightChess.png
    image_path: /assets/images/graphicsCaptures/realtime/brightChess.png
  - url: /assets/images/graphicsCaptures/realtime/sharpen.png
    image_path: /assets/images/graphicsCaptures/realtime/sharpen.png

---

Realtime is my month-long project for Brown's computer graphics class. 
I implemented the rendering pipeline that loads and render a scene file with the GUI to interactively adjust the tesselation
parameters.
This project helped me learn a lot about rendering pipeline concepts and how post processing is done in a 3D realtime engine.

{% include gallery %}

For lighting, I wrote a glsl shader following the phong lighting model, and supports up to 8 directional, point, and spot lights.
I additionally implemented optimization via distance-based Level of Detail, and post processing shaders (grayscale, sharpen, and screen space ambient occlusion).

{% include gallery id="gallery2"%}
