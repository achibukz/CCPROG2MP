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
void arrProf(string names[], int *numNames);
void selSort(string arr[], int n);
int profFinder(string arr[], string name, int n);
Profile createProfile();
void selProfile();
void viewStat(string name);
void cursorStart(FILE *file, string target);
void profileChanger(Profile *profile, int type, int diff, int win, int leader);
void delProfile1(string name);
void delProfile2(string name);
void mainMenu(Profile *profile);
void profile_mainMenu();
void printBoardTex(struct Cell board[][15], int boardRows, int boardColumns,
                int fog, FILE *file);
void copy(string target);
void paste();
void rewriteFile(FILE *sourceFile, FILE *destFile, long endPos);
void sortProf(Profile Prof[], int numPlay);
void leaderBoards();
void manipulate(string target, string cope, struct Cell board[][15], char state, int boardRows, int boardColumn, Profile *profile, int n);


#endif