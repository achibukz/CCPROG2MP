#ifndef _STRUCTS_H
#define _STRUCTS_H

typedef char string[21];

typedef struct Profile {

  string name;
  int wonGame[3];
  int lostGame[3];
  int gameP;
  int totalSec;

} Profile;

struct CoordTag {
  int xCoord;
  int yCoord;
};

struct CellState {
  int isRevealed;
  int isMine;
  int isFlagged;
};

struct Cell {
  struct CoordTag position;
  struct CellState state;
  int adjacentMines;
};

void blank();
void printProfile(Profile profile);
void printBoards(Profile profile);
void printBoardTex(struct Cell board[][15], int boardRows, int boardColumns,
                int fog, FILE *file);

void arrProf(string names[], int *numNames);
void selSort(string arr[], int n);
void sortProf(Profile Prof[], int numPlay);

void cursorStart(FILE *file, string target);
int profFinder(string arr[], string name, int n);
void rewriteFile(FILE *sourceFile, FILE *destFile, long endPos);

Profile createProfile();
void selProfile(int *programRunning);
void viewStat(string name);
void delProfile1(string name);
void delProfile2(string name);
void leaderBoards();
void mainMenu(Profile *profile, int *programRunning);
void printMinesweeper();

void profileChanger(Profile *profile, int type, int diff, int win, int leader);
void profile_mainMenu(int *programRunning);

void copy(string target);
void paste();
void manipulate(string target, string cope, struct Cell board[][15], char state, int boardRows, int boardColumn, Profile *profile);


#endif