#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

/** Initializes all cells to EMPTY value
 *
 * @param array Reference to array
 */
void create_empty_puzzle(int (*array)[NUM_COLS]) {
    int r, c;
    for (r = 0; r < NUM_ROWS; ++r) {
        for (c = 0; c < NUM_COLS; ++c) {
            array[r][c] = EMPTY;
        }
    }
}

/** Generates a new radom puzzle
 *
 * @param array Reference to array
 */
void create_new_puzzle(int (*array)[NUM_COLS]) {
    int test_array[NUM_ROWS][NUM_COLS];

    create_empty_puzzle(array);
    create_empty_puzzle(test_array);

    //fewest clues possible for proper sudoku is 17
    int starting_amount_needed = 19;
    int numbers_inserted = 0;

    int possible_values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    while (numbers_inserted < starting_amount_needed) {
        printf("Added: %d numbers", numbers_inserted);
        //get random unassigned cell
        int random_row = generate_random_number(0, 8);
        int random_col = generate_random_number(0, 8);

        while (get_value_in(array, random_row, random_col) != EMPTY) {
            random_row = generate_random_number(0, 8);
            random_col = generate_random_number(0, 8);
        }

        int test_value;
        int random_possible_value_index = generate_random_number(0, 8);

        int i;
        int index;
        for (i = 0; i < 9; ++i) {
            index = (i + random_possible_value_index) % 8;
            test_value = possible_values[index];
            if (is_legal_move(array, random_row, random_col, test_value)) {
                add_permanent(test_array, random_row, random_col, test_value);
                if (sudoku_solver(test_array)) {
                    add_permanent(array, random_row, random_col, test_value);
                    copy_array(array, test_array);
                    break;
                }
            }
        }
        numbers_inserted += 1;
    }
    display(array);
}

/** Copies the values from source to target array
 *
 * @param source_array  Source array
 * @param target_array  Target array
 */
void copy_array(int (*source_array)[NUM_COLS], int (*target_array)[NUM_COLS]) {
    int r, c;
    reset(target_array);
    for (r = 0; r < NUM_ROWS; ++r) {
        for (c = 0; c < NUM_COLS; ++c) {
            add_permanent(target_array, r, c, get_value_in(source_array, r, c));
        }
    }
}

/** Generates a random int from range
 *
 * @param low  Low value
 * @param high  High value
 * @return  Random value
 */
int generate_random_number(int low, int high) {
    srand(time(0));
    return (rand() % (high - low + 1)) + low;
}

/** Prints a given array
 *
 * @param array  Array
 */
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

/** Sets the value of a cell
 *
 * @param array  Array to update
 * @param row  Row index
 * @param col  Column index
 * @param value  Value to add
 * @param is_permanent  Whether it is a permanent value
 */
void set_cell_value(int (*array)[NUM_COLS], int row, int col, int value, int is_permanent) {
    if (value >= 0 && value < 10) {
        if (is_permanent) {
            array[row][col] = -1 * value;
        } else {
            array[row][col] = value;
        }
    }
}

/** Adds the user's guess
 *
 * @param array  Array to update
 * @param row  Row index
 * @param col  Column index
 * @param value  Value to add
 */
void add_guess(int (*array)[NUM_COLS], int row, int col, int value) {
    set_cell_value(array, row, col, value, FALSE);
}

/** Adds permanent values to the puzzle
 *
 * @param array  Array to update
 * @param row  Row index
 * @param col  Column index
 * @param value  Value to add
 */
void add_permanent(int (*array)[NUM_COLS], int row, int col, int value) {
    set_cell_value(array, row, col, value, TRUE);
}

/** Resets a cell's value to empty value
 *
 * @param array  Array to update
 * @param row  Row index
 * @param col  Column index
 */
void reset_cell(int (*array)[NUM_COLS], int row, int col) {
    set_cell_value(array, row, col, EMPTY, FALSE);
}

/** Gets the current value in a cell
 *
 * @param array  Array to update
 * @param row  Row index
 * @param col  Column index
 */
int get_value_in(int (*array)[NUM_COLS], int row, int col) {
    return abs(array[row][col]);
}

/** Solves the sudoku with the back-tracking algorithm
 *
 * @param array  Puzzle to solve
 * @return  TRUE if solved, else FALSE
 */
int sudoku_solver(int (*array)[NUM_COLS]) {
    int r, c;
    int test_value;
    for (r = 0; r < NUM_ROWS; ++r) {
        for (c = 0; c < NUM_COLS; ++c) {
            if (array[r][c] == EMPTY) {
                for (test_value = MIN_VALUE; test_value <= MAX_VALUE; ++test_value) {
                    if (is_legal_move(array, r, c, test_value)) {
                        add_guess(array, r, c, test_value);
                        if (sudoku_solver(array) == TRUE) {
                            return TRUE;
                        } else {
                            reset_cell(array, r, c);
                        }
                    }
                }
                return FALSE;
            }
        }
    }
    return TRUE;
}

/** Checks if the given value to add is legal
 *
 * @param array  Array to update
 * @param row  Row index
 * @param col  Column index
 * @param value  Value to check
 */
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

/** Checks if the cell is a permanent cell
 *
 * @param array  Array to check
 * @param row  Row index
 * @param col Column index
 * @return Whether it is a permanent cell
 */
int is_permanent_value(int (*array)[NUM_COLS], int row, int col) {
    if (get_value_in(array, row, col) < 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/** Checks if the value is in a given row
 *
 * @param array  Array to check
 * @param row  Row index
 * @return Whether value is in row
 */
int value_in_row(int (*array)[NUM_COLS], int row, int value) {
    int c;
    for (c = 0; c < NUM_COLS; ++c) {
        if (get_value_in(array, row, c) == value) {
            return TRUE;
        }
    }
    return FALSE;
}

/** Checks if the value is in a given col
 *
 * @param array  Array to check
 * @param col Column index
 * @return Whether value is in column
 */
int value_in_col(int (*array)[NUM_COLS], int col, int value) {
    int r;
    for (r = 0; r < NUM_ROWS; ++r) {
        if (get_value_in(array, r, col) == value) {
            return TRUE;
        }
    }
    return FALSE;
}

/** Checks if the value is in a given col
 *
 * @param array  Array to check
 * @param row Row index
 * @param col Column index
 * @return Whether value is in the associated 9x9 square
 */
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
 */
void reset(int (*array)[NUM_COLS]) {
    int r, c;
    for (r = 0; r < NUM_ROWS; r++) {
        for (c = 0; c < NUM_COLS; c++) {
            int value = array[r][c];
            if (value > 0) {
                reset_cell(array, r, c);
            }
        }
    }
}

int main(void) {
    setbuf(stdout, NULL);
    int board[NUM_ROWS][NUM_COLS];
    int sample_board[NUM_ROWS][NUM_COLS];
    //create_empty_puzzle(sample_board);
    //create_sample_puzzle(sample_board);
    create_empty_puzzle(board);
    printf("generating new board\n");
    create_new_puzzle(board);
    display(board);
    return 1;
}