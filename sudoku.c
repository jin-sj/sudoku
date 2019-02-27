#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

#define TRUE 1
#define FALSE 0
#define EMPTY 0
#define NUM_ROWS 9
//#define NUM_COLS 9
#define MIN_VALUE 1
#define MAX_VALUE 9

int current_row;
int current_col;

void create_sample_puzzle(int (*array)[NUM_COLS]) {
    add_permanent(array, 0, 2, 4);
    add_permanent(array, 0, 3, 3);
    add_permanent(array, 0, 6, 2);
    add_permanent(array, 0, 8, 9);

    add_permanent(array, 1, 2, 5);
    add_permanent(array, 1, 5, 9);
    add_permanent(array, 1, 8, 1);

    add_permanent(array, 2, 1, 7);
    add_permanent(array, 2, 4, 6);
    add_permanent(array, 2, 7, 4);
    add_permanent(array, 2, 8, 3);

    add_permanent(array, 3, 2, 6);
    add_permanent(array, 3, 5, 2);
    add_permanent(array, 3, 7, 8);
    add_permanent(array, 3, 8, 7);

    add_permanent(array, 4, 0, 1);
    add_permanent(array, 4, 1, 9);
    add_permanent(array, 4, 5, 7);
    add_permanent(array, 4, 6, 4);

    add_permanent(array, 5, 1, 5);
    add_permanent(array, 5, 4, 8);
    add_permanent(array, 5, 5, 3);

    add_permanent(array, 6, 0, 6);
    add_permanent(array, 6, 6, 1);
    add_permanent(array, 6, 8, 5);

    add_permanent(array, 7, 2, 3);
    add_permanent(array, 7, 3, 5);
    add_permanent(array, 7, 5, 8);
    add_permanent(array, 7, 6, 6);
    add_permanent(array, 7, 7, 9);

    add_permanent(array, 8, 1, 4);
    add_permanent(array, 8, 2, 2);
    add_permanent(array, 8, 3, 9);
    add_permanent(array, 8, 4, 1);
    add_permanent(array, 8, 6, 3);
}

void create_empty_puzzle(int (*array)[NUM_COLS]) {
    int r, c;
    for (r = 0; r < NUM_ROWS; ++r) {
        for (c = 0; c < NUM_COLS; ++c) {
            array[r][c] = EMPTY;
        }
    }
    //array = {{EMPTY}};
}

void display(int (*array)[NUM_COLS]) {
    int r;
    int c;
    for (r = 0; r < NUM_ROWS; r++) {
        for (c = 0; c < NUM_COLS; c++) {
            if (c == 2 || c == 5) {
                printf("%d | ", abs(array[r][c]));
            } else {
                printf("%d ", abs(array[r][c]));
            }
        }
        printf("\n");
    }
}

void set_cell_value(int (*array)[NUM_COLS], int row, int col, int value, int is_permanent) {
    if (value >= 0 && value < 10) {
        if (is_permanent) {
            array[row][col] = -1 * value;
        } else {
            array[row][col] = value;
        }
    }
}

void add_guess(int (*array)[NUM_COLS], int row, int col, int value) {
    set_cell_value(array, row, col, value, FALSE);
}

void add_permanent(int (*array)[NUM_COLS], int row, int col, int value) {
    set_cell_value(array, row, col, value, TRUE);
}

void reset_cell(int (*array)[NUM_COLS], int row, int col) {
    set_cell_value(array, row, col, EMPTY, FALSE);
}

int get_value_in(int (*array)[NUM_COLS], int row, int col) {
    return abs(array[row][col]);
}

int sudoku_solver(int (*array)[NUM_COLS]) {
    int r, c;
    int test_value;
    for (r = 0; r < NUM_ROWS; ++r) {
        for (c = 0; c < NUM_COLS; ++c) {
            if (array[r][c] == EMPTY) {
                for (test_value = MIN_VALUE; test_value < MAX_VALUE; ++test_value) {
                    if (is_legal_move(array, r, c, test_value)) {
                        add_guess(array, r, c, test_value);
                        if (sudoku_solver(array) == TRUE) {
                            return TRUE;
                        } else {
                            reset_cell(array, r, c);
                        }
                    }
                }
                printf("Not solvable\n");
                display(array);
                return FALSE;
            }
        }
    }
    printf("SOLVED!\n");
    display(array);
    return TRUE;
}

int is_legal_move(int (*array)[NUM_COLS], int row, int col, int value) {
    if (!is_permanent_value(array, row, col) &&
        !value_in_row(array, row, value) &&
        !value_in_col(array, col, value) &&
        !value_in_square(array, row, col, value)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int is_permanent_value(int (*array)[NUM_COLS], int row, int col) {
    if (get_value_in(array, row, col) < 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int value_in_row(int (*array)[NUM_COLS], int row, int value) {
    int c;
    for (c = 0; c < NUM_COLS; ++c) {
        if (get_value_in(array, row, c) == value) {
            return TRUE;
        }
    }
    return FALSE;
}

int value_in_col(int (*array)[NUM_COLS], int col, int value) {
    int r;
    for (r = 0; r < NUM_ROWS; ++r) {
        if (get_value_in(array, r, col) == value) {
            return TRUE;
        }
    }
    return FALSE;
}

int value_in_square(int (*array)[NUM_COLS], int row, int col, int value) {
    int r, c;
    int r_start, r_end;
    int c_start, c_end;
    if (row <= 2) {
        r_start = 0;
        r_end = 2;
    } else if (row <= 5) {
        r_start = 3;
        r_end = 5;
    } else {
        r_start = 6;
        r_end = 8;
    }

    if (col <= 2) {
        c_start = 0;
        c_end = 2;
    } else if (col <= 5) {
        c_start = 3;
        c_end = 5;
    } else  {
        c_start = 6;
        c_end = 8;
    }

    for (r = r_start; r <= r_end; ++r) {
        for (c = c_start; c <= c_end; ++c) {
            if (get_value_in(array, r, c) == value) {
                return TRUE;
            }
        }
    }
    return FALSE;
}


/** Checks if the puzzle is full
 *
 * @param array
 * @param row
 * @param col
 * @return
 */
int is_full(int (*array)[NUM_COLS], int row, int col) {
    int r, c;
    for (r = 0; r < NUM_ROWS; r++) {
        for (c = 0; c < NUM_COLS; c++) {
            int value = get_value_in(array, r, c);
            if (!(abs(value) > 0)) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

/** Resets non-permanent values to 0
 *
 */
void reset(int (*array)[NUM_COLS]) {
    int r, c;
    for (r = 0; r < NUM_ROWS; r++) {
        for (c = 0; c < NUM_COLS; c++) {
            int value = get_value_in(array, r, c);
            if (value > 0) {
                reset_cell(array, r, c);
            }
        }
    }
}

int test(int (*array)[NUM_COLS]) {
    if (sudoku_solver(array)) {
        printf("SOLVER is probably working\n");
        return TRUE;
    } else {
        printf("SOLVER is NOT working\n");
        return FALSE;
    }
}

int main(void) {
    int board[NUM_ROWS][NUM_COLS];
    int sample_board[NUM_ROWS][NUM_COLS];
    create_empty_puzzle(sample_board);
    create_sample_puzzle(sample_board);
    display(sample_board);
    //printf("value in row: %d\n", value_in_row(sample_board, 0, 4));
    sudoku_solver(sample_board);
    return 1;
}