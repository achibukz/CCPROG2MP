#include "profunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
  blank() - Creates a Horizontal Dash for Display.
 */
void blank() {

  printf("---------------------------------------------------\n");
}

/*
  printProfile()

  This function displayes the Details of the Player.

  @param: profile - A struct Profile of the Player
 */
void printProfile(Profile profile) {
  printf("Profile Name: %s\n", profile.name);
  printf("  Games Won:\n");
  printf("     Classic-Easy: %d\n", profile.wonGame[0]);
  printf("     Classic-Difficult: %d\n", profile.wonGame[1]);
  printf("     Custom: %d\n", profile.wonGame[2]);
  printf("  Games Lost:\n");
  printf("     Classic-Easy: %d\n", profile.lostGame[0]);
  printf("     Classic-Difficult: %d\n", profile.lostGame[1]);
  printf("     Custom: %d\n", profile.lostGame[2]);
  printf("  Games Played: %d\n", profile.gameP - 1);
  printf("  Three Most Recent Games: \n");
  printBoards(profile);
}

void printBoards(Profile profile) {

    FILE *file = fopen("prof.txt", "r");
    if (file == NULL) {
    printf("Error Opening File.");
    }
    string start;
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

Profile createProfile() {
  Profile profileArr[20];
  int numProf = 0;
  int check = 0;
  int numNames;
  string arr[20];
  int nCheck = 0;

  arrProf(arr, &numNames);

  Profile profile;
  blank();

  while (check != 1) {
    printf("Profile Name (3-20 characters): ");
    scanf("%s", profile.name);

    nCheck = profFinder(arr, profile.name, numNames);
    printf("%d\n", nCheck);

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

  profileArr[numProf] = profile;

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
  fprintf(fp1, "%s ", profile.name);
  fprintf(fp1, "%d", lead);
  fprintf(fp1, "\n");



  fclose(fp1);

  blank();
  printf("Profile is Saved.\n");

  blank();
  printProfile(profileArr[numProf]);

  numProf++;


    mainMenu(&profile);
    return profile;
}

void viewStat(string name) {
    blank();
    printf("View Statistics\n");
    blank();
  int found = 0;
  Profile profile;

  FILE *file = fopen("prof.txt", "r");
  if (file == NULL) {
    printf("Error Opening File.");
  }

  while (fscanf(file, "%s %d %d %d %d %d %d %d", profile.name, &profile.wonGame[0],
                &profile.wonGame[1], &profile.wonGame[2], &profile.lostGame[0],
                &profile.lostGame[1], &profile.lostGame[2], &profile.gameP) != EOF) {
    if (strcmp(profile.name, name) == 0) {
      found = 1;
      break;
    }
  }

  fclose(file);

  if (found) {
    blank();
    printf("Profile found.\n");
    blank();
    printProfile(profile);
  } else {
    blank();
    printf("Profile not found.\n");
  }

  mainMenu(&profile);
}

// ALPHABETICAL ORDER
void selProfile(){
    Profile profile;
    string arr[10];
    int name;
    int numNames, i;
    int nCheck = 0;

    arrProf(arr, &numNames);

    printf("Select Your Profile: \n");
    for (i = 0; i < numNames; i++) {
        printf("%d: %s\n",i + 1, arr[i]);
    }
    
  while (nCheck != 1){
    printf("What profile will you use? (Select The Number) ");
    scanf("%d", &name);

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

  name -= 1;
  nCheck = 0;


    FILE *file = fopen("prof.txt", "r");
    if (file == NULL) {
        printf("Error Opening File.");
    }

    while (fscanf(file, "%s %d %d %d %d %d %d %d", profile.name, &profile.wonGame[0],
                &profile.wonGame[1], &profile.wonGame[2], &profile.lostGame[0],
                &profile.lostGame[1], &profile.lostGame[2], &profile.gameP) != EOF) {
        if (strcmp(profile.name, arr[name]) == 0) {
            break;
        }
    }

    fclose(file);

    mainMenu(&profile);
    


}

void cursorStart(FILE *file, string target) {
    char buffer[256]; 
    long startPos; 

    rewind(file);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, target) != NULL) {
            startPos = ftell(file) - strlen(buffer);
            break;
        }
    }

    fseek(file, startPos - 1, SEEK_SET);
}

void profileChanger(Profile *profile, int type, int diff, int win){

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
}

void delProfile1(string filename, string name) {
    string end;
    sprintf(end, "%s End", name);
    FILE *fp = fopen(filename, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    char buffer[1024];

    if (!fp || !tempFile) {
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
            fputs(buffer, tempFile);
        }

        // Check for the end of the section to remove
        if (strstr(buffer, end) != NULL) {
            copy = 1; // Resume copying
        }
    }

    fclose(fp);
    fclose(tempFile);

    // Remove the original file and rename the temp file to the original file name
    remove(filename);
    rename("temp.txt", filename);

    printf("Deleted Successfully.\n");

}

void delProfile2(string filename, string name){
  FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Failed to open file for reading");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Failed to open temporary file for writing");
        fclose(fp);
        return;
    }

    char buffer[256]; // Assuming each line won't exceed 255 characters
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Use strstr to find the target substring in the current line
        if (strstr(buffer, name) == NULL) {
            // If the line does not contain the target name, write it to the temp file
            fputs(buffer, tempFile);
        }
    }

    fclose(fp);
    fclose(tempFile);

    // Remove the original file and rename the temp file to the original file name
    remove(filename);
    if (rename("temp.txt", filename) != 0) {
        perror("Error renaming temporary file");
    } else {
        printf("Profile deleted successfully.\n");
    }
}

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

void rewriteFile(FILE *sourceFile, FILE *destFile, long endPos) {
    char buffer[256];
    while (ftell(sourceFile) < endPos && fgets(buffer, sizeof(buffer), sourceFile) != NULL) {
        fputs(buffer, destFile);
    }
}

void manipulate(string target, string cope, struct Cell board[][15], char state, int boardRows, int boardColumn, Profile *profile, int n){
    copy(cope);
    
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
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("\nError opening temporary file\n");
        fclose(file);
        return;
    }

    rewriteFile(file, tempFile, endPos);

    fclose(file);
    fclose(tempFile);

    // Replace original file with temporary file
    remove("prof.txt");
    rename("temp.txt", "prof.txt");

    paste();

}


void profile_mainMenu() {

  int userInput;
  string arr[10];
  int numNames;
  int check;
  char con;
  string name;
  int i;

  arrProf(arr, &numNames);
    
  blank();
  printf("1: Create Profile\n");
  printf("2: Select Existing Profile\n");
  printf("3: Delete Existing Profile\n");
  printf("What is your Choice: ");
  scanf("%d", &userInput);
  getchar();

  switch (userInput) {
  case 1:
    if (numNames == 10){
      printf("The Program has reached the Maximum of 10 Profiles.\n");
      printf("Please select an existing profile or Delete a Profile\n");
      profile_mainMenu();
    }
    else{
      createProfile();
      break;
    }
    
  case 2:
    selProfile();
    break;
  case 3:
    printf("Select Your Profile: \n");
    for (i = 0; i < numNames; i++) {
        printf("%d: %s\n",i + 1, arr[i]);
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
        delProfile1("prof.txt", name);
        delProfile2("profNames.txt", name);
        profile_mainMenu();

      }
      else{
        blank();
        profile_mainMenu();
      }
    }
    break;
  default:
    break;
  }
}