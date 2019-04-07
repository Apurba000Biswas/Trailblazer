# Trailblazer

This project is one of the Assignment of CS 106B from stanford University.

Starter code and problem documentation can be found on the following website
http://web.stanford.edu/class/archive/cs/cs106b/cs106b.1172//assn/trailblazer.html


Finds path between two places in a map

Path searching was implemented by four diffrent algorithms:
### 1- BFS(Breadth-first search):
My Sollution - [Breadth-first search](https://github.com/Apurba000Biswas/Trailblazer/blob/master/src/trailblazer.cpp#L29)
#### Running Sollution:
<div align="center">
  <img src ="img/bfs_middle_earth.png" width ="900">
</div>
<div align="center">
  <img src ="img/bfs_stanford.png" width ="900">
</div>
<div align="center">
  <img src ="img/bfs_usa.png" width ="900">
</div>
<div align="center">
  <img src ="img/bfs_istanbul.png" width ="900">
</div>

Finds a shortest path that has smallest number of nodes.

### 2- Dijkstras Algorithm:
My Sollution - [Dijkstras](https://github.com/Apurba000Biswas/Trailblazer/blob/master/src/trailblazer.cpp#L97)
#### Running Sollution:
<div align="center">
  <img src ="img/dijkastra_mddle_earth.png" width ="900">
</div>
<div align="center">
  <img src ="img/dijkastra_stanford.png" width ="900">
</div>
<div align="center">
  <img src ="img/dijkastra_usa.png" width ="900">
</div>

Finds a cheapest path that.

### 3- A* Search:
My Sollution - [A_Star](https://github.com/Apurba000Biswas/Trailblazer/blob/master/src/trailblazer.cpp#L160)

Exactly does the dijkstras algorithm dose, onley faster. It Uses a Heuristics to guess the end position's path.

### 4- Alternative Route Search:
My Sollution - [Alternative Route Search](https://github.com/Apurba000Biswas/Trailblazer/blob/master/src/trailblazer.cpp#L180)

Finds an alternative path to reach the end position. It Uses A* / Dijkastras algortihm internally to finds the best alternative path after the orignal best path.(We Assume atleast 20% path should be diffrent than best path found by dijkstra/A* ).

