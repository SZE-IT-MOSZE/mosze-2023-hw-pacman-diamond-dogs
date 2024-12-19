#pragma once

#include <cstdlib>
#include <iostream>


enum Direction {
    up,
    down,
    left,
    right
};


inline Direction GetRandomDirection () {
    int a = rand () % 4;
    return (Direction)a;
}

