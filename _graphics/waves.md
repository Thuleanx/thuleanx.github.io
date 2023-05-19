---
title: "Water Wavelets"
excerpt: "Ocean Surface Simulation"
header:
  overlay_color: "#000"
  overlay_filter: "0.1"
  overlay_image: /assets/images/graphicsCaptures/waterwavelet/ambientWaves.png
  teaser: /assets/images/graphicsCaptures/waterwavelet/waterWaveletIntroduce.gif
sidebar:
  - title: "Role"
    image: "/assets/images/graphicsCaptures/waterwavelet/topDownWaves.png"
    text: "Simulation Programmer"
  - title: "Tools"
    text: "C++, OpenGL, ImGui"
  - title: "Responsiblities"
    text: >-
        Design and program simulation system on the GPU, visualizer for ease of debugging, as well as create and load terrain
        model from blender.
  - title: "Links"
    text: >-
        [Repository](https://github.com/LoganDooley/CS2240FinalProject)

gallery:
  - url: /assets/images/graphicsCaptures/waterwavelet/waterWaveletIntroduce.gif
    image_path: /assets/images/graphicsCaptures/waterwavelet/waterWaveletIntroduce.gif
  - url: /assets/images/graphicsCaptures/waterwavelet/boundaryReflection.gif
    image_path: /assets/images/graphicsCaptures/waterwavelet/boundaryReflection.gif
  - url: /assets/images/graphicsCaptures/waterwavelet/Ambient.gif
    image_path: /assets/images/graphicsCaptures/waterwavelet/Ambient.gif

gallery2:
  - url: /assets/images/graphicsCaptures/waterwavelet/visualizationGrid.png
    image_path: /assets/images/graphicsCaptures/waterwavelet/visualizationGrid.png
    title: "Visualization grid of the 8 simulation textures."
  - url: /assets/images/graphicsCaptures/waterwavelet/normalData.png
    image_path: /assets/images/graphicsCaptures/waterwavelet/normalData.png
    title: "Normal data of the boundary / terrain"
  - url: /assets/images/graphicsCaptures/waterwavelet/reflectionVisualization.png
    image_path: /assets/images/graphicsCaptures/waterwavelet/reflectionVisualization.png
    title: "Reflection seen in the simulation visualizer."
---

As a final project for my graduate graphics class, my team implemented a [Water Surface Wavelet from SIGGRAPH 2018](https://dl.acm.org/doi/pdf/10.1145/3197517.3201336).
Unlike traditional FFT-based implementations of water surface, the paper's wavelet-based approach 
allows for more localized and dynamic effects such as boundary reflection, spatially varying wind, and interactions with
moving solids.

{% include gallery %}
{% include figure image_path="/assets/images/graphicsCaptures/waterwavelet/advectionCutOffByDiffusion.gif" %}

My work primarily focused on architecturing and programming the simulation to run on the GPU in realtime.
Specifically, I compressed the 4D wave amplitude simulation table into 8 2D textures, one for each wavedirection, 
and packs the amplitude data of a certain wavenumber into one of the 4 color channels.
I then programmed a glsl fragment shader to perform the simulation step, and optimized by precomputing 
constants on the CPU.

Below are visualization tools that I wrote to display the simulation textures.

{% include gallery id="gallery2" %}


