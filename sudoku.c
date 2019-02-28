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
    int starting_amount_needed = 25;

    int possible_values[9] = {1, 2, 3, 4, 5, 6, 7, 8 ,9};
    int shuffled_list[81];

    int tries_done = 0;
    int max_tries = 100;
    while (tries_done < max_tries) {
        tries_done += 1;
        shuffle_list(shuffled_list, 81);
        int numbers_inserted = 0;
        while (numbers_inserted < starting_amount_needed) {
            //get random unassigned cell
            int shuffled_index = shuffled_list[numbers_inserted];
            int random_row = shuffled_index / 9;
            int random_col = shuffled_index % 9;

            int test_value;
            int random_possible_value_index = generate_random_number(0, 8);

            int index;
            int i;
            for (i = 0; i < 9; ++i) {
                if (get_value_in(test_array, random_row, random_col) == EMPTY) {
                    index = (i + random_possible_value_index) % 8;
                    test_value = possible_values[index];
                    if (is_legal_move(test_array, random_row, random_col, test_value)) {
                        add_permanent(test_array, random_row, random_col, test_value);
                    }
                }
            }
            numbers_inserted += 1;
        }
        copy_array(test_array, array);
        if (sudoku_solver(test_array)) {
            break;
        } else {
            create_empty_puzzle(test_array);
        }
    }
}

/** Initializes a list from 1 to 81 and shuffles it
 *
 * @param list List[81]
 * @param size size of list
 */
void shuffle_list(int * list, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        list[i] = i;
    }

    size_t p;
    for (p = 0; p < size; p++)
    {
        size_t q = p + rand() / (RAND_MAX / (size - p) + 1);
        int t = list[q];
        list[q] = list[p];
        list[p] = t;
    }
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
    if (!is_permanent_cell(array, row, col)) {
        set_cell_value(array, row, col, value, FALSE);
    } else {
        printf("(%d, %d) is a permanent value!", row, col);
    }
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
    if (!is_permanent_cell(array, row, col) &&
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
int is_permanent_cell(int (*array)[NUM_COLS], int row, int col) {
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

/** Prints possible values of the current cell
 *
 * @param array
 * @param row
 * @param col
 */
void print_possible_values(int (*array)[NUM_COLS], int row, int col) {
    int i;
    for (i = 1; i < MAX_VALUE + 1; ++i) {
        if (is_legal_move(array, row, col, i)) {
            printf("%d, ", i);
        }
    }
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


int main() {
    printf("Hello, this is the Sudoku Solver!\n");

    int puzzle[NUM_ROWS][NUM_COLS];
    int original_puzzle[NUM_ROWS][NUM_COLS];
    create_empty_puzzle(original_puzzle);
    create_empty_puzzle(puzzle);
    create_new_puzzle(original_puzzle);
    copy_array(original_puzzle, puzzle);

    int menuSelection;
    int menuInputCorrect = 0;
    int input;
    int quit = 0;

    printf("Welcome to the array shift program.\n");

    //TODO:
    //create a new puzzle
    display(puzzle);
    //loop to solve puzzle
    do {
        do {
            printf("Enter 1 to input a value.\n");
            printf("Enter 2 to start the puzzle over.\n");
            printf("Enter 3 to show solution.\n");
            printf("Enter 4 to display initial puzzle.\n");
            printf("Enter 5 to end working on this puzzle and create another one.\n");
            printf("Enter 6 to quit program\n");

            scanf("%d", &menuSelection);

            if ((menuSelection > 0 && menuSelection < 7)) {
                menuInputCorrect = 1;
            } else {
                printf("Please enter a valid menu number.\n");
            }
        } while (menuInputCorrect == 0);

        if (menuSelection == 1) {
            int inputCorrectMenu1 = 0;
            do {
                int inputRow, inputColumn;
                printf("What row do you want to add a value to (0 - 8)?\n");
                scanf("%d", &inputRow);
                printf("What column do you want to add a value to (0 - 8)?\n");
                scanf("%d", &inputColumn);
                if (inputRow >= 0 && inputRow < 9 && inputColumn > 0 && inputColumn < 10) {
                    inputCorrectMenu1 = 1;
                    //TODO input value, call method
                    //TODO display puzzle
                    int inputCorrectValue = 0;
                    int menuSelectionValue = 0;
                    do {
                        printf("Enter 1 to input a value.\n");
                        printf("Enter 2 to see possible values.\n");
                        printf("Enter 3 to go back to main menu.\n");

                        scanf("%d", &menuSelectionValue);
                        if ((menuSelectionValue > 0 && menuSelectionValue < 4)) {
                            inputCorrectValue = 1;
                        } else {
                            printf("Please enter a valid menu number.\n");
                        }
                    } while (inputCorrectValue == 0);

                    int inputValue;
                    if (menuSelectionValue == 1) {
                        printf("What value do you want to input?\n");
                        scanf("%d", &inputValue);
                        add_guess(puzzle, inputRow, inputColumn, inputValue);
                        //TODO: if input value is valid, add to puzzle
                        //if not valid goes back to menu
                    } else if (menuSelectionValue == 2) {
                        printf("Possible values:\n");
                        print_possible_values(puzzle, inputRow, inputColumn);
                    } else if (menuSelectionValue == 3){
                        inputCorrectMenu1 = 1;
                    }
                }
            } while (inputCorrectMenu1 == 0);
        }
        else if (menuSelection == 2) {
            copy_array(original_puzzle, puzzle);
        }
        else if (menuSelection == 3) {
            printf("This is the solution: \n");
            sudoku_solver(puzzle);
            display(puzzle);
        }
        else if (menuSelection == 4) {
            //TODO display initial puzzle
            display(original_puzzle);
        }
        else if (menuSelection == 5) {
            printf("Creating another puzzle...\n");
            create_new_puzzle(original_puzzle);
            copy_array(original_puzzle, puzzle);
            //TODO display puzzle
            display(puzzle);
        }
        else {
            quit = 1;
        }
    } while (quit == 0);

    return 0;
}