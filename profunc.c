#include "profunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

/*
  blank() - Creates a Horizontal Dash for Display.
 */
void blank() {
  iSetColor(I_COLOR_PURPLE);
  printf("---------------------------------------------------\n");
}

/*
  printProfile()

  This function displayes the Details of the Player.

  @param: profile - A struct Profile of the Player
 */
void printProfile(Profile profile) {
  iSetColor(I_COLOR_CYAN);
  printf("Profile Name: %s\n", profile.name);
  iSetColor(I_COLOR_GREEN);
  printf("  Games Won:\n");
  printf("     Classic-Easy: %d\n", profile.wonGame[0]);
  printf("     Classic-Difficult: %d\n", profile.wonGame[1]);
  printf("     Custom: %d\n", profile.wonGame[2]);
  iSetColor(I_COLOR_RED);
  printf("  Games Lost:\n");
  printf("     Classic-Easy: %d\n", profile.lostGame[0]);
  printf("     Classic-Difficult: %d\n", profile.lostGame[1]);
  printf("     Custom: %d\n", profile.lostGame[2]);
  iSetColor(I_COLOR_YELLOW);
  printf("  Games Played: %d\n", profile.gameP - 1);
  printf("  Three Most Recent Games: \n");
  printBoards(profile);
}

/*
  printBoards()

  This function gets all text from Point A = Profile.Name's Board 1: to 
  Point B = Profile.Name End.

  @param: profile - A struct Profile of the Player
 */
void printBoards(Profile profile) {

    FILE *file = fopen("prof.txt", "r");
    if (file == NULL) {
    printf("Error Opening File.");
    }
    string start;
    iSetColor(I_COLOR_CYAN);
    sprintf(start, "%s's Board 1:", profile.name);
    string check;
    sprintf(check, "%s End", profile.name);
    char line[256];
    int printing = 0; 

    while (fgets(line, sizeof(line), file)) {
        if (printing) {
            if (strstr(line, check)) {
                printing = 0;
                printf("    %s", line); 
            } else {
                printf("    %s", line); 
            }
        } else {
            if (strstr(line, start)) {
                printing = 1;
                printf("    %s", line);
            }
        }
    }

    fclose(file);
}

/*
  arrProf()

  This function stores all the Profile Names in one Array and updates a Variable
  that stores how many Profiles do we have.

  @param: names[] - A string array to store all the Profile Names
  @param: *numNames - A integer pointer that stores how many players do we have
 */
void arrProf(string names[], int *numNames) {
    FILE *file = fopen("profNames.txt", "a+");
    if (file == NULL) {
    printf("Error Opening File.");
    }

    // Initialize the Number of Names to 0
    *numNames = 0;

     while (*numNames < 10 && fscanf(file, "%20s", names[*numNames]) != EOF) {
        (*numNames)++;
        while (fgetc(file) != '\n' && !feof(file)); 
    }


    fclose(file);

    selSort(names, *numNames);

}

/*
  selSort()

  This function sorts all the Profile Names in one Array.

  @param: names[] - A string array to store all the Profile Names
  @param: n - A integer that stores how many players do we have
 */
void selSort(string arr[], int n) {
    int i, j, min;
    string temp;


    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[min]) < 0) {
                min = j;
            }
        }
        if (min != i) {
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[min]);
            strcpy(arr[min], temp);
        }
    }
}

/*
  profFinder()

  This function stores all the Profile Names in one Array and updates a Variable
  that stores how many Profiles do we have.

  @param: arr[] - A string array that stores all the Profile Names
  @param: name - A target string that stores what Profile are we finding
  @param: n - A integer that stores how many players do we have

  @return: found - Value to know if we found the profile that we are looking for

 */
int profFinder(string arr[], string name, int n){
  int found = 1;
  int i = 0;
  int end = 0;
  
  while (end != 1){
    
    if (strcmp(arr[i], name) == 0){
      found = 0;
      end = 1;
    }
    i++;

    if (i == 20){
      end = 1;
    }
  }

  return found;
}

