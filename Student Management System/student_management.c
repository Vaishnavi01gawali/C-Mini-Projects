#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILE_NAME "students.dat"

struct Student
{
    int rollNo;
    char name[50];
    char course[50];
    float marks;
};

struct Student students[MAX_STUDENTS];
int studentCount = 0;


/* Function declarations */
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void sortStudents();
void saveStudents();
void loadStudents();
void menu();


/* Main Function */
int main()
{
    loadStudents();

    menu();

    return 0;
}


/* Display Menu */
void menu()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM\n");
        printf("========================================\n");

        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Sort Students by Marks\n");
        printf("7. Save Students\n");
        printf("8. Exit\n");

        printf("========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                sortStudents();
                break;

            case 7:
                saveStudents();
                break;

            case 8:
                saveStudents();
                printf("\nThank you for using Student Management System!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while(choice != 8);
}


/* Add Student */
void addStudent()
{
	int i;
    if(studentCount >= MAX_STUDENTS)
    {
        printf("\nStudent limit reached!\n");
        return;
    }

    printf("\n========== ADD STUDENT ==========\n");

    printf("Enter Roll No: ");
    scanf("%d", &students[studentCount].rollNo);

    /* Check duplicate roll number */
    for(i = 0; i < studentCount; i++)
    {
        if(students[i].rollNo == students[studentCount].rollNo)
        {
            printf("Roll number already exists!\n");
            return;
        }
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", students[studentCount].name);

    printf("Enter Course: ");
    scanf(" %[^\n]", students[studentCount].course);

    printf("Enter Marks: ");
    scanf("%f", &students[studentCount].marks);

    if(students[studentCount].marks < 0 ||
       students[studentCount].marks > 100)
    {
        printf("Invalid marks! Marks should be between 0 and 100.\n");
        return;
    }

    studentCount++;

    saveStudents();

    printf("\nStudent added successfully!\n");
}


/* Display Students */
void displayStudents()
{
	int i;
    if(studentCount == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n================ STUDENT RECORDS ================\n");

    printf("%-10s %-25s %-20s %-10s\n",
           "Roll No", "Name", "Course", "Marks");

    printf("---------------------------------------------------\n");

    for(i = 0; i < studentCount; i++)
    {
        printf("%-10d %-25s %-20s %-10.2f\n",
               students[i].rollNo,
               students[i].name,
               students[i].course,
               students[i].marks);
    }

    printf("===================================================\n");
}


/* Search Student */
void searchStudent()
{
	int i;
    int rollNo;
    int found = 0;

    printf("\n========== SEARCH STUDENT ==========\n");

    printf("Enter Roll No to search: ");
    scanf("%d", &rollNo);

    for(i = 0; i < studentCount; i++)
    {
        if(students[i].rollNo == rollNo)
        {
            printf("\nStudent Found!\n");

            printf("Roll No : %d\n", students[i].rollNo);
            printf("Name    : %s\n", students[i].name);
            printf("Course  : %s\n", students[i].course);
            printf("Marks   : %.2f\n", students[i].marks);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nStudent not found!\n");
    }
}


/* Update Student */
void updateStudent()
{
	int i;
    int rollNo;
    int found = 0;

    printf("\n========== UPDATE STUDENT ==========\n");

    printf("Enter Roll No to update: ");
    scanf("%d", &rollNo);

    for(i = 0; i < studentCount; i++)
    {
        if(students[i].rollNo == rollNo)
        {
            printf("\nStudent Found!\n");

            printf("Current Name: %s\n", students[i].name);
            printf("Enter New Name: ");
            scanf(" %[^\n]", students[i].name);

            printf("Current Course: %s\n", students[i].course);
            printf("Enter New Course: ");
            scanf(" %[^\n]", students[i].course);

            printf("Current Marks: %.2f\n", students[i].marks);
            printf("Enter New Marks: ");
            scanf("%f", &students[i].marks);

            if(students[i].marks < 0 ||
               students[i].marks > 100)
            {
                printf("Invalid marks!\n");
                return;
            }

            saveStudents();

            printf("\nStudent updated successfully!\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nStudent not found!\n");
    }
}


/* Delete Student */
void deleteStudent()
{
	int i;
	int j;
    int rollNo;
    int found = 0;

    printf("\n========== DELETE STUDENT ==========\n");

    printf("Enter Roll No to delete: ");
    scanf("%d", &rollNo);

    for(i = 0; i < studentCount; i++)
    {
        if(students[i].rollNo == rollNo)
        {
            found = 1;

            /* Shift records */
            for(j = i; j < studentCount - 1; j++)
            {
                students[j] = students[j + 1];
            }

            studentCount--;

            saveStudents();

            printf("\nStudent deleted successfully!\n");

            break;
        }
    }

    if(found == 0)
    {
        printf("\nStudent not found!\n");
    }
}


/* Sort Students by Marks */
void sortStudents()
{
    struct Student temp;
    int i;
    int j;

    if(studentCount == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    for(i = 0; i < studentCount - 1; i++)
    {
        for(j = 0; j < studentCount - i - 1; j++)
        {
            if(students[j].marks < students[j + 1].marks)
            {
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\nStudents sorted by marks in descending order.\n");

    displayStudents();
}


/* Save Students to File */
void saveStudents()
{
    FILE *fp;

    fp = fopen(FILE_NAME, "wb");

    if(fp == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    fwrite(&studentCount, sizeof(int), 1, fp);

    fwrite(students,
           sizeof(struct Student),
           studentCount,
           fp);

    fclose(fp);
}


/* Load Students from File */
void loadStudents()
{
    FILE *fp;

    fp = fopen(FILE_NAME, "rb");

    if(fp == NULL)
    {
        /* File doesn't exist for first run */
        studentCount = 0;
        return;
    }

    fread(&studentCount, sizeof(int), 1, fp);

    fread(students,
          sizeof(struct Student),
          studentCount,
          fp);

    fclose(fp);
}
