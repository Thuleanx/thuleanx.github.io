---
layout: post
title: "Shiny Shores"
image:
    thumbnail: /assets/images/gameCaptures/shiny-shores/gameplay_rushingwave.gif
sidebar:
    team: 2
    duration: 1 week
    tools: Unity, FMOD
    platforms: WebGL
    image: /assets/images/gameCaptures/shiny-shores/cover.png
    text: >-
        - State machine player character controller and animation

        - Procedural wave construction

        - Collectible system and high score tracker

        - Leaderboard system
---

I collaborated with artist [Allison Yeh](https://allisonkyeh.com/) to develop
Shiny Shores, which ended up ranking 16th out of 1484 entries in
[Brackey's Game Jam 2024.2](https://itch.io/jam/brackeys-12).
You play as a little child collecting shells and other shiny trinkets in between waves.

{% include image-collection.html class='half' images="
    /assets/images/gameCaptures/shiny-shores/title_small.gif,
    /assets/images/gameCaptures/shiny-shores/gameplay_4.gif
" %}

{% include image-collection.html class='third' images="
    /assets/images/gameCaptures/shiny-shores/gameplay3.gif,
    /assets/images/gameCaptures/shiny-shores/gameplay_rushingwave.gif,
    /assets/images/gameCaptures/shiny-shores/gameover_2.gif" %}

---

![](/assets/images/gameCaptures/shiny-shores/gameplay1.gif){:.align-right}
Hands down the most challenging part of the jam is handling the visual and
mechanic of the waves.

Initially our idea was that they would come in, leave behind shiny shells, 
and the player needs to stay at the dock at the bottom of the screen to be safe.
Somewhere along the line, we introduced rock obstacles that would block the player's part,
which is where the fun of the game truly shines.


# Prototype

![](/assets/images/gameCaptures/shiny-shores/wave_prototype_approach.png){:.align-right .w30}
My first order of business was generating the wave mesh.
One approach is splitting the waves into slices that hit a particular rock.
This is what I went with for the prototype.

Using a line-sweep algorithm, we can construct these slices in $O(n \log{n})$, 
$n$ being the number of rocks. 
This only needs to be recomputed when a rock emerges or sink.

<div class="clearfix"></div>

{::options parse_block_html="true" /}
<details><summary markdown="span">Code Snippet - Prototype</summary>

```c++
List<KeyValuePair<bool, Vector2>> points = new List<KeyValuePair<bool,Vector2>>();
SortedDictionary<float, int> sweepLine = new SortedDictionary<float, int>();
List<Vector2> obstacleSliceBoundaries = new List<Vector2>();

foreach (Obstacle obstacle in obstacles) {
    SphereCollider sphereCollider = obstacle?.GetComponent<SphereCollider>();
    if (!sphereCollider) continue;
    Vector3 obstaclePosition = obstacle.transform.position;

    float crossSectionRadius = sphereCollider.radius;
    if (crossSectionRadius == 0.0) continue;

    points.Add(new KeyValuePair<bool, Vector2>(
        true, 
        new Vector2(obstaclePosition.x - crossSectionRadius, obstaclePosition.z))
    );
    points.Add(new KeyValuePair<bool, Vector2>(
        false, 
        new Vector2(obstaclePosition.x + crossSectionRadius, obstaclePosition.z))
    );
}

points.Sort((a,b) => {
    if (a.Value.x != b.Value.x) return a.Value.x.CompareTo(b.Value.x);
    if (a.Key != b.Key) return a.Key.CompareTo(b.Key);
    return 0;
});

for (int i = 0; i < points.Count; ) {
    float xPosition = points[i].Value.x;
    while (i < points.Count && xPosition == points[i].Value.x) {
        float zPosition = points[i].Value.y;

        if (sweepLine.ContainsKey(zPosition))
            sweepLine[zPosition] += (points[i].Key ? 1 : -1);
        else
            sweepLine.Add(zPosition, 1);

        if (sweepLine[zPosition] == 0) 
            sweepLine.Remove(zPosition);
        i++;
    }

    if (sweepLine.Count == 0) 
        obstacleSliceBoundaries.Add(new Vector2(xPosition, Mathf.NegativeInfinity));
    else {
        var firstItem = sweepLine.GetEnumerator();
        firstItem.MoveNext();

        float lowestKey = firstItem.Current.Key;
        obstacleSliceBoundaries.Add(new Vector2(xPosition, lowestKey));
    }
}
```
</details>
{::options parse_block_html="false" /}


# Iteration

![](/assets/images/gameCaptures/shiny-shores/wave_iteration_smooth_border.png){:.align-right .w30}
With the prototype approach, however, we end up with quite rectangular waves.
Every slice is a quad afterall.
In Shiny Shores we wanted the waves to look more organic and that means 
absolutely no sharp edges.
Ideally, it would look like the image to the right.

<div class="clearfix"></div>

![](/assets/images/gameCaptures/shiny-shores/wave_iteration_unintended_border.png){:.align-right .w30}
We can add smoothed out borders to the wave slices in shader.
However, we would run into unintended borders.
Of course, one workaround is to determine if a left or right border is added to
a slice by looking at whether neighboring slices, but this approach is **inellegant**.

<div class="clearfix"></div>

![](/assets/images/gameCaptures/shiny-shores/wave_final.png){:.align-right}
After some thinking, it dawned on me that the wave slices need not be disjoint. 
They can intersect!
As long as the UVs are lined up correctly, z fighting will not matter since there's visually no artifact.

The code for this is quite similar to a quicksort. 
First find the shortest wave slice, then make a giant wave covering the whole arena up
to the length of that slice, then recurse on the left and right.