/*
  createProfile()

  This function creates a Profile and prints it on a text file.

 */
Profile createProfile() {
  //Profile profileArr[20];
  int numProf = 0;
  int check = 0;
  int numNames;
  string arr[20];
  int nCheck = 0;

  arrProf(arr, &numNames);

  Profile profile;

  while (check != 1) {
    printf("Profile Name (3-20 characters): ");
    scanf("%s", profile.name);

    nCheck = profFinder(arr, profile.name, numNames);

    if (strlen(profile.name) >= 3 && strlen(profile.name) <= 20 && nCheck == 1) {
      printf("Valid Profile Name. Thank you!\n");
      check = 1; // Exit the loop if the name is valid
    } 
    else if (strlen(profile.name) < 3 && strlen(profile.name) > 20){
      printf("Invalid name length. Please enter a name with 3 to 20 "
             "characters.\n");
      while (getchar() != '\n')
        ; // Clear input buffer
    }
    else if (nCheck == 0){
      printf("Name is already used. Please enter a unique name.\n");
      while (getchar() != '\n')
        ; // Clear input buffer
    }
  }

  int i;

  for (i = 0; i < 3; i++) {
    profile.wonGame[i] = 0;
    profile.lostGame[i] = 0;
  }

  profile.gameP = 1;

  //profileArr[numProf] = profile;

  FILE *file = fopen("prof.txt", "a");
  if (file == NULL) {
    printf("Error Opening File.");
  }

  // fprintf(file,"Profile: ");
  fprintf(file, "%s ", profile.name);
  for (int i = 0; i < 3; i++) {
    fprintf(file, "%d ", profile.wonGame[i]);
  }
  for (int i = 0; i < 3; i++) {
    fprintf(file, "%d ", profile.lostGame[i]);
  }
  fprintf(file, "%d ", profile.gameP);
  fprintf(file, "\n");


  for (i = 0; i < 3; i++){
    fprintf(file, "%s's Board %d: \n", profile.name, i + 1);
  }

  fprintf(file, "\n");
  fprintf(file, "%s End\n", profile.name);
  fprintf(file, "\n");


  fclose(file);

  FILE *fp1 = fopen("profNames.txt", "a");

  if (fp1 == NULL) {
    printf("Error Opening File.");
  }

  int lead = 0;
  fprintf(fp1, "%s %d       ", profile.name, lead);
  fprintf(fp1, "\n");



  fclose(fp1);

  iSetColor(I_COLOR_YELLOW);
  printf("Profile is Saved.\n");

  blank();
  
  //printProfile(profileArr[numProf]);

  numProf++;
  iSetColor(I_COLOR_YELLOW);
  printf("Press any key to continue...");
  while(!kbhit()){}

  return profile;
}

/*
  viewStat()

  This function finds the name of our Profile and gets the details of the profile from
  the text file.

  @param: name - A target string that stores the name of our profile.
 */
void viewStat(string name) {
  int found = 0;
  Profile profile;

  FILE *file = fopen("prof.txt", "r");
  if (file == NULL) {
    printf("Error Opening File.");
  }


  int var;

  do{
    var = fscanf(file, "%s %d %d %d %d %d %d %d", profile.name, &profile.wonGame[0],
                &profile.wonGame[1], &profile.wonGame[2], &profile.lostGame[0],
                &profile.lostGame[1], &profile.lostGame[2], &profile.gameP);
    if (strcmp(profile.name, name) == 0) {
      found = 1;
    }
  }while(var != EOF && found != 1);

  fclose(file);

  if (found) {
    iSetColor(I_COLOR_YELLOW);
    printf("Profile found.\n");
    printf("\n");
    printProfile(profile);
  } else {
    iSetColor(I_COLOR_YELLOW);
    printf("Profile not found.\n");
    printf("\n");
  }
}

/*
  selProfile()

  This function selects what profile do we want to use and gets the values of the different
  variables of the profile and stores it in our program.

 */
