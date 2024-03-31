/*
Description : < describe what this program does briefly >
Author : Bukuhan, Abram Aki R. && Gemal, Ryan
Section : S17A
Last Modified : 1/29/2024
Acknowledgments : < list of references used in the making of this project > */

//#include "profilesFunc.h"
#include "interface.c"
#include "profunc.c"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void printMinesweeper(){
  char BOLDRED[10] = "\e[1;31m";
  char RED[10] = "\e[0;31m";
  char BOLDYELLOW[10] = "\e[1;33m";
  char BOLDBLUE[10] = "\e[1;34m";
  char WHITE[10] = "\e[0;37m";

  printf("                    %s     __,-~~/~    `---.\n", BOLDRED);
  printf("                   %s_/_,---(      ,    )\n", BOLDRED);
  printf("               %s__ /       %s <    /   %s)  \\___\n", BOLDRED, BOLDYELLOW, BOLDRED);
  printf("  %s- ------===;;;'%s====------------------===;;;===%s----- -  -\n", BOLDRED, BOLDYELLOW, BOLDRED);
  printf("                  %s\\/  %s~\"~\"~\"~\"~\"~\\~\"~)~%s\"/\n", BOLDRED, BOLDYELLOW, BOLDRED);
  printf("                  %s(_ (   %s\\  (     >  %s  \\)\n", BOLDRED, BOLDYELLOW, BOLDRED);
  printf("                   %s\\_( _ %s<         %s>_>'\n", BOLDRED, BOLDYELLOW, BOLDRED);
  printf("                      %s~ `-i' %s::>%s|--\"\n", BOLDRED, BOLDYELLOW, BOLDRED);
  printf("                          %sI%s;|.|.%s|\n", BOLDRED, BOLDYELLOW, BOLDRED);
  printf("                         %s<|%si::|i%s|`.\n", BOLDRED, BOLDYELLOW, BOLDRED);
  printf("                        %s(` %s^'\"`-%s' \")\n", BOLDRED, BOLDYELLOW, BOLDRED);

  // Minesweeper text
  printf("%s", BOLDYELLOW);
  printf("        _                                                   \n");
  printf("  /\\/\\ (_)_ __   ___  _____      _____  ___ _ __   ___ _ __ \n");
  printf(" /    \\| | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n");
  printf("/ /\\/\\ \\ | | | |  __/\\__ \\ V  V /  __/  __/ |_) |  __/ |   \n");
  printf("\\/    \\/_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   \n");
  printf("                                           |_|              \n");
}

/*
  nRandomizer() - Generates a random integer within a given range

  This function takes in two integer parameters, nLower and nUpper, and returns
  a random integer within the range [nLower, nUpper].

  @param: nLower - the lower bound of the range (inclusive)
  @param: nUpper - the upper bound of the range (inclusive)

  @return: An integer value within the range [nLower, nUpper]
 */
int nRandomizer(int nLower, int nUpper) {
  if (nLower > nUpper) {
    int nTemp = nLower;
    nLower = nUpper;
    nUpper = nTemp;
  }
  int nRand = (rand() % (nUpper - nLower + 1)) + nLower;
  return nRand;
}

void createMine(struct Cell board[][15], struct CoordTag mine) {
  board[mine.xCoord][mine.yCoord].state.isMine = 1;
}

struct CoordTag generateRandomMine(int boardRows, int boardCols) {
  struct CoordTag randomMine;

  randomMine.xCoord = nRandomizer(0, boardRows - 1);
  randomMine.yCoord = nRandomizer(0, boardCols - 1);

  return randomMine;
}

struct CoordTag generateMineExcept(int boardRows, int boardCols,
                                   struct CoordTag exceptCell) {
  struct CoordTag randomMine;

  randomMine.xCoord = nRandomizer(0, boardRows - 1);
  randomMine.yCoord = nRandomizer(0, boardCols - 1);

  if (randomMine.xCoord == exceptCell.xCoord &&
      randomMine.yCoord == exceptCell.yCoord) {
    randomMine.xCoord = nRandomizer(0, boardRows - 1);
    randomMine.yCoord = nRandomizer(0, boardCols - 1);
  }

  return randomMine;
}

