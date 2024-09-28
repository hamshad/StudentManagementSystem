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
