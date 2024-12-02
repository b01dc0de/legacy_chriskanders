#ifndef PSEUDOKU_H
#define PSEUDOKU_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW_OF(r) {r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7], r[8]}
#define COL_OF(c) {c[0], c[9], c[18], c[27], c[36], c[45], c[54], c[63], c[72]}
#define BOX_OF(b) {b[0], b[1], b[2], b[9], b[10], b[11], b[18], b[19], b[20]}

//typedefs for integer types
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

//typedefs for unsigned integer types
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

//typedefs for floating-point types
typedef float real32;
typedef double real64;
typedef long double real128;

//contains all peers (row/col/box values) of a cell
typedef struct
{
    int row[9];
    int col[9];
    int box[9];
} neighbors;

//contains possible values of a cell w/number of vals
typedef struct
{
    int vals[9];
    int size;
} possible_values;

//contains two main grids of the game
typedef struct
{
    int grid[81];
    int* get_row_ptr(int*, int);
    int* get_col_ptr(int*, int);
    int* get_box_ptr(int*, int);
    neighbors* get_neighbors(int*, int);
    int is_safe(int*, int, int);
    possible_values* get_pos_vals(int*, int);
    int fill_grid(int*, int);
    void copy_grid(int*, int*);
    void init_grid(int*);
    void print_grid(int*);
} grid;

#endif

/*
  {1, 2, 3,----4, 5, 6,----7, 8, 9,
  .4, 5, 6,----7, 8, 9,----1, 2, 3,
  .7, 8, 9,----1, 2, 3,----4, 5, 6,
  |||||||||||||||||||||||||||||||||
  .2, 3, 4,----5, 6, 7,----8, 9, 1,
  .5, 6, 7,----8, 9, 1,----2, 3, 4,
  .8, 9, 1,----2, 3, 4,----5, 6, 7,
  |||||||||||||||||||||||||||||||||
  .3, 4, 5,----6, 7, 8,----9, 1, 2,
  .6, 7, 8,----9, 1, 2,----3, 4, 5,
  .9, 1, 2,----3, 4, 5,----6, 7, 8}
*/

/*
  {.0, .1, .2,---.3, .4, .5,---.6, .7, .8,
  ..9, 10, 11,---12, 13, 14,---15, 16, 17,
  .18, 19, 20,---21, 22, 23,---24, 25, 26,
  ||||||||||||||||||||||||||||||||||||||||
  .27, 28, 29,---30, 31, 32,---33, 34, 35,
  .36, 37, 38,---39, 40, 41,---42, 43, 44,
  .45, 46, 47,---48, 49, 50,---51, 52, 53,
  ||||||||||||||||||||||||||||||||||||||||
  .54, 55, 56,---57, 58, 59,---60, 61, 62,
  .63, 64, 65,---66, 67, 68,---69, 70, 71,
  .72, 73, 74,---75, 76, 77,---78, 79, 80}
*/