int isPosMatch(struct CoordTag cellA, struct CoordTag cellB) {
  return cellA.xCoord == cellB.xCoord && cellA.yCoord == cellB.yCoord;
}

void initializeMines(struct Cell board[][15], int mineCount, int boardRows,
                     int boardCols, struct CoordTag userCell) {
  int i, j, k;
  struct CoordTag mines[35];
  struct CoordTag tempMine;
  struct CoordTag adjacentCells[10] = {
      {userCell.xCoord - 1, userCell.yCoord},
      {userCell.xCoord + 1, userCell.yCoord},
      {userCell.xCoord, userCell.yCoord - 1},
      {userCell.xCoord, userCell.yCoord + 1},
      {userCell.xCoord - 1, userCell.yCoord - 1},
      {userCell.xCoord - 1, userCell.yCoord + 1},
      {userCell.xCoord + 1, userCell.yCoord - 1},
      {userCell.xCoord + 1, userCell.yCoord + 1}};

  int hasConflict;

  for (i = 0; i < mineCount; i++) {
    // mines[i] = generateRandomMine(boardRows, boardCols);
    tempMine = generateRandomMine(boardRows, boardCols);
    hasConflict = 0;

    // Checks previous mines
    for (j = 0; j < i; j++) {
      if (mines[j].xCoord == tempMine.xCoord &&
          mines[j].yCoord == tempMine.yCoord) {
        hasConflict = 1;
      }
    }

    while (hasConflict) {
      tempMine =
          generateRandomMine(boardRows, boardCols); // Generate a new mine
      hasConflict = 0;                              // Reset the flag

      // Check for conflicts with previous mines
      for (j = 0; j < i; j++) {
        for (k = 0; k < 8; k++) {
          while (isPosMatch(mines[j], adjacentCells[k])) {
            mines[j] =
                generateMineExcept(boardRows, boardCols, adjacentCells[k]);
            // hasConflict = 1;
          }
        }
        while (isPosMatch(mines[j], userCell)) {
          mines[j] = generateMineExcept(boardRows, boardCols, userCell);
          // hasConflict = 1;
        }
        if (mines[j].xCoord == tempMine.xCoord &&
            mines[j].yCoord == tempMine.yCoord) {
          hasConflict = 1;
        }
      }
    }
    mines[i] = tempMine;
  }

  for (i = 0; i < mineCount; i++) {
    for (k = 0; k < 8; k++) {
      while (isPosMatch(mines[i], adjacentCells[k])) {
        mines[i] = generateMineExcept(boardRows, boardCols, adjacentCells[k]);
      }
    }
    while (isPosMatch(mines[i], userCell)) {
      mines[i] = generateMineExcept(boardRows, boardCols, userCell);
      // hasConflict = 1;
    }
    createMine(board, mines[i]);
  }
}

int checkAdjacentMines(struct Cell board[][15], int boardRows, int boardCols,
                       struct CoordTag targetCell) {
  int count = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      // Skip the target cell itself
      if (i != 0 || j != 0) {
        int row = targetCell.xCoord + i;
        int col = targetCell.yCoord + j;

        // Check if the cell is within the board
        if (row >= 0 && row < boardRows && col >= 0 && col < boardCols) {
          // If the cell contains a mine (-1), increment the count
          if (board[row][col].state.isMine == 1) {
            count++;
          }
        }
      }
    }
  }
  board[targetCell.xCoord][targetCell.yCoord].adjacentMines = count;
  return count;
}

int isMine(struct Cell board[][15], struct CoordTag targetCell) {
  return board[targetCell.xCoord][targetCell.yCoord].state.isMine;
}

