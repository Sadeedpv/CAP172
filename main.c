// standard C libraries
#include <stdio.h>
/*
Math.h here is imported for the floor function which we will use to
calculate the row and col that the user will play
*/
#include <math.h>
/* To make use of bool values like true and false in c */
#include<stdbool.h>

char board[3][3]; // Tic-Tac-Toe board

void initializeBoard() {
    // Initialize the board with empty values at the start, this function is for that and it returns nothing/void
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

/*
Display the board as a 3D matrix with values from 1-9
This function also returns void
*/
void displayBoard() {
    int count = 1;
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' '){
                printf(" %d ", count);
            }else{
                printf(" %c ", board[i][j]);
            }
            if (j < 2) printf("|");
            count++;
        }
        if (i < 2) printf("\n---|---|---\n");
    }
    printf("\n");
}

/*
Checking for all the possible win combinations in a tic-tac-toe game
*/
int checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return 1; // Row match
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return 1; // Column match
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return 1;

    return 0; // No winner
}

int checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return 0; // Empty space exists, so not a draw yet
        }
    }
    return 1; // Draw
}

void playerMove(int player) {
    int row, col, loc;
    char mark = (player == 1) ? 'X' : 'O';

    while (true) {
        printf("Player %d (%c), enter where you want to play (1-9): ", player, mark);
        scanf("%d", &loc);
        row = floor((loc - 1)/3);
        col = floor((loc-1)%3);

        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = mark;
            break;
        } else{
            printf("Invalid move! Try again.\n");
        }

    }
}

int main() {
    int currentPlayer = 1;

    initializeBoard();

    printf("Welcome to Tic-Tac-Toe!\n");
    displayBoard();

    while (true) {
        playerMove(currentPlayer);
        displayBoard();

        if (checkWin()) {
            printf("Player %d wins!\n", currentPlayer);
            break;
        }
        if (checkDraw()) {
            printf("It's a draw!\n");
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Switch players
    }

    return 0;
}
