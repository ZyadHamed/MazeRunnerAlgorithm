# MazeRunnerAlgorithm
I designed this project on behalf of the All Egypt Micromouse competition. The project utilizes an original, novel-of-art approach to explore and map the maze. Then uses a modified  optimal path finding algorithm to determine the shortest path from the start to the center. The testing platform is based on the mms simulator made by [mackorone](https://github.com/mackorone/mms)

* The movment mechanism utilizes a position tracking system for the x-coordinate, y-coordinate, and the movement direction of the robot. If the robot's initial direction is the forward direction (Moving up in the y-axis), then the y-cooridnate increments by 1 for each cell being moved. Similarly, right direction is moving right in the x-axis, incrementing the x-coordinate by 1. Left direction is moving left in the x-axis, decrementing the x-coordinate by 1. Backward direction is moving down in the y-axis, decrementing the y-coordinate by 1.
![Robot in maze](https://user-images.githubusercontent.com/61621248/210372088-ae1e7440-6bb2-47c9-a721-21a39fdcaa5b.png)

* The exploration algorithm checks for each of the aviliable paths around the robot, then selects the least visited path to be revisited again by the robot. That ensures that eventually all the cells within the maze, no matter how large it is, will be visited and mapped by the robot. When two surrounding cells have equal value of being visited, the robot selects according to the following order: Forward, Right, Left

* When the robot visits a new cell, it maps that cell in an array of a defined element of type Cell that has 3 properties for surrounding walls of the cells (LeftWall, RightWall, FrontWall), and a property for keeping track of the visited count. That array represents the whole Maze, where Maze[x][y] is the cell as position (x, y). The robot increments the visited count of Maze[x][y] by 1, and sets each of the wall parameters to match the walls around that cell.

* After the mapping phase is completed, the Maze array is compiled into an double-dimensional array of characters, where the character 0 represents a free space, and 1 represents a wall. That compiled array of charactes can then be solved for the optimal path between two points via breadth first search. 