int inspect(struct Cell board[][15], int boardRows, int boardCols,
            struct CoordTag targetCell) {
  int adjacentMines =
      checkAdjacentMines(board, boardRows, boardCols, targetCell);

  board[targetCell.xCoord][targetCell.yCoord].state.isRevealed = 1;

  if (board[targetCell.xCoord][targetCell.yCoord].state.isMine == 1) {
    return 1; // Game over
  }

  else {
    if (board[targetCell.xCoord][targetCell.yCoord].state.isFlagged == 1) {
      board[targetCell.xCoord][targetCell.yCoord].state.isFlagged = 0;
    }
    if (adjacentMines == 0) {
      struct CoordTag adjacentCells[] = {
          {targetCell.xCoord - 1, targetCell.yCoord},
          {targetCell.xCoord + 1, targetCell.yCoord},
          {targetCell.xCoord, targetCell.yCoord - 1},
          {targetCell.xCoord, targetCell.yCoord + 1}};

      for (int i = 0; i < 4; i++) {
        if (adjacentCells[i].xCoord >= 0 &&
            adjacentCells[i].xCoord < boardRows &&
            adjacentCells[i].yCoord >= 0 &&
            adjacentCells[i].yCoord < boardCols &&
            board[adjacentCells[i].xCoord][adjacentCells[i].yCoord]
                    .state.isRevealed == 0) {
          inspect(board, boardRows, boardCols, adjacentCells[i]);
        }
      }
    }
    return 0;
  }
}

void flag(struct Cell board[][15], struct CoordTag targetCell) {
  if (board[targetCell.xCoord][targetCell.yCoord].state.isRevealed == 0) {
    if (board[targetCell.xCoord][targetCell.yCoord].state.isFlagged == 0) {
      board[targetCell.xCoord][targetCell.yCoord].state.isFlagged = 1;
    } else {
      board[targetCell.xCoord][targetCell.yCoord].state.isFlagged = 0;
    }
  }
}

/*
  Function Comments and Description
*/
void printBoard(struct Cell board[][15], int boardRows, int boardColumns,
                int fog) {
  int i, j;
  for (i = 0; i < boardRows; i++) {
    if (i == 0) {
      iSetColor(I_COLOR_BLUE);
      printf("  ");
      for (j = 0; j < boardColumns; j++) {
        if (j < 10) {
          printf(" %d ", j);
        } else {
          printf("%d ", j);
        }
      }
      printf("\n");
    }

    iSetColor(I_COLOR_WHITE);
    for (j = 0; j < boardColumns; j++) {
      if (j == 0) {
        iSetColor(I_COLOR_BLUE);
        printf("%d  ", i);
      }
      if (board[i][j].state.isMine == 1 && fog == 0) {
        if(board[i][j].state.isFlagged){
          iSetColor(I_COLOR_PURPLE);
          printf("!  ");
        }
        else{
          iSetColor(I_COLOR_RED);
          printf("X  ");
        }
      } else if (board[i][j].state.isFlagged == 1) {
        iSetColor(I_COLOR_YELLOW);
        printf("?  ");
      } else if (board[i][j].state.isRevealed == 0) {
        iSetColor(I_COLOR_WHITE);
        printf(".  ");
      } else if (board[i][j].state.isRevealed == 1) {
        iSetColor(I_COLOR_GREEN);
        printf("%d  ", board[i][j].adjacentMines);
      }
      iSetColor(I_COLOR_WHITE);
    }
    printf("\n");
  }
}

