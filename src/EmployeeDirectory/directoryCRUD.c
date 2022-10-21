#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int employeeID;
    char* firstName;
    char* lastName;
    char* position;
    int telephone;
} typedef Employee;

Employee* loadDirectoryFromFile(int* employeeNumOut) {
    char* filePath = "./directory.txt";
    FILE* file_ptr = fopen(filePath, "r");

    /* TODO: change permissions to be admin only read write*/

    if (file_ptr == NULL) { /* TODO: create file if doesn't exist*/
        printf("\nFile '%s' does not exist.\n", filePath);
        return;
    }

    /* Get number of entries */
    fread(employeeNumOut, sizeof(int), 1, file_ptr);

    Employee* employees = malloc(sizeof(Employee)* (*employeeNumOut));
    fread(employees, sizeof(struct Employee), employeeNumOut, file_ptr);
    return employees;
}

void writeDirectoryToFile(Employee* employees, int employeesNum) {

    char* filePath = "./directory.txt";
    FILE* file_ptr = fopen(filePath, "w");

    /* TODO: change permissions to be admin only read write*/

    if (file_ptr == NULL) { /* TODO: create file if doesn't exist*/
        printf("\nFile '%s' does not exist.\n", filePath);
        return;
    }

    int employeeIndex = 0;
    char* outputStr[100];

    /*for (employeeIndex; employeeIndex < employeesNum; employeeIndex++) {
        fwrite(employees, sizeof(struct Employee), employeesNum, file_ptr);
    }*/

    for (employeeIndex; employeeIndex < employeesNum; employeeIndex++) {
        sprintf(outputStr, "%d,%s,%s,%s,%d\n", employees[employeesNum].employeeID, employees[employeesNum].lastName, employees[employeesNum].firstName, employees[employeesNum].position, employees[employeesNum].telephone);
        fputs(outputStr, file_ptr);
    }

    fclose(file_ptr);
}
void writeDirectoryToFileUser(Employee* employees, int employeesNum) {

    char* filePath = "./directory.txt";

    remove(filePath);

    FILE* file_ptr = fopen(filePath, "w");

    /* TODO: change permissions to be admin only read write*/

    if (file_ptr == NULL) { /* TODO: create file if doesn't exist*/
        printf("\nFile '%s' does not exist.\n", filePath);
        return;
    }

    fwrite(&employeesNum, sizeof(employeesNum), 1, file_ptr);

    int numWritten = 0;
    numWritten = fwrite(&employees, sizeof(struct Employee), employeesNum, file_ptr);

    char* buffer = "buffer";
    fwrite(buffer, sizeof(buffer), 1, file_ptr);

    printf("\n%d records written.\n", numWritten);

    fclose(file_ptr);
}
void writeDirectoryToFileMan(int id, char* lastName, char* firstName, char* position, int telephone) {

    char* filePath = "./directory.txt";
    FILE* file_ptr = fopen(filePath, "w+");

    /* TODO: change permissions to be admin only read write*/

    if (file_ptr == NULL) { /* TODO: create file if doesn't exist*/
        printf("\nFile '%s' does not exist.\n", filePath);
        return;
    }

    char* outputStr[1000] = {0};

    sprintf(outputStr, "%d,%s,%s,%s,%d\n", id, lastName, firstName, position, telephone);
    fputs(outputStr, file_ptr);

    fclose(file_ptr);
}

int isEmployeeInDirectory(Employee* employees, int employeesNum, int employee_id_number) {
    int isFound = 0;
    int employeeIndex = 0;

    for (employeeIndex; employeeIndex < employeesNum; employeeIndex++) {
        if (employees[employeeIndex].employeeID == employee_id_number) {
            isFound = 1;
            break;
        }
    }

    return isFound;
}

void displayOutputHeader() {
    printf("\n\n| Employee ID | Last Name | First Name | Position | Telephone |\n");
}

void displayEmployeeInfo(Employee employee) {
    printf("| %-11d | %-9s | %-10s | %-8s | %-9d |\n", employee.employeeID, employee.lastName, employee.firstName, employee.position, employee.telephone);
}

void displayEmployee(Employee employee) {
    displayOutputHeader();
    displayEmployeeInfo(employee);
}

void displaySingleEmployeeDirectory(Employee* employees, int employeesNum, int employee_id_number) {
    if (employeesNum < 1) {
        printf("\nNo employees in directory\n");
    }

    int employeeIndex = 0;

    for (employeeIndex; employeeIndex < employeesNum; employeeIndex++) {
        if (employees[employeeIndex].employeeID == employee_id_number) {
            displayEmployee(employees[employeeIndex]);
            break;
        }
    }
}

void displayEmployeeDirectory(Employee* employees, int employeesNum) {
    if (employeesNum < 1) {
        printf("\nNo employees in directory\n");
    }

    int employeeIndex = 0;

    for (employeeIndex; employeeIndex < employeesNum; employeeIndex++) {
        displayEmployee(employees[employeeIndex]);
    }
}


Employee* createEmployeeDirectory(Employee* employees, int* employeesNum, int employee_id_number, char* last_name, char* first_name, char* position, int telephone_number) {
    Employee* newEmployee = malloc(sizeof(Employee));
    Employee* newEmployees = malloc(sizeof(Employee) * (*employeesNum + 1));
   
    newEmployee->employeeID = employee_id_number;
    newEmployee->lastName = last_name;
    newEmployee->firstName = first_name;
    newEmployee->position = position;
    newEmployee->telephone = telephone_number;

    int employeeIndex = 0;

    for (employeeIndex; employeeIndex < *employeesNum; employeeIndex++) {
        newEmployees[employeeIndex] = employees[employeeIndex];
    }


    newEmployees[*employeesNum] = *newEmployee;
    *employeesNum += 1;
    employees = newEmployees;

    writeDirectoryToFileUser(newEmployees, *employeesNum);
    return newEmployees;
}

Employee* editEmployeeDirectory(Employee* employees, int* employeeNum, int employee_id_number, char* last_name, char* first_name, char* position, int telephone_number) {
    if (*employeeNum < 1) {
        printf("\nNo employees in directory\n");
    }

    Employee* newEmployee = malloc(sizeof(Employee));
    newEmployee->employeeID = employee_id_number;
    newEmployee->lastName = last_name;
    newEmployee->firstName = first_name;
    newEmployee->position = position;
    newEmployee->telephone = telephone_number;

    int employeeIndex = 0;

    for (employeeIndex; employeeIndex < *employeeNum; employeeIndex++) {
        if (employees[employeeIndex].employeeID != employee_id_number) {
            employees[employeeIndex] = *newEmployee;
        }
    }

    writeDirectoryToFileUser(employees, *employeeNum);
    free(newEmployee);
    return employees;
}

Employee* deleteEmployeeDirectory(Employee* employees, int* employeesNum, int employee_id_number) {
    if (employeesNum < 1) {
        printf("\nNo employees in directory\n");
        return malloc(sizeof(Employee)*0);
    }

    int newEmployeesNum = 0;

    Employee* newEmployees = malloc(sizeof(Employee)*(*employeesNum));

    int employeeIndex = 0;

    for (employeeIndex; employeeIndex < *employeesNum; employeeIndex++) {
        if (employees[employeeIndex].employeeID != employee_id_number) {
            newEmployees[newEmployeesNum] = employees[employeeIndex];
            newEmployeesNum += 1;
        }
    }

    *employeesNum = newEmployeesNum;
    employees = newEmployees;
    
    writeDirectoryToFileUser(employees, *employeesNum);
    return employees;
}