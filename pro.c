#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

#define MAX_STUDENTS 100

// Structure to store student details
struct Student 
{
    int id;
    int rollNumber;
    char name[50];
    char address[100];
    float fees;
    int marks[5]; // Marks for 5 specific subjects
};

// Subject names
const char *subjectNames[] =
 {
    "English",
    "Hindi",
    "Mathematics",
    "Science",
    "Sanskrit"
};

// Global variables
struct Student students[MAX_STUDENTS];
int studentCount = 0;

// Function prototypes
void welcomeScreen();
int login();
void mainMenu();
void addStudent();
void displayStudents();
void generateAxilSheet();
void saveToFile();
void loadFromFile();

int main() 
{
    loadFromFile(); // Load existing data
    
    welcomeScreen();
    
    if (login()) {
        mainMenu();
    } else {
        printf("\nInvalid password. Exiting...\n");
    }
    
    return 0;
}

void welcomeScreen() 
{
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t****************************************\n");
    printf("\t\t\t*                                      *\n");
    printf("\t\t\t*      COLLEGE MANAGEMENT SYSTEM       *\n");
    printf("\t\t\t*                                      *\n");
    printf("\t\t\t****************************************\n");
    printf("\n\n\t\t\tPress any key to continue...");
    getch();
}

int login()
 {
    char password[20];
    char ch;
    int i = 0;
    
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t****************************************\n");
    printf("\t\t\t*                                      *\n");
    printf("\t\t\t*           LOGIN PAGE                *\n");
    printf("\t\t\t*                                      *\n");
    printf("\t\t\t****************************************\n");
    
    printf("\n\n\t\t\tEnter Password: ");
    
    while (1)
     {
        ch = getch();
        if (ch == 13) { // Enter key
            password[i] = '\0';
            break;
        } else if (ch == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i] = ch;
            i++;
            printf("*");
        }
    }
    
    return strcmp(password, "jaihind") == 0;
}

void mainMenu() 
{
    int choice;
    
    do {
        system("cls");
        printf("\n\n\n");
        printf("\t\t\t****************************************\n");
        printf("\t\t\t*                                      *\n");
        printf("\t\t\t*          MAIN MENU                   *\n");
        printf("\t\t\t*                                      *\n");
        printf("\t\t\t****************************************\n");
        
        printf("\n\n\t\t\t1. Add Student");
        printf("\n\t\t\t2. Display All Students");
        printf("\n\t\t\t3. Generate Axil Sheet");
        printf("\n\t\t\t4. Save Data to File");
        printf("\n\t\t\t5. Exit");
        
        printf("\n\n\t\t\tEnter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                generateAxilSheet();
                break;
            case 4:
                saveToFile();
                break;
            case 5:
                printf("\n\t\t\tExiting...\n");
                break;
            default:
                printf("\n\t\t\tInvalid choice. Try again.");
                getch();
        }
    } while (choice != 5);
}

void addStudent() 
{
    system("cls");
    printf("\n\n\t\t\tADD STUDENT DETAILS\n");
    printf("\t\t\t-------------------\n");
    
    if (studentCount >= MAX_STUDENTS) 
    {
        printf("\n\t\t\tDatabase full. Cannot add more students.");
        getch();
        return;
    }
    
    printf("\n\t\t\tEnter Student ID: ");
    scanf("%d", &students[studentCount].id);
    
    printf("\n\t\t\tEnter Roll Number: ");
    scanf("%d", &students[studentCount].rollNumber);
    
    printf("\n\t\t\tEnter Name: ");
    scanf(" %[^\n]", students[studentCount].name);
    
    printf("\n\t\t\tEnter Address: ");
    scanf(" %[^\n]", students[studentCount].address);
    
    printf("\n\t\t\tEnter Fees: ");
    scanf("%f", &students[studentCount].fees);
    
    printf("\n\t\t\tEnter Marks for subjects:\n");
    for (int i = 0; i < 5; i++) {
        printf("\t\t\t%s: ", subjectNames[i]);
        scanf("%d", &students[studentCount].marks[i]);
    }
    
    studentCount++;
    printf("\n\t\t\tStudent added successfully!");
    getch();
}

