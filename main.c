    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define ROWS 5
    #define COLS 7

    typedef struct {
        bool isUsed;
        bool p1Owns;
        bool isWinning;
    } Cell;

    Cell gameBoard[ROWS][COLS];

    bool isP1Turn = true;

    int endType = 0;

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    int draw() {
        clearScreen();

        printf("╔═╦═╦═╦═╦═╦═╦═╗\n");
        for (int row = 0; row < ROWS; row ++) {
            // printf("%d: ", row);
            for (int col = 0; col < COLS; col ++) {
                if (gameBoard[row][col].isUsed) {                
                    if (gameBoard[row][col].p1Owns) {
                        char tmp[17] = "║\033[34";

                        if (gameBoard[row][col].isWinning) {
                            strcat(tmp, ";42");
                        }

                        strcat(tmp, "m●\033[0m");

                        printf("%s" ,tmp);
                    }
                    else {
                        char tmp[17] = "║\033[33";

                        if (gameBoard[row][col].isWinning) {
                            strcat(tmp, ";42");
                        }

                        strcat(tmp, "m○\033[0m");

                        printf("%s" ,tmp);
                    }
                }
                else {
                    printf("║ ");
                }

            }
            printf("║\n");
        }
        printf("╚═╩═╩═╩═╩═╩═╩═╝\n");

        return 0;
    }

    int clear() {
        isP1Turn = true;

        for (int row = 0; row < ROWS; row ++) {
            for (int col = 0; col < COLS; col ++) {
                gameBoard[row][col].isUsed = false;
            }
        }

        draw();

        return 0;
    }

    int drop(int col) {
        if (!gameBoard[0][col].isUsed) {
            for (int row = ROWS - 1; row >= 0; row --) {
                if (!gameBoard[row][col].isUsed) {
                    gameBoard[row][col].isUsed = true;
                    gameBoard[row][col].p1Owns = isP1Turn;
                    break;
                }
            }
            draw();
            isP1Turn = !isP1Turn;
        }
        else {
            draw();
            printf("\033[31mInvalid Move! All cells in the column are full!\033[0m\n");
        }

        return 0;
    }

    int testWin(bool player) {
        bool full = true;
        for (int c = 0; c < COLS; c++) {
            if (!gameBoard[0][c].isUsed) {
                full = false;
                break;
            }
        }
        if (full) {
            return 2;
        };

        for (int row = 0; row < ROWS; row ++) {
            for (int col = 0; col < COLS - 3; col ++) {
                if (gameBoard[row][col].isUsed && gameBoard[row][col + 1].isUsed && gameBoard[row][col + 2].isUsed && gameBoard[row][col + 3].isUsed) {
                    if (gameBoard[row][col].p1Owns == player && gameBoard[row][col + 1].p1Owns == player && gameBoard[row][col + 2].p1Owns == player && gameBoard[row][col + 3].p1Owns == player) {
                        gameBoard[row][col].isWinning = true;
                        gameBoard[row][col + 1].isWinning = true;
                        gameBoard[row][col + 2].isWinning = true;
                        gameBoard[row][col + 3].isWinning = true;
        
                        return 1;
                    }
                }
            }
        }

        for (int row = 0; row < ROWS - 3; row ++) {
            for (int col = 0; col < COLS; col ++) {
                if (gameBoard[row][col].isUsed && gameBoard[row + 1][col].isUsed && gameBoard[row + 2][col].isUsed && gameBoard[row + 3][col].isUsed) {
                    if (gameBoard[row][col].p1Owns == player && gameBoard[row + 1][col].p1Owns == player && gameBoard[row + 2][col].p1Owns == player && gameBoard[row + 3][col].p1Owns == player) {
                        gameBoard[row][col].isWinning = true;
                        gameBoard[row + 1][col].isWinning = true;
                        gameBoard[row + 2][col].isWinning = true;
                        gameBoard[row + 3][col].isWinning = true;

                        return 1;
                    }
                }
            }
        }

        for (int row = 3; row < ROWS; row ++) {
            for (int col = 0; col < COLS - 3; col ++) {
                if (gameBoard[row][col].isUsed && gameBoard[row - 1][col + 1].isUsed && gameBoard[row - 2][col + 2].isUsed && gameBoard[row - 3][col + 3].isUsed) {
                    if (gameBoard[row][col].p1Owns == player && gameBoard[row - 1][col + 1].p1Owns == player && gameBoard[row - 2][col + 2].p1Owns == player && gameBoard[row - 3][col + 3].p1Owns == player) {
                        gameBoard[row][col].isWinning = true;
                        gameBoard[row - 1][col + 1].isWinning = true;
                        gameBoard[row - 2][col + 2].isWinning = true;
                        gameBoard[row - 3][col + 3].isWinning = true;

                        return 1;
                    }
                }
            }
        }

        for (int row = 0; row < ROWS - 3; row ++) {
            for (int col = 0; col < COLS - 3; col ++) {
                if (gameBoard[row][col].isUsed && gameBoard[row + 1][col + 1].isUsed && gameBoard[row + 2][col + 2].isUsed && gameBoard[row + 3][col + 3].isUsed) {
                    if (gameBoard[row][col].p1Owns == player && gameBoard[row + 1][col + 1].p1Owns == player && gameBoard[row + 2][col + 2].p1Owns == player && gameBoard[row + 3][col + 3].p1Owns == player) {
                        gameBoard[row][col].isWinning = true;
                        gameBoard[row + 1][col + 1].isWinning = true;
                        gameBoard[row + 2][col + 2].isWinning = true;
                        gameBoard[row + 3][col + 3].isWinning = true;

                        return 1;
                    }
                }
            }
        }

        return 0;
    }

    int main() { 
        clear();

        while (1)
        {
            printf(isP1Turn ? "\033[34mPlayer 1's\033[0m turn!\n": "\033[33mPlayer 2's\033[0m turn!\n");
            printf("Drop positions (1-7): ");
            int scanner;
            scanf("%d", &scanner);

            if (scanner < 1 || scanner > 7) {
                draw();
                printf("\033[31mInvalid Move! Outside of board range!\033[0m\n");
            }
            else {
                drop(scanner - 1);
            }

            endType = testWin(!isP1Turn);

            if (endType != 0) {
                break;
            }
        }
        draw();

        if (endType != 2) {
            printf(!isP1Turn ? "\033[34mPlayer 1\033[0m WON!\n": "\033[33mPlayer 2\033[0m WON!\n");
        }
        else {
            printf("Draw!");
        }

        return 0;
    }
