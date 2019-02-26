#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define EMPTY 0
#define NUM_ROWS 9
#define NUM_COLS 9

void create_empty_puzzle(int * array, int row, int col) {
    array = {{EMPTY}};
}

void display(int * array) {
    int i;
    int j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (!(abs(array[i][j]) > 0 && abs(array[i][j]) < 10)) {
                if (j != 8) {
                    if (j == 2 || j == 5) {
                        printf("%d | ", abs(array[i][j]));
                    } else {
                        printf("%d, ", abs(array[i][j]));
                    }
                } else {
                    printf("%d", abs(array[i][j]));
                }
            }
        }
    }
}


void set_cell_value(int * array, int row, int col, int value, int is_permanent) {
    if (value > 0 && value < 10) {
        if (is_permanent) {
            array[row][col] = -1 * value;
        } else {
            if (array[row][col] > 0 && array[row][col] < 10) {
                array[row][col] = value;
            } else {
                printf("(%d, %d) is a permanent value\n", row, col);
            }
        }
    } else {
        printf("Please provide a valid value [1-9]\n");
    }
}

int check_puzzle(int * array, int row, int col) {
    return 0;
}

int get_value_in(int * array, int row, int col) {
    return array[row][col];
}

int * get_allowed_values(int * array, int * allowed int row, int col) {
    return allowed;
}

/** Checks if the puzzle is full
 *
 * @param array
 * @param row
 * @param col
 * @return
 */
int is_full(int * array, int row, int col) {
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
void reset(int * array) {
    int r, c,;
    for (r = 0; r < NUM_ROWS; r++) {
        for (c = 0; c < NUM_COLS; c++) {
            int value = get_value_in(array, r, c);
            if (value > 0) {
                set_cell_value(array, r, c, EMPTY, FALSE);
            }
        }
    }

}

int main(void) {
    int board[9][9];
    create_sudoku_puzzle(board)
    return 0;
}