#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int masterBoardStateArray[9][9]; //0 is blank square, number otherwise

int originalPuzzleLocations[9][9];  //booleans for if the square can be changed

int possibleValues[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int newPuzzle[9][9];

int newPuzzleSolved[9][9];



int isFull();

void createPuzzle() {
    //should take array, row, column
}

void displayPuzzle() {
    //should take array, row, column

}

void setPuzzleValue(int row, int column, int value) {
    masterBoardStateArray[column][row] = value;
}

void addGuess(int row, int column, int value) {
    if (originalPuzzleLocations[column][row] == 0) {
        //indicates can be changed, not part of original puzzle
        masterBoardStateArray[column][row] = value;
    }
}

void removeGuess(int row, int column) {
    if (originalPuzzleLocations[column][row] == 0) {
        //indicates can be changed, not part of original puzzle
        masterBoardStateArray[column][row] = 0;
    }
    else {
        printf("Sorry you can't remove a number that is part of the original puzzle.\n");
    }
}

int checkPuzzle() {
    //returns 1 if puzzle is okay

    if (isFull() != 1) {
        return 0;
    }
    //check each column
    for (int i = 0; i < 9; i++) {
        //go across
        int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int j = 0; j < 9; j++) {
            //go down the column
            if (arr[masterBoardStateArray[j][i] - 1] == 0) {
                return 0;
            }
            else {
                arr[masterBoardStateArray[j][i] - 1] = 0;
            }
        }
    }
    //check each row
    for (int j = 0; j < 9; j++) {
        //go across
        int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (int i = 0; i < 9; i++) {
            //go down the column
            if (arr[masterBoardStateArray[j][i] - 1] == 0) {
                return 0;
            }
            else {
                arr[masterBoardStateArray[j][i] - 1] = 0;
            }
        }
    }
    //check each 3x3
    for (int startingColumn = 0; startingColumn < 9; startingColumn += 3) {
        for (int startingRow = 0; startingRow < 9; startingRow += 3) {
            int arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            for (int i = startingColumn; i < startingColumn + 3; i++) {
                for (int j = startingRow; j < startingRow + 3; j++) {
                    if (arr[masterBoardStateArray[j][i] - 1] == 0) {
                        return 0;
                    }
                    else {
                        arr[masterBoardStateArray[j][i] - 1] = 0;
                    }
                }
            }
        }
    }

    return 0;
}

int getValueOfSquare(int row, int column) {
    return masterBoardStateArray[column][row];
}

int valueAllowedInThreeByThree(int row, int column, int valueToCheck) {
    //look at 3 x 3 area first
    int groupAcross = column/3;
    int groupDown = row/3;
    int startColumn = 3 * groupAcross;
    int finishColumn = startColumn + 2;
    int startRow = 3 * groupDown;
    int finishRow = startRow + 2;

    for (int i = startRow; i <= finishRow; i++) {
        for (int j = startColumn; j <= finishColumn; j++) {
            if (newPuzzle[i][j] == valueToCheck) {
                return 0;
            }
        }
    }
    return 1;
}

int valueAllowedInRowAndColumn(int row, int column, int valueToCheck) {
    //TODO not complete, just copy and paste
    //check column
    for (int j = 0; j < 9; j++) {
        //go down the column
        if (newPuzzle[j][column] == valueToCheck) {
            return 0;
        }
    }
    //check row
    for (int i = 0; i < 9; i++) {
        //go down the column
        if (newPuzzle[row][i] == valueToCheck) {
            return 0;
        }
    }
    return 1;

}

int numberAllowedInSquare(int row, int column, int valueToCheck) {
    for (int i = 0; i < 9; i++) {
        if (newPuzzle[i][column] == valueToCheck || newPuzzle[row][i] == valueToCheck) {
            return 0;
        }
    }

    int groupAcross = column/3;
    int groupDown = row/3;
    int startColumn = 3 * groupAcross;
    int finishColumn = startColumn + 2;
    int startRow = 3 * groupDown;
    int finishRow = startRow + 2;

    for (int i = startRow; i <= finishRow; i++) {
        for (int j = startColumn; j <= finishColumn; j++) {
            if (newPuzzle[i][j] == valueToCheck) {
                return 0;
            }
        }
    }
    return 1;
}

