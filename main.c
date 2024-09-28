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
        printf("Invalid choice! Please enter a number between 1 and 6.\n");
    }
  }

  return 0;
}


void addStudent() {
  FILE *fp;   // File pointer for file operations
  Student s;  // Variable of type Student to hold the students's information
  

  // Open the file in append mode (to add data without overwriting)
  fp = fopen(FILE_NAME, "ab");
  if (fp == NULL) {
    printf("Error opening file!\n");
    return;
  }


  // Collect student details from the user
  printf("\n=== Add New Student ===\n");
  printf("Enter ID: ");
  scanf("%d", &s.id);
  printf("Enter Name: ");
  scanf("%[^\n]", &s.name);
  printf("Enter Age: ");
  scanf("%d", &s.age);
  printf("Enter Grade: ");
  scanf("%[^\n]", &s.grade);


  fwrite(&s, sizeof(Student), 1, fp);
  fclose(fp);

  printf("Student added successfully!\n");
}


void viewStudents() {
  FILE *fp;
  Student s;

  // Open the file in read mode
  fp = fopen(FILE_NAME, "rb");
  if (fp == NULL) {
    printf("No student records found.\n");
    return;
  }

  printf("\n--- List of Students ---\n");
  printf("ID\tName\t\tAge\tGrade\n");
  printf("----------------------------------------\n");

  // Read and display student's details one by one from the file
  while(fread(&s, sizeof(Student), 1, fp)) {
    printf("%d\t-15s\t%d\t%s\n", s.id, s.name, s.age, s.grade);
  }

  fclose(fp);
}


void searchStudent() {
  FILE *fp;
}
