//
// Created by Seung Jung Jin on 2019-02-20.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

static const int NUM_COLS = 9;

void create_sample_puzzle(int (*array)[NUM_COLS]);

void create_empty_puzzle(int (*array)[NUM_COLS]);
void display(int (*array)[NUM_COLS]);

void set_cell_value(int (*array)[NUM_COLS], int row, int col, int value, int is_permanent);
void add_guess(int (*array)[NUM_COLS], int row, int col, int value);
void add_permanent(int (*array)[NUM_COLS], int row, int col, int value);
int get_value_in(int (*array)[NUM_COLS], int row, int col);

void reset_cell( int (*array)[NUM_COLS], int row, int col);

int sudoku_solver(int (*array)[NUM_COLS]);

int is_legal_move(int (*array)[NUM_COLS] , int row, int col, int value);
int is_permanent_value(int (*array)[NUM_COLS], int row, int col);
int value_in_row(int (*array)[NUM_COLS], int row, int col);
int value_in_col(int (*array)[NUM_COLS], int row, int col);
int value_in_square(int (*array)[NUM_COLS], int row, int col, int value);

int is_full(int (*array)[NUM_COLS], int row, int col);
void reset(int (*array)[NUM_COLS]);

int test(int (*array)[NUM_COLS]);
#endif //SUDOKU_SUDOKU_H