int readCustomLevel(char fileName[], struct Cell board[][15], int *boardRows,
                    int *boardCols, int *mineCount) {
  int i, j;
  int readMines = 0;
  
  char filePath[50] = "levels/";
  strcat(filePath, fileName);
  strcat(filePath, ".txt");
  FILE *fp = fopen(filePath, "r");
  char currentLine[20] = "";
  if (fp == NULL) {
    printf("Error: could not open file %s.\n", fileName);
    return 1;
  }
  fscanf(fp, "%d %d", boardRows, boardCols);
  printf("Rows: %d, Cols: %d\n", *boardRows, *boardCols);
  for (i = 0; i < *boardRows; i++) {
    fscanf(fp, "%s", currentLine);
    // printf("%c\n", currentLine);
    for (j = 0; j < *boardCols; j++) {
      if (currentLine[j] == 'X') {
        board[i][j].state.isMine = 1;
        readMines++;
      }
    }
  }
  *mineCount = readMines;
  fclose(fp); // Close the file after reading
  return 0;   // Return 0 to indicate success
}

int writeCustomLevel(char fileName[]) {
  int i, j;
  int boardRows, boardCols;
  struct Cell board[15][15];

  int cursorX = 3, cursorY = 1;
  struct CoordTag userCell = {0, 0};
  char userChar;
  int userChoosing;
  int levelIsValid = 0;
  int userMinesPlaced = 0;

  int makingLevel = 1;

  system("mkdir levels");

  char filePath[50] = "levels/";
  strcat(filePath, fileName);
  strcat(filePath, ".txt");
  FILE *fp = fopen(filePath, "r");
  if (fp != NULL) {
    printf("Error: file %s already exists.\n", fileName);
    return 1;
  } else {
    fp = fopen(filePath, "w");

    do {
      printf("Enter amount of rows: ");
      scanf("%d", &boardRows);

      if (boardRows > 10 || boardRows < 5) {
        printf("Error: number of rows must be between 5 and 10.\n");
      }
    } while (boardRows > 10 || boardRows < 5);

    do {
      printf("Enter amount of columns: ");
      scanf("%d", &boardCols);

      if (boardCols < 5 || boardCols > 15) {
        printf("Error: number of columns must be between 5 and 15..\n");
      }
    } while (boardCols < 5 || boardCols > 15);
    fprintf(fp, "%d %d\n", boardRows, boardCols);
  }

  for (i = 0; i < boardRows; i++) {
    for (j = 0; j < boardCols; j++) {
      board[i][j].adjacentMines = 0;
      board[i][j].state.isRevealed = 0;
      board[i][j].state.isFlagged = 0;
      board[i][j].state.isMine = 0;
    }
  }

  while (!levelIsValid) {
    while (makingLevel) {
      userChoosing = 1;
      //iClear(0, 0, 50, 50);
      system("cls");
      printBoard(board, boardRows, boardCols, 0);
      printf("Press an arrow key to move.\n");
      printf("Press M to toggle a mine in the board.\n");
      printf("Press S to finish and save.\n");

      iMoveCursor(cursorX, cursorY);
      if (userChoosing) {
        userChar = getch();
        // printf("User char: %d\n", userChar);
        if (userChar == -32) {
          // printf("Up, down, left, or right?");
          userChar = getch();
          switch (userChar) {
          case 75: // Left arrow
            if (cursorX - 2 >= 2 && userCell.yCoord - 1 >= 0) {
              cursorX -= 3;
              userCell.yCoord--;
            }
            break;
          case 77: // Right arrow
            if (cursorX + 2 < boardCols * 3 &&
                userCell.yCoord + 1 < boardCols) {
              cursorX += 3;
              userCell.yCoord++;
            }
            break;
          case 72: // Up arrow
            if (cursorY - 1 >= 1 && userCell.xCoord - 1 >= 0) {
              cursorY--;
              userCell.xCoord--;
            }
            break;
          case 80: // Down arrow
            if (cursorY + 1 <= boardRows && userCell.xCoord + 1 < boardRows) {
              cursorY++;
              userCell.xCoord++;
            }
            break;
          default:
            break;
          }
          iMoveCursor(cursorX, cursorY);
        } else if (userChar == 'M' || userChar == 'm') {
          if (board[userCell.xCoord][userCell.yCoord].state.isMine == 1) {
            board[userCell.xCoord][userCell.yCoord].state.isMine = 0;
            userMinesPlaced--;
          } else {
            board[userCell.xCoord][userCell.yCoord].state.isMine = 1;
            userMinesPlaced++;
          }
          // userCell.xCoord = 0;
          // userCell.yCoord = 0;
          userChoosing = 0;
          userChar = ' ';
        } else if (userChar == 'S' || userChar == 's') {
          userChoosing = 0;
          if (userMinesPlaced == 0 ||
              userMinesPlaced == boardRows * boardCols) {
            while (userChar != 13) { // Enter key
              printf("Error: the level must contain at least one mine and at "
                     "most %d mines.\n",
                     boardRows * boardCols - 1);
              printf("Press enter to continue..");
              userChar = getch();
              system("cls");
            }
            makingLevel = 1;
          } else {
            makingLevel = 0;
            levelIsValid = 1;
          }
        }
        
      }
    }
  }

  for (i = 0; i < boardRows; i++) {
    for (j = 0; j < boardCols; j++) {
      if (board[i][j].state.isMine == 1) {
        fprintf(fp, "X");
      } else {
        fprintf(fp, ".");
      }
    }
    fprintf(fp, "\n");
  }

  fclose(fp); // Close the file after writing
  system("cls");
  printf("Text file %s successfully created!\n", fileName);
  printf("Press any key to continue...");
  while(!kbhit()){
    //
  }
  system("cls");
  return 0;   // Return 0 to indicate success
}