void selProfile(int *programRunning){
    Profile profile;
    string arr[10];
    int name;
    int numNames, i;
    int nCheck = 0;
    char userChar;
    int cursorX = 20, cursorY = 21;

    arrProf(arr, &numNames);
    iSetColor(I_COLOR_CYAN);
    printf("               Select Your Profile: \n");
    for (i = 0; i < numNames; i++) {
        iSetColor(I_COLOR_YELLOW);
        printf("                    %d: %s\n",i + 1, arr[i]);
    }

  name = 1;
  userChar = ' ';
  while (nCheck != 1){
      iMoveCursor(cursorX, cursorY);
      userChar = getch();
      // printf("User char: %d\n", userChar);
      if (userChar == -32) {
        // printf("Up, down, left, or right?");
        userChar = getch();
        switch (userChar) {
        case 72: // Up arrow
          if (name-1 > 0 && name-1 <= numNames) {
            name--;
            cursorY--;
            iMoveCursor(cursorX, cursorY);
          }
          break;
        case 80: // Down arrow
          if (name+1 > 0 && name+1 <= numNames) {
            name++;
            cursorY++;
            iMoveCursor(cursorX, cursorY);
          }
          break;
        default:
          break;
        }
        
      } else if(userChar == 13){
        nCheck = 0;
        cursorX--;
        iMoveCursor(cursorX, cursorY);
        if (1 <= name && name <= numNames) {
            blank();
            printf("Profile found.\n");
            blank();
            nCheck = 1;
        } 
        else {
            blank();
            printf("Profile not found.\n");
            printf("Please Try Again.\n");
        }
      }
    
    
  }

  name -= 1;
  
    int found = 0;
    int var1, var2;
    FILE *file = fopen("prof.txt", "r");
    if (file == NULL) {
        printf("Error Opening File.");
    }


    do{
      var1 = fscanf(file, "%s %d %d %d %d %d %d %d", profile.name, &profile.wonGame[0],
                &profile.wonGame[1], &profile.wonGame[2], &profile.lostGame[0],
                &profile.lostGame[1], &profile.lostGame[2], &profile.gameP);
      if (strcmp(profile.name, arr[name]) == 0) {
            found = 1;
        }

    }while(var1 != EOF && found != 1);

    fclose(file);

    found = 0;
    FILE *fp1 = fopen("profNames.txt", "r");
    if (fp1 == NULL) {
        printf("Error Opening File.");
    }


    do{
      var2 = fscanf(file, "%s %d", profile.name, &profile.totalSec);
      if (strcmp(profile.name, arr[name]) == 0) {
            found = 1;
        }
    }while(var2 != EOF && found != 1);

    fclose(fp1);

  mainMenu(&profile, programRunning);
}

/*
  cursorStart()

  This function finds the target string and puts our invisible cursor at the string.

  @param: *file - pointer FILE to access our text file.
  @param: target - A target string that we use to find and put our cursor at.
 */
void cursorStart(FILE *file, string target) {
    char buffer[256]; 
    long startPos; 

    rewind(file);

    int found = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL && found == 0){
      if (strstr(buffer, target) != NULL) {
            startPos = ftell(file) - strlen(buffer);
            found = 1;
        }
    }

    fseek(file, startPos - 1, SEEK_SET);
}

/*
  profileChanger()

  This function updates the variables of our Profile and updates it in our text file.

  @param: *profile - a Profile pointer that stores the Profile that we are using
  @param: type - A integer that stores what type of Game are we playing
  @param: diff - A integer that stores the difficulty of our Game
  @param: win - A integer that stores if We Win, Lose or Quit
  @param: leader - A integer that stores if we will update the leaderboard scores
 */