void displayValuesThatCanBePlayedInASquare(int row, int column){

    for (int i = 0; i < 9; i++) {
        if (valueAllowedInRowAndColumn(row, column, possibleValues[i]) == 0) {
            possibleValues[i] = 0;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (possibleValues[i] != 0) {
            printf("%d\t", possibleValues[i]);
        }
    }

    for (int i = 0; i < 9; i++) {
        possibleValues[i] = i + 1;
    }
}

int isFull(int puzzle[][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (puzzle[j][i] != 0) {
                return 0;
            }
        }
    }
    return 1;
}

void resetBoard() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (originalPuzzleLocations[j][i] != 1) {
                masterBoardStateArray[j][i] = 0;
            }
        }
    }
}

int createNewPuzzle() {

    //set all values in newPuzzle to 0
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            newPuzzle[j][i] = 0;
        }
    }

    int startingAmountNeeded = 25;
    //fewest clues possible for proper sudoku is 17
    int numbersInsertedCount = 0;
    int maxInitialNumbersInRow = 5;
    int maxInitialNumbersInColumn = 5;
    int maxInitialNumbersInBox = 5;
    srand(time(0));

    int whileLoopCount = 0;

    while (numbersInsertedCount < startingAmountNeeded) {
        whileLoopCount++;
//        printf("while loop: ");
//        printf("%d\n", whileLoopCount);

        if (whileLoopCount > 10000000) {
            printf("trying again\n");
            return 0;
        }

        int column = rand() % 9;
        int row = rand() % 9;

        //TODO mixed up rows and columns
        int possibleValues[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; //a one means it's a viable number at that index

        //check if that place already has a number
        if (newPuzzle[row][column] != 0){
            continue;
        }

        int groupAcross = column/3;
        int groupDown = row/3;
        //if that section of 3x3 needs more numbers
        int startColumn = 3 * groupAcross;
        int finishColumn = startColumn + 2;
        int startRow = 3 * groupDown;
        int finishRow = startRow + 2;
        int count = 0;
        for (int j = startRow; j <= finishRow; j++) {
            for (int i = startColumn; i <= finishColumn; i++) {
                if (masterBoardStateArray[j][i] != 0) {
                    count++;
                    possibleValues[masterBoardStateArray[j][i] - 1] = 0;
                }
            }
        }
        if (count == maxInitialNumbersInBox) {
            continue;
        }
        //if that row needs more
        count = 0;
        for (int i = 0; i < 9; i++) {
            if (newPuzzle[row][i] != 0) {
                count++;
                possibleValues[masterBoardStateArray[row][i] - 1] = 0;
            }
        }
        if (count > maxInitialNumbersInRow - 1) {
            continue;
        }

        //if that column needs more
        count = 0;
        for (int j = 0; j < 9; j++) {
            if (newPuzzle[j][column] != 0) {
                count++;
                possibleValues[masterBoardStateArray[j][column] - 1] = 0;
            }
        }
        if (count > maxInitialNumbersInRow - 1) {
            continue;
        }

        //count number of 1s still in array
        count = 0;
        for (int i = 0; i < 9; i++) {
            if (possibleValues[i] == 1) {
                count++;
            }
        }
        if (count == 0) {
            return 0;
        }

        //generate random number from 0 to number of 1s still in array

        int whichPossibleValueStillAtOneToInsert = rand() % count; //will range from 0 to count - 1

        int countOfOnes = 0;
        int valueToInsert = 0; //initialization

        for (int i = 0; i < 9; i++) { //go through possibleValues index
            if (possibleValues[i] == 1) {
                if (countOfOnes == whichPossibleValueStillAtOneToInsert) {
                    valueToInsert = i + 1;
                    break;
                }
                countOfOnes++;
            }
        }

        //if (valueAllowedInRowAndColumn(row, column, valueToInsert) == 1 && valueAllowedInThreeByThree(row, column, valueToInsert) == 1) {
        if (numberAllowedInSquare(row, column, valueToInsert) == 1) {
                newPuzzle[row][column] = valueToInsert;
            //insert that number into puzzle
            numbersInsertedCount++;
            printf("inserted %d values: ", numbersInsertedCount);
            printf("%d\n", valueToInsert);

        }


    }

    //copy new puzzle to

    //TODO test whether puzzle is solvable
    //test whether it has a single solution
    printf("%d\n", whileLoopCount);
    return 1;
}

