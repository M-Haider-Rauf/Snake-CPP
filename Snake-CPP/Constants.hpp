#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

constexpr unsigned GRID_WIDTH = 810u;
constexpr unsigned GRID_HEIGHT = 600u;

constexpr unsigned WIN_WIDTH = GRID_WIDTH;
constexpr unsigned WIN_HEIGHT = GRID_HEIGHT + 60u;

constexpr unsigned CELL_SIZE = 30u;
constexpr unsigned GRID_COLS = GRID_WIDTH / CELL_SIZE;
constexpr unsigned GRID_ROWS = GRID_HEIGHT / CELL_SIZE;

#endif // !CONSTANTS_HPP