void profileChanger(Profile *profile, int type, int diff, int win, int leader){

    if (type == 1 && diff == 1 && win == 1){
        profile->wonGame[0]++;
    }
    else if (type == 1 && diff == 2 && win == 1){
        profile->wonGame[1]++;
    }
    else if (type == 2 && win == 1){
        profile->wonGame[2]++;
    }
    else if (type == 1 && diff == 1 && win == 0){
        profile->lostGame[0]++;
    }
    else if (type == 1 && diff == 2 && win == 0){
        profile->lostGame[1]++;
    }
    else if (type == 2 && win == 0){
        profile->lostGame[2]++;
    }

    profile->gameP++;


  FILE *file = fopen("prof.txt", "r+");
  if (file == NULL) {
    printf("Error Opening File.");
  }

  cursorStart(file, profile->name);
  fprintf(file, "%s %d %d %d %d %d %d %d", profile->name, 
          profile->wonGame[0], profile->wonGame[1], profile->wonGame[2],
          profile->lostGame[0], profile->lostGame[1], profile->lostGame[2], profile->gameP);

  fclose(file);
  blank();
  
  if (leader == 1){
  delProfile2(profile->name);

  FILE *fp1 = fopen("profNames.txt", "a");
  if (file == NULL) {
    printf("Error Opening File.");
  }
  fprintf(fp1, "\n");

  fprintf(fp1, "%s %d", profile->name, profile->totalSec);
  fprintf(fp1, "\n");

  fclose(fp1);
  }
  
}

/*
  delProfile1()

  This function deletes the profile in our prof.txt file.

  @param: name - A target string that stores the name of our profile.
 */
void delProfile1(string name) {
    string end;
    sprintf(end, "%s End", name);
    FILE *fp = fopen("prof.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char buffer[1024];

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    int copy = 1; // Start copying by default
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Check for the start of the section to remove
        if (strstr(buffer, name) != NULL) {
            copy = 0; // Stop copying
        }

        // Copy the line if outside the section to remove
        if (copy) {
            fputs(buffer, temp);
        }

        // Check for the end of the section to remove
        if (strstr(buffer, end) != NULL) {
            copy = 1; // Resume copying
        }
    }

    fclose(fp);
    fclose(temp);

    // Remove the original file and rename the temp file to the original file name
    remove("prof.txt");
    rename("temp.txt", "prof.txt");

    printf("Deleted Successfully.\n");

}

/*
  delProfile2()

  This function deletes the profile in our profNames.txt file.

  @param: name - A target string that stores the name of our profile.
 */