void displayStudents() 
{
    system("cls");
    printf("\n\n\t\t\tSTUDENT DETAILS\n");
    printf("\t\t\t---------------\n");
    
    if (studentCount == 0)
     {
        printf("\n\t\t\tNo students in database.");
        getch();
        return;
    }
    
    for (int i = 0; i < studentCount; i++) 
    {
        printf("\n\t\t\tStudent ID: %d", students[i].id);
        printf("\n\t\t\tRoll Number: %d", students[i].rollNumber);
        printf("\n\t\t\tName: %s", students[i].name);
        printf("\n\t\t\tAddress: %s", students[i].address);
        printf("\n\t\t\tFees: %.2f", students[i].fees);
        printf("\n\t\t\tMarks: \n");
        for (int j = 0; j < 5; j++)
         {
            printf("\t\t\t%s: %d\n", subjectNames[j], students[i].marks[j]);
        }
        printf("\n\t\t\t------------------------------------");
    }
    
    getch();
}

void generateAxilSheet() 
{
    system("cls");
    printf("\n\n\t\t\tAXIL SHEET GENERATION\n");
    printf("\t\t\t---------------------\n");
    
    if (studentCount == 0)
     {
        printf("\n\t\t\tNo students in database.");
        getch();
        return;
    }
    
    int roll, found = 0;
    printf("\n\t\t\tEnter Roll Number: ");
    scanf("%d", &roll);
    
    for (int i = 0; i < studentCount; i++) 
    {
        if (students[i].rollNumber == roll) 
        {
            found = 1;
            
            // Calculate total and percentage
            int total = 0;
            for (int j = 0; j < 5; j++) {
                total += students[i].marks[j];
            }
            float percentage = (float)total / 5;
            
            // Display axil sheet
            printf("\n\n\t\t\tAXIL SHEET FOR %s", students[i].name);
            printf("\n\t\t\t------------------------------------");
            printf("\n\t\t\tStudent ID: %d", students[i].id);
            printf("\n\t\t\tRoll Number: %d", students[i].rollNumber);
            printf("\n\t\t\tName: %s", students[i].name);
            printf("\n\t\t\tAddress: %s", students[i].address);
            printf("\n\n\t\t\tMarks Obtained:");
            for (int j = 0; j < 5; j++) 
            {
                printf("\n\t\t\t%s: %d", subjectNames[j], students[i].marks[j]);
            }
            printf("\n\t\t\t------------------------------------");
            printf("\n\t\t\tTotal Marks: %d", total);
            printf("\n\t\t\tPercentage: %.2f%%", percentage);
            printf("\n\t\t\t------------------------------------");
            
            // Save to file
            FILE *file = fopen("axil_sheet.txt", "w");
            if (file != NULL) {
                fprintf(file, "AXIL SHEET FOR %s\n", students[i].name);
                fprintf(file, "------------------------------------\n");
                fprintf(file, "Student ID: %d\n", students[i].id);
                fprintf(file, "Roll Number: %d\n", students[i].rollNumber);
                fprintf(file, "Name: %s\n", students[i].name);
                fprintf(file, "Address: %s\n\n", students[i].address);
                fprintf(file, "Marks Obtained:\n");
                for (int j = 0; j < 5; j++) {
                    fprintf(file, "%s: %d\n", subjectNames[j], students[i].marks[j]);
                }
                fprintf(file, "------------------------------------\n");
                fprintf(file, "Total Marks: %d\n", total);
                fprintf(file, "Percentage: %.2f%%\n", percentage);
                fprintf(file, "------------------------------------\n");
                fclose(file);
                printf("\n\n\t\t\tAxil sheet saved to 'axil_sheet.txt'");
            } else {
                printf("\n\n\t\t\tError saving axil sheet to file.");
            }
            
            break;
        }
    }
    
    if (!found) 
    {
        printf("\n\t\t\tStudent with roll number %d not found.", roll);
    }
    
    getch();
}

void saveToFile()
 {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL)
     {
        printf("\n\t\t\tError opening file for writing.");
        getch();
        return;
    }
    
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), studentCount, file);
    
    fclose(file);
    printf("\n\t\t\tData saved to file successfully!");
    getch();
}

void loadFromFile() 
{
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL)
     {
        // File doesn't exist, first run
        return;
    }
    
    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), studentCount, file);
    
    fclose(file);
}