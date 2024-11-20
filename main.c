// standard C libraries
#include <stdio.h>
/*
Math.h here is imported for the floor function which we will use to
calculate the row and col that the user will play
*/
#include <math.h>
/* To make use of bool values like true and false in c */
#include<stdbool.h>

char board[3][3]; // Tic-Tac-Toe boardScore
typedef struct{
    /* data */
    char key;
    int score;
} Score;


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

// Check win for minimax algorithm
char checkWin_Minimax(char board[3][3]) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0]; // Row match
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i]; // Column match
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') return ' '; // Empty space exists, so not a draw yet
        }
    }
    return 't'; // No winner
}

double minimax(char boardmod[3][3], bool isMaximizing){
    Score scores[] = {
        {'X', -1},
        {'O', 1},
        {'t', 0}};
    char sc = checkWin_Minimax(boardmod);
    for (int i = 0; i < 3; i++){
        if (scores[i].key == sc) return scores[i].score;
    }
    if (isMaximizing){
        double bestScore = -INFINITY;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (boardmod[i][j] == ' '){
                    boardmod[i][j] = 'O';
                    bestScore = fmax(bestScore, minimax(boardmod, false));
                    boardmod[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }else{
        double bestScore = INFINITY;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                if (boardmod[i][j] == ' '){
                    boardmod[i][j] = 'X';
                    bestScore = fmin(bestScore, minimax(boardmod, true));
                    boardmod[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
}

// Use Minimax algorithm to calculate the best Move for O
void bestMove(char board[3][3]){
    int r,c;
    char boardModel[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            boardModel[i][j] = board[i][j];
        }
    }
    double bestScore = -INFINITY;
    double score;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (boardModel[i][j] == ' '){
                boardModel[i][j] = 'O';
                score = minimax(boardModel, false);
                boardModel[i][j] = ' ';
                if (score > bestScore){
                    bestScore = score;
                    r = i;
                    c = j;
                }
            }
        }
    }
    board[r][c] = 'O';
}



int main() {
    char option;
    printf("Press A if you want to play multiplayer\nPress B if you want to play against computer\n");
    scanf("%c", &option);
    if (option == 'A' || option == 'a'){
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
    }else if (option == 'B' || option == 'b'){
        initializeBoard();

        printf("Welcome to Tic-Tac-Toe!\n");
        displayBoard();
        while (true){
            playerMove(1);
            displayBoard();
            if (checkWin()) {
                printf("You win!\n");
                break;
            }
            if (checkDraw()) {
                printf("It's a draw!\n");
                break;
            }
            printf("\n AI is calculating O's move... \n");
            // Play the best move by O
            bestMove(board);
            displayBoard();
            if (checkWin()) {
                printf("AI win!\n");
                break;
            }
            if (checkDraw()) {
                printf("It's a draw!\n");
                break;
            }

        }
    }
}
