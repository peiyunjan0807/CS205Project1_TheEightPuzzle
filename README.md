# CS205Project1_TheEightPuzzle

**CS205: Introduction to Artificial Intelligence — Project 1**
Solving the classic 8 puzzle problem using three search algorithms:
- Uniform Cost Search
- A* with the Misplaced Tile heuristic
- A* with the Manhattan Distance heuristic

## File description
* `eight_puzzle.hpp` – contains the implementation of three search algorithms.
* `driver.cpp` – main function that runs the interactive 8-puzzle solver.

## Example of this project?

    1. Start the Solver
        ```
        Welcome to my 8‐Puzzle Solver. Type '1' to use a default puzzle, or '2' to create your own.
        2
        ```
    2. Enter a Custom Puzzle
        ```
        Enter your puzzle, using a zero to represent the blank.
        Enter the puzzle delimiting the numbers with a space. 
        RET only when finished.
        
        Enter the first row: 1 2 3
        Enter the second row: 4 0 6
        Enter the third row: 7 5 8
        ```
    3. Select Search Algorithm
        ```
        Select algorithm. (1) for Uniform Cost Search, (2) for the Misplaced Tile Heuristic, or (3) the Manhattan Distance Heuristic.
        3
        ```

    4. Output
        ```
        The best state to expand with a g(n) = 0 and h(n) = 2 is... 
        [1, 2, 3]
        [4, 0, 6]
        [7, 5, 8]
        The best state to expand with a g(n) = 1 and h(n) = 1 is... 
        [1, 2, 3]
        [4, 5, 6]
        [7, 0, 8]
        The best state to expand with a g(n) = 2 and h(n) = 0 is... 
        [1, 2, 3]
        [4, 5, 6]
        [7, 8, 0]
        
        Goal state!
        
        Solution depth was 2 
        Number of nodes expanded: 2 
        Max queue size: 5
        ```
###
