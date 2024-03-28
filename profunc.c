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
}

/*
  arrProf()

  This function stores all the Profile Names in one Array and updates a Variable
  that stores how many Profiles do we have.

  @param: names[] - A string array to store all the Profile Names
  @param: *numNames - A integer pointer that stores how many players do we have
 */
void arrProf(string names[], int *numNames) {
    FILE *file = fopen("prof.txt", "a+");
    if (file == NULL) {
    printf("Error Opening File.");
    }

    // Initialize the Number of Names to 0
    *numNames = 0;
    while (*numNames < 40 && fscanf(file, "%20s", names[*numNames]) != EOF) {
        (*numNames)++;
        while (fgetc(file) != '\n' && !feof(file)); 
    }

    int i;

    int num = *numNames / 4;
    int cnt = 0;
    string temp[num];

    for (i = 0; i < *numNames; i++){
      if(i % 4 == 0){
        strcpy(temp[cnt], names[i]);
        cnt++;
      }
    }

    *numNames /= 4;

    for (i = 0; i < *numNames; i++){
      strcpy(names[i], temp[i]);
    }

    printf("arrprof\n");
    for(i = 0; i < *numNames; i++){
      printf("%s\n", names[i]);
    }
    printf("\n");

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

    printf("Selsort\n ");
    for(i = 0; i < n; i++){
      printf("%s\n", arr[i]);
    }
    printf("\n");
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

  profileArr[numProf] = profile;

  FILE *file = fopen("prof.txt", "a");
  if (file == NULL) {
    printf("Error Opening File.");
  }

  fprintf(file, "%s ", profile.name);
  for (int i = 0; i < 3; i++) {
    fprintf(file, "%d ", profile.wonGame[i]);
  }
  for (int i = 0; i < 3; i++) {
    fprintf(file, "%d ", profile.lostGame[i]);
  }
  fprintf(file, "\n");

  fprintf(file, "%s's Board 1: \n", profile.name);
  for (i = 0; i < 18; i++){
    fprintf(file, "\n");
  }


  fprintf(file, "%s's Board 2: \n", profile.name);
  for (i = 0; i < 18; i++){
    fprintf(file, "\n");
  }

  fprintf(file, "%s's Board 3: \n", profile.name);
  for (i = 0; i < 18; i++){
    fprintf(file, "\n");
  }

  fprintf(file, "\n");


  fclose(file);

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

  while (fscanf(file, "%s %d %d %d %d %d %d", profile.name, &profile.wonGame[0],
                &profile.wonGame[1], &profile.wonGame[2], &profile.lostGame[0],
                &profile.lostGame[1], &profile.lostGame[2]) != EOF) {
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

    printf("SelProf\n");

    for (i = 0; i < 10; i++){
      printf("%s\n", arr[i]);
    }

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

    while (fscanf(file, "%s %d %d %d %d %d %d", profile.name, &profile.wonGame[0],
                &profile.wonGame[1], &profile.wonGame[2], &profile.lostGame[0],
                &profile.lostGame[1], &profile.lostGame[2]) != EOF) {
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
    else if (type == 1 && win == 0){
        profile->lostGame[2]++;
    }


  FILE *file = fopen("prof.txt", "r+");
  if (file == NULL) {
    printf("Error Opening File.");
  }

  cursorStart(file, profile->name);
  fprintf(file, "%s %d %d %d %d %d %d", profile->name, 
          profile->wonGame[0], profile->wonGame[1], profile->wonGame[2],
          profile->lostGame[0], profile->lostGame[1], profile->lostGame[2]);

  fclose(file);
  blank();
}

void delProfile(string name) {
    Profile arr[10];
    int i = 0;
    int found = 0;

    FILE *file = fopen("prof.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char tempFileName[L_tmpnam];
    tmpnam(tempFileName);

    FILE *tempFile = fopen(tempFileName, "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%s %d %d %d %d %d %d", arr[i].name, &arr[i].wonGame[0],
                &arr[i].wonGame[1], &arr[i].wonGame[2], &arr[i].lostGame[0],
                &arr[i].lostGame[1], &arr[i].lostGame[2]) != EOF) {
        if (strcmp(arr[i].name, name) != 0) {
            fprintf(tempFile, "%s %d %d %d %d %d %d\n", arr[i].name, arr[i].wonGame[0],
                    arr[i].wonGame[1], arr[i].wonGame[2], arr[i].lostGame[0],
                    arr[i].lostGame[1], arr[i].lostGame[2]);
        } else {
            found = 1;
        }
        i++;
    }

    fclose(file);
    fclose(tempFile);

    if (found == 0) {
        printf("Profile not found.\n");
        return;
    }

    if (remove("prof.txt") != 0) {
        printf("Error removing file.\n");
        return;
    }
    if (rename(tempFileName, "prof.txt") != 0) {
        printf("Error renaming file.\n");
        return;
    }

    printf("Profile deleted successfully.\n");

    profile_mainMenu();
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
        fprintf(file, "X  ");
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

  fprintf(file, "HI BITCHES\n");
}

void recentGame(struct Cell board[][15], char state, int boardRows, int boardColumn, Profile *profile, int n){
  
  FILE *file = fopen("prof.txt", "r+");
  if (file == NULL) {
    printf("Error Opening File.");
  }

  int fog;

  if (state == 'W' || state == 'L'){
    fog = 0;
  }
  else if (state == 'Q'){
    fog = 1;
  }

  string check;
  sprintf(check, "%s's Board %d:", profile -> name, n);

  cursorStart(file, check);
  fseek(file, strlen(check) + 1, SEEK_CUR);
  fprintf(file, "\n");

  fprintf(file, "%c %d %d\n", state, boardRows, boardColumn);
  printBoardTex(board, boardRows, boardColumn, fog, file);
  fprintf(file, "HI FUCKERS\n");




  fclose(file);                
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
        delProfile(name);
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