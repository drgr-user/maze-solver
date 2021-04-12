# maze_solver
Artificial Intelligence I course mid-quarter project - fall 2020

Maze Solver was the mid-quarter project for the Artificial Intelligence I course at IASBS in fall 2020. It gets an input file containing information about a maze, a start point, and a goal point. Maze Solver uses Breadth-first search, Depth-first search, and Iterative deepening depth-first search algorithms to find a path from the start point to the goal point in the maze.

Input
-----
The first line represents the number of rows and columns. Each of the following lines indicates in which direction a maze cell is open, using `1` if it's traversable and `0` if it's closed. The bottom line shows the `start` and the `goal` cells.
```
number_of_rows number_of_columns
up right down left
up right down left
up right down left
.
.
.
up right down left
start goal
```

Output
------
The output file is a traceback from the `goal` cell to the `start` cell.