/*
  Function Comments and Description
*/
void startGame(Profile *profile) {
  int gameType = 1;
  int difficulty;

  int boardRows;
  int boardCols;
  int mineCount;
  int flagCount;
  int revealCount;
  int turnCount = 0;
  struct Cell board[15][15];

  int userChoosing = 0;
  char userChar;
  char customFileName[55];
  int cursorX = 3, cursorY = 1;
  int menuCursorX = 0, menuCursorY = 20;

  int i, j;

  char inspectOrFlag;
  struct CoordTag userCell = {0, 0};

  int gameStatus = 0;
  int gameResult = 0;
  int hasChosenLevel = 0;
  int hasChosenGameType = 0;

  int totalsec = 0;
  int hour = 0; int min = 0; int sec = 0;
  time_t start = time(NULL);

  for (i = 0; i < 15; i++) {
    for (j = 0; j < 15; j++) {
      board[i][j].adjacentMines = 0;
      board[i][j].state.isRevealed = 0;
      board[i][j].state.isFlagged = 0;
      board[i][j].state.isMine = 0;
    }
  }

  while(gameType != 3){
    while (!hasChosenGameType){
      hasChosenLevel = 0;
      while(!hasChosenLevel){
        menuCursorX = 20, menuCursorY = 21;
        userChoosing = 1;
        iClear(0, 20, 50, 7);
        iSetColor(I_COLOR_CYAN);
        printf("                 Choose a game type:\n");
        iSetColor(I_COLOR_YELLOW);
        printf("                    1: Classic game\n");
        printf("                    2: Custom game\n");
        printf("                    3: Back to main menu\n");
        iMoveCursor(menuCursorX, menuCursorY);
        gameType = 1;
        while(userChoosing){
          iMoveCursor(menuCursorX, menuCursorY);
          userChar = getch();
          // printf("User char: %d\n", userChar);
          if (userChar == -32) {
            // printf("Up, down, left, or right?");
            userChar = getch();
            switch (userChar) {
            case 72: // Up arrow
              if (gameType-1 > 0 && gameType-1 < 4) {
                gameType--;
                menuCursorY--;
                iMoveCursor(menuCursorX, menuCursorY);
              }
              break;
            case 80: // Down arrow
              if (gameType+1 > 0 && gameType+1 < 4) {
                gameType++;
                menuCursorY++;
                iMoveCursor(menuCursorX, menuCursorY);
              }
              break;
            default:
              break;
            }
            
          } else if(userChar == 13){
            userChoosing = 0;
            menuCursorX--;
            if(gameType == 3){ menuCursorY-=2; }
            hasChosenGameType = 1;
          }
        }

        if (gameType == 1) {
          menuCursorX = 20, menuCursorY = 21;
          difficulty = 1;
          userChoosing = 1;
         
          iMoveCursor(20, 21);
          iClear(0, 20, 50, 7);
          iSetColor(I_COLOR_CYAN);
          printf("                  Choose a difficulty:\n");
          iSetColor(I_COLOR_YELLOW);
          printf("                    1: Easy (8 x 8 level with 10 mines)\n");
          printf("                    2: Difficult (10 x 15 level with 35 mines)\n");
          printf("                    3: Back to game types");
          while(userChoosing){
            iMoveCursor(menuCursorX, menuCursorY);
            userChar = getch();
            // printf("User char: %d\n", userChar);
            if (userChar == -32) {
              // printf("Up, down, left, or right?");
              userChar = getch();
              switch (userChar) {
              case 72: // Up arrow
                if (difficulty-1 > 0 && difficulty-1 < 4) {
                  difficulty--;
                  menuCursorY--;
                  iMoveCursor(menuCursorX, menuCursorY);
                }
                break;
              case 80: // Down arrow
                if (difficulty+1 > 0 && difficulty+1 < 4) {
                  difficulty++;
                  menuCursorY++;
                  iMoveCursor(menuCursorX, menuCursorY);
                }
                break;
              default:
                break;
              }
            
          } else if(userChar == 13){
            userChoosing = 0;
            menuCursorX--;
            if(difficulty == 3){ menuCursorY-=2; }
            hasChosenLevel = 1;
          }
        }

          if (difficulty == 1) {
            boardRows = 8;
            boardCols = 8;
            mineCount = 10;
            hasChosenLevel = 1;
            hasChosenGameType = 1;
            gameStatus++;
          }

          else if (difficulty == 2) {
            boardRows = 10;
            boardCols = 15;
            mineCount = 35; 
            hasChosenLevel = 1;
            hasChosenGameType = 1;
            gameStatus++;
          }
          else if(difficulty == 3){
            hasChosenGameType = 0;
            hasChosenLevel = 0;
            gameType = 3;
            iClear(0, 20, 75, 7);
            //iMoveCursor(0, 19);
          }
        }

        else if (gameType == 2) {
            iClear(0, 20, 50, 7);
            iMoveCursor(10, 20);
            iSetColor(I_COLOR_CYAN);
            printf("Enter B to go back to game types.\n");
            printf("\n");
            iSetColor(I_COLOR_YELLOW);
            printf("Enter a file name (without .txt): ");
            scanf("%s", customFileName);
            if(strcmp(customFileName, "B") == 0){
              hasChosenGameType = 0;
            }
            else if(readCustomLevel(customFileName, board, &boardRows, &boardCols, &mineCount) == 1){
              printf("Press any key to continue...\n");
              while(!kbhit());
            }
            else{
              hasChosenLevel = 1;
              gameStatus++;
            }
        }

        else if (gameType == 3) {
          gameStatus = 0;
          hasChosenGameType = 1;
          hasChosenLevel = 1;
        }
      }

      while (gameStatus) {
        // cursorX = 2;
        // cursorY = 1;
        userChoosing = 1;
        flagCount = 0;
        revealCount = 0;

        //iClear(0, 0, 50, 50);
        system("cls");
        printBoard(board, boardRows, boardCols, 1);
        printf("Press an arrow key to move.\n");
        printf("Press I to inspect, F to flag, Q to quit.\n");
        
        totalsec = difftime(time(NULL), start);
        hour = totalsec / 3600;
        min = (totalsec % 3600) / 60;
        sec = totalsec % 60;
        printf("Time elapsed: %02d:%02d:%02d\n", hour, min, sec);
        
        iMoveCursor(cursorX, cursorY);
        if(kbhit() && userChoosing) {
          userChar = getch();
          // printf("User char: %d\n", userChar);
          if (userChar == -32) {
            // printf("Up, down, left, or right?");
            userChar = getch();
            switch (userChar) {
            case 75: // Left arrow
              if (cursorX - 2 >= 2 && userCell.yCoord - 1 >= 0) {
                cursorX -= 3;
                userCell.yCoord--;
              }
              break;
            case 77: // Right arrow
              if (cursorX + 2 < boardCols * 3 && userCell.yCoord + 1 < boardCols) {
                cursorX += 3;
                userCell.yCoord++;
              }
              break;
            case 72: // Up arrow
              if (cursorY - 1 >= 1 && userCell.xCoord - 1 >= 0) {
                cursorY--;
                userCell.xCoord--;
              }
              break;
            case 80: // Down arrow
              if (cursorY + 1 <= boardRows && userCell.xCoord + 1 < boardRows) {
                cursorY++;
                userCell.xCoord++;
              }
              break;
            default:
              break;
            }
            iMoveCursor(cursorX, cursorY);
          } else if (userChar == 'F' || userChar == 'f' || userChar == 'I' ||
                    userChar == 'i') {
            userChoosing = 0;
            inspectOrFlag = userChar;
            if (turnCount == 0 && gameType == 1) {
              initializeMines(board, mineCount, boardRows, boardCols, userCell);
            }
            if (inspectOrFlag == 'I' || inspectOrFlag == 'i') {
              if (inspect(board, boardRows, boardCols, userCell) == 1) {
                gameStatus--;
              }
              turnCount++;
            }
            if (inspectOrFlag == 'F' || inspectOrFlag == 'f') {
              flag(board, userCell);
              turnCount++;
            }
            // userCell.xCoord = 0;
            // userCell.yCoord = 0;
            userChar = ' ';
          } else if (userChar == 'Q' || userChar == 'q') {
            userChoosing = 0;
            gameStatus--; // Quit
            gameResult = 2;
          }
        }

        for (i = 0; i < boardRows; i++) {
          for (j = 0; j < boardCols; j++) {
            if (board[i][j].state.isFlagged == 1 && board[i][j].state.isMine == 1) {
              flagCount++;
            } else if (board[i][j].state.isRevealed == 1) {
              revealCount++;
            }
          }
        }

        if (flagCount + revealCount == boardRows * boardCols) {
          if (flagCount == mineCount) {
            gameResult = 1; // Win
          }
          gameStatus--;
        }
        Sleep(300);
      }

      if(gameType != 3){
        //iClear(0, 0, 50, 50);
        system("cls");
        printf("Game over!\n");

        int leader = 0;

        if ((gameResult == 1 && profile-> totalSec > totalsec) || (gameResult == 1 && profile->totalSec == 0)){
          profile->totalSec = totalsec;
          leader = 1;
        }

        string check;
        string copy;

        if (profile->gameP % 3 == 1){
          sprintf(check, "%s's Board 1:", profile->name);
          sprintf(copy, "%s's Board 2:", profile->name);
        }
        else if (profile->gameP % 3 == 2){
          sprintf(check, "%s's Board 2:", profile->name);
          sprintf(copy, "%s's Board 3:", profile->name);
        }
        else if (profile->gameP % 3 == 0){
          sprintf(check, "%s's Board 3:", profile->name);
          sprintf(copy, "%s End", profile->name);

        }

        if(gameResult == 0){
          printBoard(board, boardRows, boardCols, 0);
          printf("You lose!\n");
          manipulate(check, copy, board, 'L', boardRows, boardCols, profile);
        }
        else if(gameResult == 1){
          printBoard(board, boardRows, boardCols, 0);
          printf("You win!\n");
          manipulate(check, copy, board, 'W', boardRows, boardCols, profile);
        }
        else if(gameResult == 2){
          printBoard(board, boardRows, boardCols, 1);
          printf("You quit the game!\n");
          manipulate(check, copy, board, 'Q', boardRows, boardCols, profile);
        }

        profileChanger(profile, gameType, difficulty, gameResult, leader);
        printf("Press any key to continue...");
        while(!kbhit()){
          //
        }
        gameType = 3;
      }
    }
  }
}

