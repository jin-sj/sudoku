//
// Created by Seung Jung Jin on 2019-02-20.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

void generate_random_puzzle(int * array, int row, int col);

void create_empty_puzzle(int * array, int row, int col);
void read_puzzle_file(int * array, char path);
void display_puzzle(int * array, int row, int col);

int check_puzzle(int * array, int row, int col);

int get_cell_value(int * array, int row, int col);
void set_cell_value(int * array, int row, int col, int value, int is_permanent);

int is_full(int * array, int row, int col);

int is_legal(int * array, int row, int col, int value);
int * get_allowed_values(int * array, int * allowed int row, int col);
int check_row(int * array, int row, int col);
int check_col(int * array, int row, int col);
int check_square(int * array, int row, int col);

void reset(int * array);
#endif SUDOKU_SUDOKU_H
