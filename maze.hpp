// labirintus gener�l�shoz header f�jlok
#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>
#include <vector>

#define GRID_WIDTH 21       //labirintus magass�ga
#define GRID_HEIGHT 21      //labirintus sz�less�ge
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

class Maze {
public:
    Maze();
    void generateMaze();
    void printMaze();
    std::vector<std::vector<int>> getMazeMatrix();

private:
    void resetGrid();
    int xyToIndex(int x, int y);
    bool isInBounds(int x, int y);
    void visit(int x, int y);

    char grid[GRID_WIDTH * GRID_HEIGHT];
    std::vector<std::vector<int>> mazeMatrix;
};

#endif