/*
  Function Comments and Description
*/
void mainMenu(Profile *profile, int *programRunning) {
  
  
  char fileName[55];
  int userInput;
  srand(time(0));
  Profile prof = *profile;
  int stayMenu = 1;


  int userChoosing = 1;
  char userChar;

  // while(userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4
  // && userInput != 5){
  while(stayMenu && *programRunning){
    int cursorX = 18;
    int cursorY = 21;
    system("cls");
    blank();
    printMinesweeper();
    printf("              Welcome to Minesweeper, %s!\n", profile -> name);
    
    iSetColor(I_COLOR_WHITE);
    blank();
    
    iSetColor(I_COLOR_CYAN);
    printf("                  Main Menu\n");
    iSetColor(I_COLOR_YELLOW);
    printf("                  1: Start Game\n");
    printf("                  2: Create a Level\n");
    printf("                  3: Change Profile\n");
    printf("                  4: View Statistics\n");
    printf("                  5: Leaderboards\n");
    printf("                  6: Quit\n");
    blank();
    iSetColor(I_COLOR_WHITE);

    iMoveCursor(18, 21);
    userInput = 1;
    userChoosing = 1;
    userChar = ' ';
    while(userChoosing){
      iMoveCursor(cursorX, cursorY);
      userChar = getch();
      // printf("User char: %d\n", userChar);
      if (userChar == -32) {
        // printf("Up, down, left, or right?");
        userChar = getch();
        switch (userChar) {
        case 72: // Up arrow
          if (userInput-1 > 0 && userInput-1 < 7) {
            userInput--;
            cursorY--;
            iMoveCursor(cursorX, cursorY);
          }
          break;
        case 80: // Down arrow
          if (userInput+1 > 0 && userInput+1 < 7) {
            userInput++;
            cursorY++;
            iMoveCursor(cursorX, cursorY);
          }
          break;
        default:
          break;
        }
        
      } else if(userChar == 13){
        userChoosing = 0;
        cursorX--;
        iMoveCursor(cursorX, cursorY);
      }
    }

    switch (userInput) {
    case 1:
      startGame(&prof);
      break;
    case 2:
      printf("Enter the file name to save the level (without .txt extension): ");
      scanf("%s", fileName);

      writeCustomLevel(fileName);
      break;
    case 3:
    iClear(0, 20, 75, 8);
      selProfile(programRunning);
      break;
    case 4:
      iClear(0, 20, 75, 8);
      viewStat(prof.name);
      iSetColor(I_COLOR_YELLOW);
      blank();
      printf("Press any key to continue...");
      while(!kbhit()){ /* do nothing */ }
      break;
    case 5:
      iClear(0, 20, 75, 7);
      leaderBoards();
      iSetColor(I_COLOR_YELLOW);
      printf("Press any key to continue...");
      while(!kbhit()){ /* do nothing */ }
      break;
    case 6:
      stayMenu = 0;
      *programRunning = 0;
      break;
    }
  }
  //}
}

int main() {
  int programRunning = 1;
  profile_mainMenu(&programRunning);

  return 0;
}

/*
This is to certify that this project is my own work , based on my personal
efforts in studying and applying the concepts learned . I have constructed the
functions and their respective algorithms and corresponding code by myself . The
program was run , tested , and debugged by my own efforts . I further certify
that I have not copied in part or whole or otherwise plagiarized the work of
other students and / or persons . Bukuhan, Abram Aki R. && Gemal, Ryan, DLSU ID
# 12313467 && 12338737
*/