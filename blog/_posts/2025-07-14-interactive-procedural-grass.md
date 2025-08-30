---
layout: page
title: "Interactive Procedural Grass"
categories: graphics shader
image: 
  thumbnail: /assets/images/blogs/grass/grassPreview.gif
---

For the 2025 TCG and Coreblazer game jam, [Allison Yeh](https://allisonkyeh.com/) 
and I made a little wholesome game called Secret Florist about 
a small child collecting flowers, 
crafting bouquets, 
and giving it out to townsfolks.
Since the gameplay is light, I challenged myself to build an interactive 
procedural foliage system for the game in the 3 weeks we had for the jam.

What I ended up with was a system of generating grass entirely on the GPU with
compute shader, renders them in chunks to benefit from frustum and occlusion culling,
and sways as the player walks by according to a compute shader simulation. 
The algorithm models grass sway as a mass-spring-damper system and supports an arbitrary number 
of entities interacting with the grass instead of only one player.

# Result

{% include image-collection.html class='half' images="
    /assets/images/blogs/grass/sway.gif,
    /assets/images/blogs/grass/sway2.gif"
    caption = "Grass swaying as player walks by, 'remembers' where they have been for a couple seconds "
%}

# References

![Old grass implementation](/assets/images/blogs/grass/oldGrass.gif){:.align-right .w50}
Way back in 2023, I made an procedural grass system with C++ and OpenGL.
The grass there is uniform and there was virtually no gameplay.

For this project, I want to implement grass in a commercial game engine.
Breadth of the Wild's stylized grass partially influenced the look, and a lot of 
the techniques I use are from a Ghost of Tsushima developer's talk.

# Generation

There are multiple approaches I considered for generating mass foliage, including:
1. Instancing objects on the CPU then batch them into one / few draw calls
2. Generating foliage with geometry shaders, although this is grossly inefficient
3. Lastly, generating the grass on the GPU with a compute shader, storing it 
in a compute buffer, and drawing the grass should only be 1 draw call.

I opted for the last way since it is the most performant.
We won't have to push too much grass data from the CPU to the GPU, and we won't be
regenerating the grass every frame.

## Tiling

The first step is breaking the world into 10x10 tiles.
It's infeasible to generate unique blades of grass for the entire world, so we 
reuse this 10x10 tile of grass for each world chunk.
Doing so also allows us to take advantage of Unity's built-in frustum culling, 
occlusion culling, and LOD systems.

{% include image-collection.html class='half' images="
    /assets/images/blogs/grass/chunk.png,
    /assets/images/blogs/grass/culling.png"
    caption = "Grass chunks (left) and using frustum culling on them (right)"
%}

## Compute shader

![One grass blade](/assets/images/blogs/grass/oneGrass.png){:.align-right .w30}
Since grass generation is not the focus of the project, I decided to start
working off of [NedMakesGames' grass generation scripts](https://gist.github.com/NedMakesGames/80a3a7d4a8dcb58110b211e4d0f36b28)
with a slight modification to produce correct normals and grass blades on a field
instead of vertices of a supplied mesh.

Each instance of our compute shader will be responsible for generating one grass
blade. 
This is stored in two large compute buffers:
```c++
struct GeneratedVertex {
    float3 positionOS;
    float3 normalOS;
    float2 uv;
    float3 bladeAnchorOS;
};
// Source and index buffers for the generated mesh
RWStructuredBuffer<GeneratedVertex> _GeneratedVertices;
RWStructuredBuffer<int> _GeneratedIndices;
```
and since the number of vertices and triangles that form each grass blades
is identical, we know exactly where to place data into the buffers so there's 
no need for an atomic counter.

The process goes as follows:
- Use the instance ID to determine where the grass should be placed on our mesh
```c++
int x = id.x - floor(id.x / _NumBladesX) * _NumBladesX;
int y = floor(id.x / _NumBladesX);
float2 planeUV = float2(float(x) / _NumBladesX, float(y) / _NumBladesY);
```
- Calculate a random direction and bend for the grass blade:
```c++
// The twist matrix decides which direction the grass blade will face
float3x3 twistMatrix = AngleAxis3x3(
    rand(positionOS + _RandomSeed, 2) * PI * 2, float3(0, 0, 1));
// This bend angle decides how much the tip bends
float bendAngle = rand(positionOS + _RandomSeed, 3) * _MaxBendAngle;
```
- Iterate through each blade segment, create vertices
``` c++
for (int i = 0; i < numBladeSegments; i++) {
	// The v rises as we increase in segments
	float v = i / (float)numBladeSegments;
	// The u of the first vertex. It converges on 0.5 as the segment increases
	// this code will make /\ this sort of shape
	float u = 0.5 - (1 - v) * 0.5;
	float3x3 transform = CalculateTransformationForHeight(
        v, tsToOs, twistMatrix, bendAngle);
	vertices[i * 2] = MakeGeneratedPoint(
        positionOS, normalOS, dimensions, transform, float2(u, v));
	vertices[i * 2 + 1] = MakeGeneratedPoint(
        positionOS, normalOS, dimensions, transform, float2(1 - u, v));
}
// Calculate the transform for the blade tip
float3x3 tipTransform = CalculateTransformationForHeight(
    1, tsToOs, twistMatrix, bendAngle);
// Append the tip vertex
vertices[numBladeSegments * 2] = MakeGeneratedPoint(
    positionOS, normalOS, dimensions, tipTransform, float2(0.5, 1));
```
- Append them to the compute buffer

# Vertex shader

Onto the vertex shader. 
Doing nothing and passing the compute buffer data to the fragment shader yields a grid of uniformly dense grass.
{% include image-collection.html class='display' images="
    /assets/images/blogs/grass/simpleVertShader.png"
%}

## Random offset

Our first order of business was adding a random offset to the grass blades. 
This already makes the grass looks much more organic. 
Truthfully, this can be done in the compute shader generation stage as well,
doing so here is a personal and less performant choice.
{% include image-collection.html class='display' images="
    /assets/images/blogs/grass/vertJitter.png"
%}
```c++
float3 randomOffset = 
	tangentWS * randNegative1to1(bladeAnchorWS, 0) 
	+ bitangentWS * randNegative1to1(bladeAnchorWS, 1);
randomOffset *= _RandomJitterRadius;
bladeAnchorWS += randomOffset; // Apply jitter to the anchor for wind
```

## Wind

Next is spatially varying wind. 
This is simple, just add tillable noise on the x and y.
Ideally these are packed into the red and green channel of a single texture,
but I was having trouble doing that in Krita.
{% include image-collection.html class='display' images="
    /assets/images/blogs/grass/grass_wind.gif"
%}
```c++
float2 windUV = TRANSFORM_TEX(bladeAnchorWS.xz, _WindTexture) 
	* 0.05 + _Time.y * _WindFrequency;
// Sample the wind noise texture and remap it to range between -1 and 1
float2 windNoise = 
	float2(
		SAMPLE_TEXTURE2D_LOD(_WindTexture, sampler_WindTexture, windUV, 0).x, 
		SAMPLE_TEXTURE2D_LOD(_WindTexture2, sampler_WindTexture2, windUV, 0).x) - 0.5;
// Offset blade points in a vector perpendular to it's normal, but also consistent
// across blades.
float3 windOffset = cross(float3(0,1,0), float3(windNoise.x, 0, windNoise.y));

// Then scale by the amplitude and UV.y, so points near the base of the blade are blown less
windOffset *= _WindAmplitude * input.uv.y;
```
> Notice that we use the grass blade's anchor point to sample our noise texture.
> This is so that the entire blade gets affected the same amount by wind.
> Otherwise the blades might have weird stretching artefacts.

## Density

Uniformly dense grass is boring.
Ideally, we want an artist to go in and paint where grass should be.
However, there's no time to create a robust grass painting tool in a Jam.

So we did a little hack.
We can use the Unity terrain drawing tool to alter a terrain, 
turn off the rendering, and use the heightmap as our density texture.
Albeit a little scuff, this approach presents no additional runtime cost since 
we can remove the terrain entirely at runtime and only package the heightmap.

{% include image-collection.html class='half' images="
    /assets/images/blogs/grass/grass_hack_density.gif,
    /assets/images/blogs/grass/vertDensity.png"
    caption = "Using the grass paint tool (left) and the resulting grass (right)"
%}

## Viewspace Nudge

If you look at certain parts of our grass, you will notice that they feel sparse, even when it is uniformly dense.
This is because random grass rotations cause blades to be orthogonal to our viewing angle.
One effective trick to getting the blades feeling fuller without introducing more verts 
is by pushing vertices of the blades tangential to the viewing vector as it becomes more orthogonal.

There's a variety of ways to tune this.
I just hardcoded some numbers because there won't be an artist tuning it.

{% include image-collection.html class='half' images="
    /assets/images/blogs/grass/vertNoNudge.png,
    /assets/images/blogs/grass/vertWithNudge.png"
    caption = "Original vertex shader (left) and one with viewspace nudge applied (right)"
%}

```c++
float3 GetViewSpaceNudge(float3 positionWS, float3 tangentWS, float3 normalWS, float density, float2 uv) {
    float3 viewDirWS = normalize(GetWorldSpaceNormalizeViewDir(positionWS));

    float viewDotNormal = saturate(dot(viewDirWS.xz, normalWS.xz));
    float viewSpaceThickenFactor = ease_out_quad(1 - viewDotNormal);
    viewSpaceThickenFactor *= smoothstep(0.0, 0.2, viewDotNormal);

    float3 viewSpaceXDirection = mul(UNITY_MATRIX_I_V, float4(1, 0, 0, 0)).xyz;
    viewSpaceXDirection.y = 0;

    float tangentDirection = -sign(uv.x - 0.5);
    return viewSpaceThickenFactor * 0.02 * normalize(viewSpaceXDirection) 
        * density * tangentDirection;
}
```

# Fragment shader

For the grass to register as a field instead of many individual pieces, 
we want the bottom of them to blend with the ground.
One way to do so is have the camera capture the ground into a texture, then sample it in our fragment shader.
Note that I don't apply any additional lighting in this step, since lighting is already captured by the camera.

Next is shadows.
For this step, I again refrain from using Unity's lighting functions and instead sample the shadow map directly.
Unity doesn't expose nor document their lighting function, so I had to reverse-engineer the attenuation factors.

{% include image-collection.html class='third' images="
    /assets/images/blogs/grass/noShading.png,
    /assets/images/blogs/grass/noShadow.png,
    /assets/images/blogs/grass/withShadow.png"
    caption = "Grass without shading, with shading but no shadow, and final fragment shader"
%}
```c++
float4 shadowCoord = CalculateShadowCoord(
	input.positionWS, input.positionCS);
float shadow = MainLightRealtimeShadow(shadowCoord);

groundColor = lerp(groundColor * _ShadowAttenuation.xyz, groundColor, shadow);
```

# Interaction

Historically, people commonly used two ways to implement grass interaction each with their own tradeoffs:

- Array of agent positions: We can supply the vertex shader with an array of agent positions, then sway grass near those positions. 
This is the cheapest method, but it limits the number of agents we can use.
- Signed Distance Field: Certain engines, like Unreal, builds an SDF of its entities that we can use to sway the grass.
Building an SDF is expensive, but is low-cost if the engine already does it for other effects. 

But both approaches lacks memory. 
The moment the agents leave a particular patch of grass, it "forgets" about their existence.

## Velocity Buffer
![Velocity Buffer](/assets/images/blogs/grass/velocityBuffer.png){:.align-right .w50}
Enters the velocity buffer, a 2D texture packed with information about how much grass should swap (red green components) as well as
what its current velocity is (blue alpha components).
I first heard about the idea from Aarthificial's implementation of procedural grass for his 2D platformer,
but a similar technique is also used in God of War to model foliage interaction 
with Kratos's axe throws.

Instead of only storing grass displacement and dimming the texture gradually to 0, I
thought of using a spring-mass-damper system.
This way, the grass would sway away from the player and "counter-sway" after the player leaves.

Maintaining the velocity buffer and interacting with it is handled with two compute shaders.

## Agent Displacement Shader
This compute shader draws how much grass should sway around an agent, in this case the player.
This can be dispatched every frame, every few frames, 
or every time the player moves a significant distance.
```c++
float2 getDesiredDisplacement(
	float3 pixelOffset, float agentSize) {
	
    float len = length(pixelOffset.xz);
    float2 dir = len > 0 ? normalize(displacement.xz) : float2(1,0);

    // We want a sphere mask with a radius of agentSize
    float strength = saturate((0.2 + 1 - len / agentSize));
    strength = strength * strength;

    return dir * strength;
}
```

## Spring-Mass-Damper Simulation
This compute shader runs through every texel of the velocity buffer and performs discrete integration to model the equation:

$$F = -c\vec{v} - k\vec{x}$$

$\vec{x}$ is the current displacement, $\vec{v}$ current velocity, $k$ is the system's stiffness, $c$ is damping.
Since this is a game jam, I use the simple Euler integration but you might want to
use a more stable method for a commercial game.

```c++
float2 get_acceleration(float2 displacement, float2 velocity) {
    return -_damping * velocity - _stiffness * displacement;
}

[numthreads(8,8,1)]
void CSMain (uint3 id : SV_DispatchThreadID)
{
    if (id.x >= (uint) _width || id.y >= (uint) _height)
        return;

    float4 packedSample = Result.Load(id.xy);
    float2 velocity = packedSample.xy;
    float2 displacement = packedSample.zw;

    Result[id.xy] = integrate(displacement, velocity, _deltaTime);
}
```

Then, all it takes is applying this grass sway in the vertex shader, similar to how we do wind.
```c++
float3 ApplyParting(float3 positionWS, float3 anchorWS) {
    float2 uv = (anchorWS.xz - _DisplacementTextureCenter) 
        / _DisplacementTextureScale + 0.5;
    float4 packedSample = tex2Dlod(_DisplacementTexture, float4(uv, 0, 0));
    float2 displacement = packedSample.zw;

    float strength = length(displacement);
    if (strength > 0.02) {
        float3 axis = normalize(cross(float3(0,1,0), float3(displacement.x,0,displacement.y)));
        float angle = strength * 0.3 * PI;

        return mul(AngleAxis3x3(angle, axis), (positionWS - anchorWS)) + anchorWS;
    } else { return positionWS; }
}
```

{% include image-collection.html class='display' images="
    /assets/images/blogs/grass/grass_sway_visualization.gif"
    caption = "Visualization of the velocity buffer in a test level"
%}
