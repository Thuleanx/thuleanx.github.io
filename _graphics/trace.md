---
title: "Path Tracing"
excerpt: "Physically Based Rendering"
header:
  overlay_color: "#000"
  overlay_filter: "0.0"
  overlay_image: /assets/images/graphicsCaptures/trace/coriginal_100pp_dl_importance.png
  teaser: /assets/images/graphicsCaptures/trace/csphere_100pp_dl_importance_stratified_dof_169.png
sidebar:
  - title: "Tools"
    image: "/assets/images/graphicsCaptures/trace/boat_100pp_dl_importance_169.png"
    text: "C++, Eigen"
  - title: "Responsiblities"
    text: >-
        Design and implement path tracer along with direct lighting and importance sampling optimizations.

gallery:
  - url: /assets/images/graphicsCaptures/trace/coriginal_100pp_dl_importance.png
    image_path: /assets/images/graphicsCaptures/trace/coriginal_100pp_dl_importance.png
  - url: /assets/images/graphicsCaptures/trace/csphere_100pp_dl_importance_attenuated.png
    image_path: /assets/images/graphicsCaptures/trace/csphere_100pp_dl_importance_attenuated.png
  - url: /assets/images/graphicsCaptures/trace/boat_100pp_dl_importance.png
    image_path: /assets/images/graphicsCaptures/trace/boat_100pp_dl_importance.png

gallery2:
  - url: /assets/images/graphicsCaptures/trace/cglossy_100pp_dl_importance.png
    image_path: /assets/images/graphicsCaptures/trace/cglossy_100pp_dl_importance.png
  - url: /assets/images/graphicsCaptures/trace/cmirror_100pp_dl_importance.png
    image_path: /assets/images/graphicsCaptures/trace/cmirror_100pp_dl_importance.png
  - url: /assets/images/graphicsCaptures/trace/csphere_100pp_dl_importance.png
    image_path: /assets/images/graphicsCaptures/trace/csphere_100pp_dl_importance.png

gallery3:
  - url: /assets/images/graphicsCaptures/trace/coriginal_100pp_noOpt.png
    image_path: /assets/images/graphicsCaptures/trace/coriginal_100pp_noOpt.png
  - url: /assets/images/graphicsCaptures/trace/coriginal_100pp_dl.png
    image_path: /assets/images/graphicsCaptures/trace/coriginal_100pp_dl.png
    
gallery4:
  - url: /assets/images/graphicsCaptures/trace/cglossy_10pp_dl.png
    image_path: /assets/images/graphicsCaptures/trace/cglossy_10pp_dl.png
  - url: /assets/images/graphicsCaptures/trace/cglossy_10pp_dl_importance.png
    image_path: /assets/images/graphicsCaptures/trace/cglossy_10pp_dl_importance.png

gallery5:
  - url: /assets/images/graphicsCaptures/trace/cglossy_100pp_dl_importance_stratified_dof.png
    image_path: /assets/images/graphicsCaptures/trace/cglossy_100pp_dl_importance_stratified_dof.png
  - url: /assets/images/graphicsCaptures/trace/csphere_100pp_dl_importance_stratified_dof.png
    image_path: /assets/images/graphicsCaptures/trace/csphere_100pp_dl_importance_stratified_dof.png
  - url: /assets/images/graphicsCaptures/trace/cwater_1000pp_dl_importance.png
    image_path: /assets/images/graphicsCaptures/trace/cwater_1000pp_dl_importance.png

---

As a 2 week project in Brown's graduate graphics class, I implemented Path Tracing in C++ and Eigen. 
This method is physically accurate unlike a regular ray tracer, and involves tracing light paths from the camera and surfaces
to perform Monte-Carlo integration for a surface's luminescence.

{% include gallery %}

The program supports diffuse, glossy, mirrored, and refractive materials. 
Since path tracing is expensive, I optimized rendering time by I using OpenMP to 
parallelize parts of the computation as well as a Bounding Volume Hierarchy to speed up ray intersection.

{% include gallery id="gallery2" caption="Renders with 100 samples per pixel taking 5-10 seconds."%}

For lower variance in our light sampling, I splitted integrating for direct and indirect lighting. 
For direct, the sensible thing is to shoot rays directly at a random point on a randomly sampled light source, 
whereas for indirect lighting, we recursively trace paths. 
The result is a much smoother render with the same sample per pixel count.

{% include gallery id="gallery3" caption="Renders with 100 samples per pixel with and without direct lighting optimization."%}

For sampling light bounces, I sampled porpotional to the BRDF (Bidirectional reflectance distribution function) instead of uniformly over the hemisphere tangent to the surface.
This is essential to get good renders of specular materials.

{% include gallery id="gallery4" caption="Renders with only 10 samples per pixel with and without importance sampling."%}

Lastly, I threw in depth of field and attenuated the refracted light for more realistic looking renders.

{% include gallery id="gallery5"%}

