// maze.cpp
#include "maze.h"
#include <cstdlib>
#include <ctime>

Maze::Maze() {
    srand(time(0));
    resetGrid();
    visit(1, 1);
}

void Maze::resetGrid() {
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i) {
        grid[i] = '#';
    }
}

int Maze::xyToIndex(int x, int y) {
    return y * GRID_WIDTH + x;
}

bool Maze::isInBounds(int x, int y) {
    return x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT;
}

void Maze::visit(int x, int y) {
    grid[xyToIndex(x, y)] = ' ';
    int dirs[4] = { NORTH, EAST, SOUTH, WEST };
    for (int i = 0; i < 4; ++i) {
        int r = rand() & 3;
        int temp = dirs[r];
        dirs[r] = dirs[i];
        dirs[i] = temp;
    }
    for (int i = 0; i < 4; ++i) {
        int dx = 0, dy = 0;
        switch (dirs[i]) {
        case NORTH: dy = -1; break;
        case SOUTH: dy = 1; break;
        case EAST: dx = 1; break;
        case WEST: dx = -1; break;
        }
        int x2 = x + (dx << 1);
        int y2 = y + (dy << 1);
        if (isInBounds(x2, y2)) {
            if (grid[xyToIndex(x2, y2)] == '#') {
                grid[xyToIndex(x2 - dx, y2 - dy)] = ' ';
                visit(x2, y2);
            }
        }
    }
}

void Maze::generateMaze() {
    mazeMatrix.clear();
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        std::vector<int> row;
        for (int x = 0; x < GRID_WIDTH; ++x) {
            row.push_back((grid[xyToIndex(x, y)] == ' ') ? 2 : 1);
        }
        mazeMatrix.push_back(row);
    }
}

std::vector<std::vector<int>> Maze::getMazeMatrix() {
    return mazeMatrix;
}

void Maze::printMaze() {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            std::cout << mazeMatrix[y][x];
        }
        std::cout << std::endl;
    }
}
