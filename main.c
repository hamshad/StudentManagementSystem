#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"


// Define the structure for student with relevant fields
typedef struct {
  int id;
  char name[50];
  int age;
  char grade[5];
} Student;

// Define function prototypes (functions that will be implemented later)
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

// Main Function
int main() {
  int choice;

  while(1) {
    printf("\n### Student Management System ###\n");
    printf("1. Add Student\n");
    printf("2. View All Students\n");
    printf("3. Search Student by ID\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Exit\n\n");
    printf("Enter yout choice: \n");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        addStudent();
        break;
      case 2:
        viewStudents();
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
        printf("Exiting the program, Goodbye!\n");
        exit(EXIT_FAILURE);
      default:
        printf(c"Invalid choice! Please enter a number between 1 and 6.\n");
    }
  }

  return 0;
}