void displayNewPuzzle() {
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            printf("%d\t", newPuzzle[j][i]);
        }
        printf("\n");
    }
}


int valueAllowed(int puzzle[][8], int row, int column, int valueToCheck) {
    //look at 3 x 3 area first

    if (puzzle[row][column] != 0) {
        return 0;
    }
    int groupAcross = column/3;
    int groupDown = row/3;
    int startColumn = 3 * groupAcross;
    int finishColumn = startColumn + 2;
    int startRow = 3 * groupDown;
    int finishRow = startRow + 2;

    for (int i = startRow; i <= finishRow; i++) {
        for (int j = startColumn; j <= finishColumn; j++) {
            if (puzzle[i][j] == valueToCheck) {
                return 0;
            }
        }
    }

    for (int j = 0; j < 9; j++) {
        //go down the column
        if (puzzle[j][column] == valueToCheck) {
            return 0;
        }
    }
    //check row
    for (int i = 0; i < 9; i++) {
        //go down the column
        if (puzzle[row][i] == valueToCheck) {
            return 0;
        }
    }
    return 1;
}


void displayPuzzleSolved() {
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            printf("%d\t", newPuzzleSolved[j][i]);
        }
        printf("\n");
    }
}

int displayPuzzleSolvedPointer(int (*puzzle)[9][9]) {
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            printf("%d\t", *puzzle[j][i]);
        }
        printf("\n");
    }
}
int solvePuzzle(int (*puzzle)[9][9], int row, int column) {

    if (row == 9) {
        printf("Puzzle Solved: \n");
        displayPuzzleSolved();
        printf("\n");
        displayPuzzleSolvedPointer(puzzle);

        return 1;
    }

    //this section moves on past numbers that are already set
    //if ((*puzzle)[row][column]) {
    if (newPuzzle[row][column] != 0) {
        if (column == 9) {
            if (solvePuzzle(puzzle, row + 1, 0) == 1) {
                return 1;
            }
//            return (solvePuzzle(puzzle, row + 1, 0) != 0);
        }
        else {
            if (solvePuzzle(puzzle, row, column + 1) == 1) {
                return 1;
            }
//            return (solvePuzzle(puzzle, row, column + 1) != 0);

        }
//        newPuzzleSolved[row][column] = 0;
//        return 0;
    }

    for (int numToTry = 1; numToTry <= 9; numToTry++) {
        if (valueAllowed((*puzzle), row, column, numToTry)) {
            newPuzzleSolved[row][column] = numToTry;
            *puzzle[row][column] = numToTry;
            if (column == 9) {
//                if (solvePuzzle(puzzle, row + 1, 0) == 1) {
//                    return 1;
//                }
                return (solvePuzzle(puzzle, row + 1, 0) != 0);

            }
            else {
//                if (solvePuzzle(puzzle, row, column + 1)) {
//                    return 1;
//                }
                return (solvePuzzle(puzzle, row, column + 1) != 0);
            }
        }
    }

//    newPuzzleSolved[row][column] = 0;
    return 0;

}

void copyNewPuzzle() {
    for (int j = 0; j < 9; j++) {
        for (int i = 0; i < 9; i++) {
            newPuzzleSolved[j][i] = newPuzzle[j][i];
        }
        printf("\n");
    }
}

int main() {
    printf("Hello, this is the Sudoku Solver!\n");

    while (createNewPuzzle() == 0) {
        createNewPuzzle();
    }
    displayNewPuzzle();
    copyNewPuzzle();
    int (*pointer)[9][9];
    pointer = &newPuzzle;
    int solvable = solvePuzzle(pointer, 0, 0);
    printf("%d\n", solvable);

    return 0;
}