void delProfile2(string name){
  FILE *fp = fopen("profNames.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Failed to open temporary file for writing");
        fclose(fp);
        return;
    }

    char buffer[256]; // Assuming each line won't exceed 255 characters
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Use strstr to find the target substring in the current line
        if (strstr(buffer, name) == NULL) {
            // If the line does not contain the target name, write it to the temp file
            fputs(buffer, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    // Remove the original file and rename the temp file to the original file name
    remove("profNames.txt");
    if (rename("temp.txt", "profNames.txt") != 0) {
        perror("Error renaming temporary file");
    } else {
        printf("Profile deleted successfully.\n");
    }
}

/*
  printBoardTex()

  This function prints our board into the text file.

  @param: board[][15] - a Struct Cell that stores our Board Values.
  @param: boardRows - A integer that stores how many rows do we have.
  @param: boardColumns - A integer that stores how many columns do we have.
  @param: fog - A integer that stores if will we put a fog or not.
  @param: file - pointer FILE to access our text file.
 */
void printBoardTex(struct Cell board[][15], int boardRows, int boardColumns,
                int fog, FILE *file){


    int i, j;
  for (i = 0; i < boardRows; i++) {
    if (i == 0) {
      fprintf(file, "  ");
      for (j = 0; j < boardColumns; j++) {
        if (j < 10) {
          fprintf(file, " %d ", j);
        } else {
          fprintf(file, "%d ", j);
        }
      }
      fprintf(file, "\n");
    }

    for (j = 0; j < boardColumns; j++) {
      if (j == 0) {
        fprintf(file, "%d  ", i);
      }
      if (board[i][j].state.isMine == 1 && fog == 0) {
        if(board[i][j].state.isFlagged){
          fprintf(file, "!  ");
        }
        else{
          fprintf(file, "X  ");
        }
      } else if (board[i][j].state.isFlagged == 1) {
        fprintf(file, "?  ");
      } else if (board[i][j].state.isRevealed == 0) {
        fprintf(file, ".  ");
      } else if (board[i][j].state.isRevealed == 1) {
        fprintf(file, "%d  ", board[i][j].adjacentMines);
      }
    }
    fprintf(file, "\n");
  }

}

/*
  copy()

  This function copies all the text that we got from the text file after the target string.

  @param: target - A target string that we will use to put our cursor at.
 */
void copy(string target){
    string text;

    FILE *fp1, *fp2;
    fp1 = fopen("prof.txt", "r");
    fp2 = fopen("dest.txt", "w");

    if(fp1 == NULL || fp2 == NULL)
    {
        printf("\nError reading file\n");
    }

    cursorStart(fp1, target);

    while (fgets(text, sizeof(text), fp1) != NULL){
        fprintf(fp2, "%s", text);
    }

    fclose(fp1);
    fclose(fp2);
}

/*
  paste()

  This function appends all the text that we get to another text file.

 */
void paste(){
    string text;

    FILE *fp1, *fp2;
    fp1 = fopen("prof.txt", "a");
    fp2 = fopen("dest.txt", "r+");

    if(fp1 == NULL || fp2 == NULL)
    {
        printf("\nError reading file\n");
    }

    while (fgets(text, sizeof(text), fp2) != NULL){
        fprintf(fp1, "%s", text);
    }

    fclose(fp1);
    fclose(fp2);

    remove("dest.txt");
}

/*
  rewriteFile()

  This function stores all the Profile Names in one Array and updates a Variable
  that stores how many Profiles do we have.

  @param: names[] - A string array to store all the Profile Names
  @param: *numNames - A integer pointer that stores how many players do we have
  
 */
void rewriteFile(FILE *sourceFile, FILE *destFile, long endPos) {
    char buffer[256];
    while (ftell(sourceFile) < endPos && fgets(buffer, sizeof(buffer), sourceFile) != NULL) {
        fputs(buffer, destFile);
    }
}

/*
  manipulate()

  This function prints the board into our text file.

  @param: target - The string that we will change the lines after.
  @param: copied - The string that we will start copying.
  @param: board[][15] - a Struct Cell that stores our Board Values.
  @param: state - A char that stores if we Won, Lost, or Quit
  @param: boardRows - A integer that stores how many rows do we have.
  @param: boardColumns - A integer that stores how many columns do we have.
  @param: *profile - a Profile pointer that stores the Profile that we are using

 */
void manipulate(string target, string copied, struct Cell board[][15], char state, int boardRows, int boardColumn, Profile *profile){
    copy(copied);
    
    FILE *file;

    file = fopen("prof.txt", "r+");

    if(file == NULL)
    {
        printf("\nError reading file\n");
    }

    int fog;

  if (state == 'W' || state == 'L'){
    fog = 0;
  }
  else if (state == 'Q'){
    fog = 1;
  }

    cursorStart(file, target);
    fprintf(file, "%s\n", target);

    fprintf(file, "%c %d %d\n", state, boardRows, boardColumn);
    printBoardTex(board, boardRows, boardColumn, fog, file);

    fprintf(file,"\n");

    long endPos = ftell(file);

    fclose(file);

 file = fopen("prof.txt", "r+");
    if (file == NULL) {
        printf("\nError reading file\n");
        return;
    }

    // Rewrite the file, discarding lines below the inserted text
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("\nError opening temporary file\n");
        fclose(file);
        return;
    }

    rewriteFile(file, temp, endPos);

    fclose(file);
    fclose(temp);

    // Replace original file with temporary file
    remove("prof.txt");
    rename("temp.txt", "prof.txt");

    paste();

}

/*
  sortProf()

  This function sorts the array of Profiles by their Total Seconds/Scores.

  @param: Prof[] - A string array to store all the Profile Names
  @param: numPlay - A integer that stores how many players do we have
 */
