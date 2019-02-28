//
// Created by Seung Jung Jin on 2019-02-20.
//

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

static const int NUM_COLS = 9;

void create_empty_puzzle(int (*array)[NUM_COLS]);
void create_new_puzzle(int (*array)[NUM_COLS]);

void shuffle_list(int * list, int size);

void display(int (*array)[NUM_COLS]);

void set_cell_value(int (*array)[NUM_COLS], int row, int col, int value, int is_permanent);
void add_guess(int (*array)[NUM_COLS], int row, int col, int value);
void add_permanent(int (*array)[NUM_COLS], int row, int col, int value);
int get_value_in(int (*array)[NUM_COLS], int row, int col);

void copy_array(int (*source_array)[NUM_COLS], int (*target_array)[NUM_COLS]);
void reset_cell( int (*array)[NUM_COLS], int row, int col);

int sudoku_solver(int (*array)[NUM_COLS]);

int generate_random_number(int low, int high);

int is_legal_move(int (*array)[NUM_COLS] , int row, int col, int value);
int is_permanent_cell(int (*array)[NUM_COLS], int row, int col);
int value_in_row(int (*array)[NUM_COLS], int row, int col);
int value_in_col(int (*array)[NUM_COLS], int row, int col);
int value_in_square(int (*array)[NUM_COLS], int row, int col, int value);
void print_possible_values(int (*array)[NUM_COLS], int row, int col);

int is_full(int (*array)[NUM_COLS], int row, int col);
void reset(int (*array)[NUM_COLS]);
#endif //SUDOKU_SUDOKU_H
