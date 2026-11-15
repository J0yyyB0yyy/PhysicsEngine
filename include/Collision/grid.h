#pragma once

#include <vector>
#include <cstddef>
#include <set>
#include <utility>
#include "./aabb.h"

struct Cell{
    std::vector<std::size_t> bodyIndices;
};

class Grid{
private:
    float cellSize;
    int colums, rows;
    std::vector<Cell> cells;

    int getCellX(float x) const;
    int getCellY(float y) const;
    std::size_t getCellIndex(int x, int y) const;
public:
    Grid(float cellSize, int columns, int rows);

    void insertBody(std::size_t bodyIndex, const AABB& box);

    std::set<std::pair<std::size_t, std::size_t>>

    getPotentialPairs() const;
};