#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* validateInputChar(char* input) {
    char* newInput[100];
    int newStrLength = 0;
    int i = 0;
    
    for (i = 0; i < strlen(input); i++) {
        /* The char needs to be a space, number, uppercase letter, or lowercase letter*/
        if ((input[i] >= 48 && input[i] <= 57) || (input[i] >= 65 && input[i] <= 90) || (input[i] >= 97 && input[i] >= 122) || input[i] == 32) {
            
            /* Strip out anything else */
            newInput[newStrLength] = input[i];
            newStrLength++;
        }
    }

    printf("%s\n", newInput);

    return newInput;
}

int validateInputInt(int input) {
    /* TODO: make sure the number is a valid number */

    return input;
}

char* getUserInputChar(char* message) {
    char* userInput = malloc(sizeof(char)*100);

    printf(message);
    scanf("%s", &userInput);

    return userInput; /*validateInputChar(userInput);*/
}

int getUserInputInt(char* message) {
    int userInput;

    printf(message);
    scanf("%d", &userInput);

    return validateInputInt(userInput);
}

int isPasswordValid(char* userPass) {
    
    char* passFile = "./password.txt";
    
    FILE* file_ptr = fopen(passFile, "r");
    int isValid = 0;

    /* TODO: change password permissions to be admin only read write too */

    if (file_ptr == NULL) {
        printf("\nFile '%s' does not exist.\n", passFile);
        return;
    }

    char* sys_Pass = fscanf(file_ptr, "%s");

    if (userPass == "123456") { /* sysPass) { // TODO: change to work with syspass */
        isValid = 1;
    }

    fclose(file_ptr);
    return isValid;
}

void changePassword(char* userPassword) {
    /* Change password with input given */
    char* passFile = "./password.txt";
    FILE* file_ptr = fopen(passFile, "w");

    /* TODO: change password permissions to be admin only read write too */

    if (file_ptr == NULL) {
        printf("\nFile '%s' does not exist.\n", *file_ptr);
        return;
    }

    fputs(userPassword, file_ptr);

    fclose(file_ptr);
}

int isUserVerified(char* message) {
    /*char* userVerify = getUserInputChar(message);*/
    printf(message);
    char* userVerify = malloc(sizeof(char)*100);
    scanf("%s", &userVerify);

    return 1;

    if (userVerify[0] == 'Y' || userVerify[0] == 'y') {
        return 1;
    }

    return 0;
}
