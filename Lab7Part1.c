/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lab7Part1.c
 * Author: liujue1
 *
 * Created on March 20, 2017, 12:30 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * 
 */

void printBoard(char board[][26], int n);
bool positionInBounds(int n, int rowNum, int colNum);
bool checkLegalInDirection(char board[][26], int n, char row, char col,
        char colour, int deltaRow, int deltaCol);
void flipBoard(char board[][26], int n, char row, char col,
        char colour, int deltaRow, int deltaCol);
int countScore(char board[][26], int n, char row, char col,
        char colour, int deltaRow, int deltaCol);
void computerMove(char color, char board[][26], int n, char *p, char *q);
bool checkAvailable(char color, char board[][26], int n);
void whoWin(int * numW, int * numB, int dimension, char board[][26]);

int main(int argc, char** argv) {
    int dimension;
    char colourComputer;
    char row, col;
    printf("Enter the board dimension: ");
    scanf("%d", &dimension);
    char board[26][26];
    char moveRow, moveCol;
    bool check, check2;
    int numW, numB;
    bool hello = false;

    // set and print the default board
    for (int row = 0; row != dimension; row++) {
        for (int col = 0; col != dimension; col++) {
            board[row][col] = 'U';
            if (row == dimension / 2 - 1 && col == dimension / 2 - 1)
                board[row][col] = 'W';
            else if (row == dimension / 2 - 1 && col == dimension / 2)
                board[row][col] = 'B';
            else if (row == dimension / 2 && col == dimension / 2 - 1)
                board[row][col] = 'B';
            else if (row == dimension / 2 && col == dimension / 2)
                board[row][col] = 'W';
        }
    }
    
    // determine which color of the pieces should the computer play
    printf("Computer plays (B/W) : ");
    scanf(" %c", &colourComputer);
    printBoard(board, dimension);

    bool g, h, i, j, k, l, m, q;
    // when the user plays first
    if (colourComputer == 'W') {
        for (;;) {
            check = checkAvailable('B', board, dimension);
            
            //input user moves and then flip the board
            if (check == true) {
                printf("Enter move for colour B (RowCol): ");
                scanf(" %c", &row);
                scanf(" %c", &col);
                g = checkLegalInDirection(board, dimension, row, col, 'B', -1, -1);
                h = checkLegalInDirection(board, dimension, row, col, 'B', -1, 0);
                i = checkLegalInDirection(board, dimension, row, col, 'B', -1, 1);
                j = checkLegalInDirection(board, dimension, row, col, 'B', 0, 1);
                k = checkLegalInDirection(board, dimension, row, col, 'B', 1, 1);
                l = checkLegalInDirection(board, dimension, row, col, 'B', 1, 0);
                m = checkLegalInDirection(board, dimension, row, col, 'B', 1, -1);
                q = checkLegalInDirection(board, dimension, row, col, 'B', 0, -1);

                if (g == true || h == true || i == true || j == true || 
                        k == true || l == true || m == true || q == true) {
                    flipBoard(board, dimension, row, col, 'B', -1, -1);
                    flipBoard(board, dimension, row, col, 'B', -1, 0);
                    flipBoard(board, dimension, row, col, 'B', -1, 1);
                    flipBoard(board, dimension, row, col, 'B', 0, 1);
                    flipBoard(board, dimension, row, col, 'B', 1, 1);
                    flipBoard(board, dimension, row, col, 'B', 1, 0);
                    flipBoard(board, dimension, row, col, 'B', 1, -1);
                    flipBoard(board, dimension, row, col, 'B', 0, -1);
                    board[row - 'a'][col - 'a'] = 'B';
                    printBoard(board, dimension);
                } else {
                    printf("Invalid move.\n");
                    printf("W player wins.");
                    hello = true;
                    break;
                }
            } else {
                check = checkAvailable('W', board, dimension);
                if (check == false) {
                    break;
                }
                printf("B player has no valid move.\n");
            }

            // computer moves and then flip the board
            computerMove('W', board, dimension, &moveRow, &moveCol);
            g = checkLegalInDirection(board, dimension, moveRow, moveCol, 'W', -1, -1);
            h = checkLegalInDirection(board, dimension, moveRow, moveCol, 'W', -1, 0);
            i = checkLegalInDirection(board, dimension, moveRow, moveCol, 'W', -1, 1);
            j = checkLegalInDirection(board, dimension, moveRow, moveCol, 'W', 0, 1);
            k = checkLegalInDirection(board, dimension, moveRow, moveCol, 'W', 1, 1);
            l = checkLegalInDirection(board, dimension, moveRow, moveCol, 'W', 1, 0);
            m = checkLegalInDirection(board, dimension, moveRow, moveCol, 'W', 1, -1);
            q = checkLegalInDirection(board, dimension, moveRow, moveCol, 'W', 0, -1);

            if (g == true || h == true || i == true || j == true || k == true 
                    || l == true || m == true || q == true) {
                flipBoard(board, dimension, moveRow, moveCol, 'W', -1, -1);
                flipBoard(board, dimension, moveRow, moveCol, 'W', -1, 0);
                flipBoard(board, dimension, moveRow, moveCol, 'W', -1, 1);
                flipBoard(board, dimension, moveRow, moveCol, 'W', 0, 1);
                flipBoard(board, dimension, moveRow, moveCol, 'W', 1, 1);
                flipBoard(board, dimension, moveRow, moveCol, 'W', 1, 0);
                flipBoard(board, dimension, moveRow, moveCol, 'W', 1, -1);
                flipBoard(board, dimension, moveRow, moveCol, 'W', 0, -1);
                board[moveRow - 'a'][moveCol - 'a'] = 'W';
                printf("Computer places W at %c%c.\n", moveRow, moveCol);
                printBoard(board, dimension);

            } else {

                check = checkAvailable('B', board, dimension);

                if (check == false) {
                    break;
                }
                printf("W player has no valid move.\n");

            }
        }
        whoWin(&numW, &numB, dimension, board);
        if (numW > numB && hello == false) {
            printf("w player wins.");
        } else if (numB > numW && hello == false) {
            printf("B player wins.");
        } else if (numB == numW && hello == false) {
            printf("Draw!");
        }
    }
    
    //when the computer moves first
    else {
        for (;;) {
            
            //computer moves and then flip the board
            computerMove('B', board, dimension, &moveRow, &moveCol);
            g = checkLegalInDirection(board, dimension, moveRow, moveCol, 'B', -1, -1);
            h = checkLegalInDirection(board, dimension, moveRow, moveCol, 'B', -1, 0);
            i = checkLegalInDirection(board, dimension, moveRow, moveCol, 'B', -1, 1);
            j = checkLegalInDirection(board, dimension, moveRow, moveCol, 'B', 0, 1);
            k = checkLegalInDirection(board, dimension, moveRow, moveCol, 'B', 1, 1);
            l = checkLegalInDirection(board, dimension, moveRow, moveCol, 'B', 1, 0);
            m = checkLegalInDirection(board, dimension, moveRow, moveCol, 'B', 1, -1);
            q = checkLegalInDirection(board, dimension, moveRow, moveCol, 'B', 0, -1);

            if (g == true || h == true || i == true || j == true || k == true 
                    || l == true || m == true || q == true) {
                flipBoard(board, dimension, moveRow, moveCol, 'B', -1, -1);
                flipBoard(board, dimension, moveRow, moveCol, 'B', -1, 0);
                flipBoard(board, dimension, moveRow, moveCol, 'B', -1, 1);
                flipBoard(board, dimension, moveRow, moveCol, 'B', 0, 1);
                flipBoard(board, dimension, moveRow, moveCol, 'B', 1, 1);
                flipBoard(board, dimension, moveRow, moveCol, 'B', 1, 0);
                flipBoard(board, dimension, moveRow, moveCol, 'B', 1, -1);
                flipBoard(board, dimension, moveRow, moveCol, 'B', 0, -1);
                board[moveRow - 'a'][moveCol - 'a'] = 'B';
                printf("Computer places B at %c%c.\n", moveRow, moveCol);
                printBoard(board, dimension);
            } else {
                check = checkAvailable('W', board, dimension);

                if (check == false) {
                    break;
                }
                printf("B player has no valid move.\n");
            }
            check = checkAvailable('W', board, dimension);
            check2 = checkAvailable('B', board, dimension);
            if (check == false && check2 == true) {
                printf("W player has no valid move.");
                continue;
            } else if (check == false && check2 == false) {
                break;
            }

            // input user's move and then flip the board
            printf("Enter move for colour W (RowCol): ");
            scanf(" %c", &row);
            scanf(" %c", &col);
            g = checkLegalInDirection(board, dimension, row, col, 'W', -1, -1);
            h = checkLegalInDirection(board, dimension, row, col, 'W', -1, 0);
            i = checkLegalInDirection(board, dimension, row, col, 'W', -1, 1);
            j = checkLegalInDirection(board, dimension, row, col, 'W', 0, 1);
            k = checkLegalInDirection(board, dimension, row, col, 'W', 1, 1);
            l = checkLegalInDirection(board, dimension, row, col, 'W', 1, 0);
            m = checkLegalInDirection(board, dimension, row, col, 'W', 1, -1);
            q = checkLegalInDirection(board, dimension, row, col, 'W', 0, -1);

            if (g == true || h == true || i == true || j == true || k == true 
                    || l == true || m == true || q == true) {
                flipBoard(board, dimension, row, col, 'W', -1, -1);
                flipBoard(board, dimension, row, col, 'W', -1, 0);
                flipBoard(board, dimension, row, col, 'W', -1, 1);
                flipBoard(board, dimension, row, col, 'W', 0, 1);
                flipBoard(board, dimension, row, col, 'W', 1, 1);
                flipBoard(board, dimension, row, col, 'W', 1, 0);
                flipBoard(board, dimension, row, col, 'W', 1, -1);
                flipBoard(board, dimension, row, col, 'W', 0, -1);
                board[row - 'a'][col - 'a'] = 'W';
                printBoard(board, dimension);

            } else {
                printf("Invalid move.\n");
                printf("B player wins.");
                hello = true;
                break;
            }



        }
        
        // declare who is the winner
        whoWin(&numW, &numB, dimension, board);
        if (numW > numB && hello == false) {
            printf("w player wins.");
        } else if (numB > numW && hello == false) {
            printf("B player wins.");
        } else if (numB == numW && hello == false) {
            printf("Draw!");
        }
    }

    return (EXIT_SUCCESS);

}