void sortProf(Profile Prof[], int numPlay) {
  Profile temp;
  int i,j;
    for (i = 0; i < numPlay - 1; i++) {
        for (j = 0; j < numPlay - i - 1; j++) {
            if (Prof[j].totalSec > Prof[j + 1].totalSec) {
                temp = Prof[j];
                Prof[j] = Prof[j + 1];
                Prof[j + 1] = temp;
            }
        }
    }
}

/*
  leaderBoards()

  This function gets all the Profiles and their Total Seconds/Scores and stores it into an
  array and Prints the Leaderboards.

 */
void leaderBoards(){
  FILE *file = fopen("profNames.txt", "r");
  if (file == NULL) {
    printf("Error Opening File.");
  }

  Profile prof[10];
  int numPlayers = 0;

  while (fscanf(file, "%s %d", prof[numPlayers].name, &prof[numPlayers].totalSec) == 2) {
        numPlayers++;
    }

  fclose(file);

  sortProf(prof, numPlayers);

  int cnt = 1;
  iSetColor(I_COLOR_CYAN);
  printf("                    Leaderboards\n");
    for (int i = 0; i < numPlayers; i++) {
        if (prof[i].totalSec != 0){
          iSetColor(I_COLOR_GREEN);
          printf("          #%d: ", cnt);
          iSetColor(I_COLOR_YELLOW);
          printf("%s ", prof[i].name);
          iSetColor(I_COLOR_GREEN);
          printf("- Seconds Taken: %d\n", prof[i].totalSec);
          cnt++;
        }
    }

  blank();
}

/*
  profile_mainMenu()

  This function displays the Menu for Profiles.

 */
void profile_mainMenu(int *programRunning) {
  system("cls");
  int userInput;
  string arr[10];
  int numNames;
  int check;
  char con;
  string name;
  int i;
  int cursorX = 20, cursorY = 21;
  int userChoosing;
  char userChar;

  arrProf(arr, &numNames);
  iSetColor(I_COLOR_PURPLE);
  blank();
  printMinesweeper();
  printf("\n");
  blank();
  iSetColor(I_COLOR_CYAN);
  printf("                    Choose a profile:\n");
  iSetColor(I_COLOR_YELLOW);
  printf("                    1: Create Profile\n");
  printf("                    2: Select Existing Profile\n");
  printf("                    3: Delete Existing Profile\n");

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
          if (userInput-1 > 0 && userInput-1 < 4) {
            userInput--;
            cursorY--;
            iMoveCursor(cursorX, cursorY);
          }
          break;
        case 80: // Down arrow
          if (userInput+1 > 0 && userInput+1 < 4) {
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
    if (numNames == 10){
      iClear(0, 20, 75, 7);
      iSetColor(I_COLOR_YELLOW);
      printf("The program has reached the maximum of 10 profiles.\n");
      printf("Please select an existing profile or delete a profile\n");
      printf("Press any key to continue...");
      while(!kbhit()){}
      profile_mainMenu(programRunning);
    }
    else{
      iClear(0, 20, 75, 7);
      createProfile();
      profile_mainMenu(programRunning);
      
    }
    break;
  case 2:
    iClear(0, 20, 75, 7);
    selProfile(programRunning);
    break;
  case 3:
    iClear(0, 20, 75, 7);
    printf("                    Select Your Profile: \n");
    for (i = 0; i < numNames; i++) {
        printf("                    %d: %s\n",i + 1, arr[i]);
    }
    blank();
    printf("Who do you want to delete (Type the Name): ");
    scanf("%s", name);
    
    check = profFinder(arr, name, numNames); 


    if(check == 0){
      printf("Profile is Found\n");
      printf("Are you sure? (Y/N): " );
      scanf(" %c", &con);

      if (con == 'Y' || con == 'y'){
        blank();
        delProfile1(name);
        delProfile2(name);
        profile_mainMenu(programRunning);

      }
      else{
        blank();
        profile_mainMenu(programRunning);
      }
    }
    break;
  default:
    break;
  }
}