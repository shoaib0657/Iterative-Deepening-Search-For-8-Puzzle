# 8-Puzzle Solver with Iterative Deepening Search

## Project Overview
This is an implementation of an 8-puzzle solver using the Iterative Deepening Search (IDS) algorithm. The 8-puzzle is a sliding puzzle that consists of a frame of numbered square tiles in random order with one tile missing. The object of the puzzle is to place the tiles in order by making sliding moves that use the empty space. 

The IDS algorithm is a combination of Depth-First Search (DFS) and Breadth-First Search (BFS) algorithms. It starts with a depth of 0 and increases the depth limit by 1 in each iteration until the goal state is found. The IDS algorithm is complete and optimal for the 8-puzzle problem.

## Features
- Randomly generates solvable 8-puzzle configurations
- Implements Iterative Deepening Search algorithm
- Checks puzzle solvability before solving
- Tracks solution depth and computation time
- Provides step-by-step solution visualization