// print the board

void printBoard(char board[][26], int n) {

    printf("  ");
    for (char i = 'a'; i != 'a' + n; i++) {
        printf("%c", i);
    }
    printf("\n");

    int s = 'a';

    for (int row = 0; row != n; row++) {
        printf("%c ", s);
        s++;
        for (int col = 0; col != n; col++) {
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}

// check if the position is in bounds 

bool positionInBounds(int n, int rowNum, int colNum) {
    bool judge = true;
    if (rowNum + 1 > n || rowNum < 0 || colNum + 1 > n || colNum < 0)
        judge = false;
    return (judge);
}

//check if the position is legal to move in one direction

bool checkLegalInDirection(char board[][26], int n, char row, char col,
        char colour, int deltaRow, int deltaCol) {
    int rowNum = row - 'a';
    int colNum = col - 'a';
    bool q;
    char anticolour = 'B';
    if (colour == 'B')
        anticolour = 'W';
    bool judge = positionInBounds(n, rowNum, colNum);
    if (board[rowNum][colNum] == 'U') {
        rowNum = rowNum + deltaRow;
        colNum = colNum + deltaCol;
        if (board[rowNum][colNum] == anticolour) {
            rowNum = rowNum + deltaRow;
            colNum = colNum + deltaCol;
            for (; judge == true; rowNum = rowNum + deltaRow,
                    colNum = colNum + deltaCol) {
                judge = positionInBounds(n, rowNum, colNum);
                if (judge == false)
                    q = false;
                if (board[rowNum][colNum] == colour) {
                    q = true;
                    judge = false;
                } else if (board[rowNum][colNum] == 'U') {
                    q = false;
                    judge = false;
                }
            }
        } else
            q = false;
    } else
        q = false;
    return (q);
}

//flip the tiles 

void flipBoard(char board[][26], int n, char row, char col,
        char colour, int deltaRow, int deltaCol) {
    int rowNum = row - 'a';
    int colNum = col - 'a';
    bool q;
    char anticolour = 'B';
    if (colour == 'B')
        anticolour = 'W';
    bool judge = positionInBounds(n, rowNum, colNum);
    if (board[rowNum][colNum] == 'U') {
        rowNum = rowNum + deltaRow;
        colNum = colNum + deltaCol;
        if (board[rowNum][colNum] == anticolour) {
            rowNum = rowNum + deltaRow;
            colNum = colNum + deltaCol;
            for (; judge == true; rowNum = rowNum + deltaRow,
                    colNum = colNum + deltaCol) {
                judge = positionInBounds(n, rowNum, colNum);
                if (judge == false)
                    q = false;
                if (board[rowNum][colNum] == colour) {
                    q = true;
                    judge = false;
                    do {
                        rowNum = rowNum - deltaRow;
                        colNum = colNum - deltaCol;
                        board[rowNum][colNum] = colour;
                    } while (rowNum != row - 'a' + deltaRow ||
                            colNum != col - 'a' + deltaCol);
                } else if (board[rowNum][colNum] == 'U') {
                    q = false;
                    judge = false;
                }
            }
        } else
            q = false;
    } else
        q = false;
}

// count the score of each available tile
int countScore(char board[][26], int n, char row, char col,
        char colour, int deltaRow, int deltaCol) {
    int count = 0;
    int rowNum = row - 'a';
    int colNum = col - 'a';
    bool q;
    char anticolour = 'B';
    if (colour == 'B')
        anticolour = 'W';
    bool judge = positionInBounds(n, rowNum, colNum);
    if (board[rowNum][colNum] == 'U') {
        rowNum = rowNum + deltaRow;
        colNum = colNum + deltaCol;
        if (board[rowNum][colNum] == anticolour) {
            rowNum = rowNum + deltaRow;
            colNum = colNum + deltaCol;
            for (; judge == true; rowNum = rowNum + deltaRow,
                    colNum = colNum + deltaCol) {
                judge = positionInBounds(n, rowNum, colNum);
                if (judge == false)
                    q = false;
                if (board[rowNum][colNum] == colour) {
                    q = true;
                    judge = false;
                    do {
                        rowNum = rowNum - deltaRow;
                        colNum = colNum - deltaCol;
                        count++;
                    } while (rowNum != row - 'a' + deltaRow ||
                            colNum != col - 'a' + deltaCol);
                } else if (board[rowNum][colNum] == 'U') {
                    q = false;
                    judge = false;
                }
            }
        } else
            q = false;
    } else
        q = false;
    return (count);
}

// figure out the best place to put the piece for computer
void computerMove(char color, char board[][26], int n, char *p, char *q) {
    int totalScore = 0;
    int bestScore = -1;
    char bestRow, bestCol;
    char substitude;

    for (char row = 'a'; row <= 'a' + n - 1; row++) {
        for (char col = 'a'; col <= 'a' + n - 1; col++) {

            totalScore = countScore(board, n, row, col, color, -1, -1)
                    + countScore(board, n, row, col, color, -1, 0)
                    + countScore(board, n, row, col, color, -1, 1)
                    + countScore(board, n, row, col, color, 0, 1)
                    + countScore(board, n, row, col, color, 1, 1)
                    + countScore(board, n, row, col, color, 1, 0)
                    + countScore(board, n, row, col, color, 1, -1)
                    + countScore(board, n, row, col, color, 0, -1);

            if (totalScore > bestScore) {
                bestRow = row;
                bestCol = col;
                bestScore = totalScore;
            } else if (totalScore == bestScore) {
                if (row < bestRow) {
                    bestRow = row;
                    bestCol = col;
                    bestScore = totalScore;
                } else {
                    if (row == bestRow) {
                        if (col < bestCol) {
                            bestRow = row;
                            bestCol = col;
                            bestScore = totalScore;
                        }
                    }
                }
            }
        }
    }
    *p = bestRow;
    *q = bestCol;
}

//count who have more pieces 
void whoWin(int * numW, int * numB, int dimension, char board[][26]) {
    int countW = 0;
    int countB = 0;
    for (char row = 'a'; row != 'a' + dimension; row++) {
        for (char col = 'a'; col != 'a' + dimension; col++) {
            if (board[row - 'a'][col - 'a'] == 'W') {
                countW = countW + 1;
            } else if (board[row - 'a'][col - 'a'] == 'B') {
                countB = countB + 1;
            }
        }
    }
    *numW = countW;
    *numB = countB;
}

//check if there is available move for the specific color
bool checkAvailable(char color, char board[][26], int n) {
    bool g, h, i, j, k, l, m, q;
    bool check = false;
    for (char row = 'a'; row <= 'a' + n - 1; row++) {
        for (char col = 'a'; col <= 'a' + n - 1; col++) {
            g = checkLegalInDirection(board, n, row, col, color, -1, -1);
            h = checkLegalInDirection(board, n, row, col, color, -1, 0);
            i = checkLegalInDirection(board, n, row, col, color, -1, 1);
            j = checkLegalInDirection(board, n, row, col, color, 0, 1);
            k = checkLegalInDirection(board, n, row, col, color, 1, 1);
            l = checkLegalInDirection(board, n, row, col, color, 1, 0);
            m = checkLegalInDirection(board, n, row, col, color, 1, -1);
            q = checkLegalInDirection(board, n, row, col, color, 0, -1);
            if (g == true || h == true || i == true || j == true || k == true 
                    || l == true || m == true
                    || q == true)
                check = true;
        }
    }
    return (check);
}
