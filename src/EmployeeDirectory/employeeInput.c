#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "directoryCRUD.c"
#include "helpers.c"

void modyifyDirectoryMenu(Employee* employees, int* employeesNum, FILE* file_ptr) {
    
    int choice = 0;

    /* Give these options: Add, Edit, Delete, Change Password */
    printf("\n\n----- Modify Employee Directory -----\n1. Add\n2. Edit\n3. Delete\n4. Change Password\n5. Cancel\n\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    int userEmployeeID;
    char* userFirstName = malloc(sizeof(char)*8);
    char* userLastName = malloc(sizeof(char)*8);
    char* userPosition = malloc(sizeof(char)*8);
    int userTelephone = 0;

    switch (choice) {
        case 1:;
            
            userEmployeeID = getUserInputInt("\nPlease enter Employee ID: ");

            if (isEmployeeInDirectory(employees, *employeesNum, userEmployeeID)) {
                printf("\nEmployee already exists\n");
                break;
            }

            printf("\nFirst Name: ");
            scanf("%s", userFirstName);

            printf("\nLast Name: ");
            scanf("%s", userLastName);

            printf("\nPosition: ");
            scanf("%s", userPosition);

            userTelephone = getUserInputInt("\nPlease enter Telephone number: ");

            Employee* newEmployee = malloc(sizeof(struct Employee));
            newEmployee->employeeID = userEmployeeID;
            newEmployee->firstName = userFirstName;
            newEmployee->lastName = userLastName;
            newEmployee->position = userPosition;
            newEmployee->telephone = userTelephone;

            *employeesNum += 1;

            Employee* newEmployees = malloc(sizeof(struct Employee)*(*employeesNum + 1));

            int j;
            for (j = 0; j < *employeesNum - 1; j++) {
                newEmployees[j] = employees[j];
            }
            newEmployees[*employeesNum-1] = *newEmployee;

            employees = newEmployees;

            writeDirectoryToFileUser(employees, *employeesNum);

            /* createEmployeeDirectory(employees, employeesNum, userEmployeeID, userLastName, userFirstName, userPosition, userTelephone); */
            break;
        case 2:;
            
            userEmployeeID = getUserInputInt("\nPlease enter Employee ID: ");

            if (!isEmployeeInDirectory(employees, *employeesNum, userEmployeeID)) {
                printf("\nEmployee does not exists\n");
                break;
            }
            
            displaySingleEmployeeDirectory(employees, *employeesNum, userEmployeeID);

            if (isUserVerified("\n\nAre you sure you want to edit? (y/n): ")) {

                char* userFirstName;
                char* userLastName;
                char* userPosition;
                int userTelephone;

                userFirstName = getUserInputChar("\nPlease enter First Name: ");
                userLastName = getUserInputChar("\nPlease enter Last Name: ");
                userPosition = getUserInputChar("\nPlease enter Position: ");
                userTelephone = getUserInputInt("\nPlease enter Telephone: ");

                editEmployeeDirectory(employees, employeesNum, userEmployeeID, userFirstName, userLastName, userPosition, userTelephone);
            }

            break;
        case 3:;
            userEmployeeID = getUserInputInt("\nPlease enter Employee ID: ");

            if (!isEmployeeInDirectory(employees, *employeesNum, userEmployeeID)) {
                printf("\nEmployee does not exists\n");
                break;
            }

            displaySingleEmployeeDirectory(employees, *employeesNum, userEmployeeID);

            /*if (isUserVerified("\n\nAre you sure you want to delete? (y/n): ")) {
            }*/
            deleteEmployeeDirectory(employees, employeesNum, userEmployeeID);

            break;
        case 4:;
            char* userPassword;
            userPassword = getUserInputInt("\nPlease enter new password: ");
            changePassword(userPassword);
            break;
        case 5:
            return;

        default:
            printf("Invalid Option. Choose a number shown.\n");
            break;
    }
}

void employeeDirectoryStart() {
    
    int choice = 0;
    int employeesNum = 0;

    char* filePath = "./directory.txt";
    FILE* file_ptr = fopen(filePath, "r");

    /* TODO: change permissions to be admin only read write*/

    if (file_ptr == NULL) { /* TODO: create file if doesn't exist*/
        printf("\nFile '%s' does not exist.\n", filePath);
        return;
    }

    /* Get number of entries */
    fread(&employeesNum, sizeof(int), 1, file_ptr);
    printf("n1: %d\n", employeesNum);

    Employee* employees = malloc(sizeof(Employee)*employeesNum);
    fread(&employees, sizeof(struct Employee), employeesNum, file_ptr);

    while (choice != 3) {
        printf("\n\n----- Employee Directory -----\n1. Read\n2. Modify\n3. Main Menu\n\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        /* Read */
        case 1:;
            filePath = "./directory.txt";
            file_ptr = fopen(filePath, "r");

            /* TODO: change permissions to be admin only read write*/

            if (file_ptr == NULL) { /* TODO: create file if doesn't exist*/
                printf("\nFile '%s' does not exist.\n", filePath);
                return;
            }

            /* Get number of entries */
            fread(&employeesNum, sizeof(int), 1, file_ptr);
            printf("n1: %d\n", employeesNum);

            employees = malloc(sizeof(Employee)*employeesNum);
            fread(&employees, sizeof(struct Employee), employeesNum, file_ptr);

            if (file_ptr) {fclose(file_ptr); file_ptr = NULL;}

            printf("\n\n| Employee ID | Last Name | First Name | Position | Telephone |\n");
            int i = 0;
            for (i; i < employeesNum; i++) {
                printf("%d,%s,%s,%s,%d\n", employees[i].employeeID, employees[i].lastName, employees[i].firstName, employees[i].position, employees[i].telephone);
            }

            break;
        /* Modify - Requires Password for Admin Access */
        case 2:;
            /* Ask for password */
            char* userPassword;
            userPassword = getUserInputChar("Modifying requires a password.\n\nPlease enter password: ");
            
            if (isPasswordValid(userPassword)) {
                modyifyDirectoryMenu(employees, &employeesNum, file_ptr);
            }
            else {
                printf("\nIncorrect password\n");
            }

            break;
        case 3:
            return;
        
        default:
            printf("Invalid Option. Choose a number shown.\n");
            break;
        }

    }

}

/*
//  Ask user if they want to modify or view an employee directory
// - If modify, then they need to give the password
// - Modifying includes adding editing or deleting
// - Viewing the directory just output the directory to a screen
// - Also ask the user if they want to modify the password

// The directyory is stopred in a file called directory.txt
// - permissions set to 644
// - Set the owner as root

// If the directory does not exist, then create it
// - CSV file one record per line
// - Cols: last_name, first_name, position, employee_id_number, telephone_number

// Program does not exit unless specified

// Compile as user and then change group (chgrp root) then change permissions to 4555
*/