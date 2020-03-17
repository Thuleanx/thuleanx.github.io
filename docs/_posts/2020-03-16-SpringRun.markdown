---
layout: post
title:  "SpringRun"
date:   2020-03-16 10:58:00 -0600
author: thuleanx
category: competitive-programming training

---

Spring break is finally happening, which means infinite time for me to do problems (and play POE Delirium). The problems that I solved will be posted here, along with some short description. 

# Day 1

## 300 iq contest

### [Best Tree][besttree] ⭐⭐⭐⭐

This problem requires a pretty interesting observation about tree matching. One more fact added to [Random Interesting Facts][RIF].

Category: Matching, Greedy, Proof

### [Just Counting][justcounting] ⭐⭐⭐⭐⭐

By solving just counting, you effectively solve all problems that requires labeling edges on graph and having the edges incident to any vertex have some property that can be constrained by linear recurrence. At first, I thought this was tree dp, but upon knowing that all you need to do is find the number of vectors in the basis, it becomes clear. By property of the graph, you can have gaussian runs in $\mathtt{O(m\log{m})}$ time instead of the usual $mathtt{O(m^3)}$.

Category: Gaussian Elimination, Graph

### [Cell Blocking][cellblocking] ⭐⭐⭐⭐

Earlier when I thought about this problem, it was clear that we construct two paths one greedily going down before right and the other greedily going right before down. If you choose to block any cell in their intersection, clearly there would be no path between (1,1) and (n,m). The problem was the cases where you have to block two cells. This was done by fixing blocking one cell on one of the greedy paths, then you end up with an alternate board where you have to block one cell (which we already solved).

Category: Constructive Algorithm, Puzzle

## ICPC WF 2019 

### [Azulejos][azulejos] ⭐⭐⭐

The problem boils down to: match x against y such that you do not restrict yourself in the future. The trick is if you have a group of A and B things, you want to start the pairing stuff in the smaller group first (because you know all of their options already). Overall, this was nice but a little messy as it requires the use of set.

Category: Greedy, Data structure, Sorting

### [Dead End Detector][deadenddetector] ⭐⭐⭐⭐

This was one of the few instances where bridge tree proves extremely useful. The problem requires you to decompose the graph into a forest of trees where some nodes are big and some are small, and edges are bridges in the original graph. After this, the answer will come with some case work.

Category: Bridge tree, Graph, Casework

### [Circular DNA][circulardna] ⭐⭐

This was one of the gimmes problems in the contest. It was clear that we want to increment ranges where the dyck path is lowest. 

Category: Combinatoric

[RIF]: {% post_url 2020-03-16-RIF %}
[besttree]: https://codeforces.com/gym/102538/problem/B
[justcounting]: https://codeforces.com/gym/102538/problem/J
[cellblocking]: https://codeforces.com/gym/102538/problem/C
[azulejos]: https://codeforces.com/gym/102511/problem/A
[deadenddetector]: https://codeforces.com/gym/102511/problem/E
[circulardna]: https://codeforces.com/gym/102511/problem/D
