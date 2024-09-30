#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"


// Define the structure for student with relevant fields
typedef struct {
  int id;
  char *name; // use pointers for name to dynamically allocate
  int age;
  char *grade; // use pointers for grade to dynamically allocate
} Student;

// Define function prototypes (functions that will be implemented later)
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
// function to clear the input buffer
void clearInputBuffer();
// creates student with dynamic memory allocation
// and returns Student's pointer
Student* createStudent();
void freeStudent(Student *s);

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
    printf("Enter your choice: \n");
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
      case 1: addStudent(); break;
      case 2: viewStudents(); break;
      case 3: searchStudent(); break;
      case 4: updateStudent(); break;
      case 5: deleteStudent(); break;
      case 6:
        printf("Exiting the program, Goodbye!\n");
        exit(EXIT_FAILURE);
      default:
        printf("Invalid choice! Please enter a number between 1 and 6.\n");
    }
  }

  return 0;
}


  // File pointer for file operations
void addStudent() {
  // Open the file in append mode (to add data without overwriting)
  FILE *fp = fopen(FILE_NAME, "ab");
  if (fp == NULL) {
    printf("Error opening file!\n");
    return;
  }

  // Dynamically allocate memory for new student
  Student *s = createStudent();

  // Collect student details from the user
  printf("\n=== Add New Student ===\n");
  printf("Enter ID: ");
  scanf("%d", &s->id);
  clearInputBuffer();

  printf("Enter Name: ");
  // scanf("%[^\n]", &s.name);
  // fgets(s.name, sizeof(s.name), stdin); // Input name
  // s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline

  // s->name = (char *)malloc(100 * sizeof(char)); // Allocate 100 characters for name
  // fgets(s->name, 100, stdin); // Read the name from user
  // s->name[strcspn(s->name, "\n")] = '\0'; // Remove the newline character at the end
  char tempName[100]; // Temp buffer for name input
  fgets(tempName, sizeof(tempName), stdin);
  tempName[strcspn(tempName, "\n")] = '\0'; // remove newline character
  s->name = strdup(tempName); // Allocate memory and copy the name
  
  printf("Enter Age: ");
  scanf("%d", &s->age);
  clearInputBuffer();

  printf("Enter Grade: ");
  // scanf("%[^\n]", &s.grade);
  // fgets(s.grade, sizeof(s.grade), stdin); // Input grade
  // s.grade[strcspn(s.grade, "\n")] = '\0'; // Remove newline

  // s->grade = (char *)malloc(10 * sizeof(char)); // Allocate 100 characters for grade
  // fgets(s->grade, 10, stdin); // Read the grade from user
  // s->grade[strcspn(s->grade, "\n")] = '\0'; // Remove the newline character at the end
  char tempGrade[10]; // Temp buffer for grade input
  fgets(tempGrade, sizeof(tempGrade), stdin);
  tempGrade[strcspn(tempGrade, "\n")] = '\0'; // remove newline character
  s->grade = strdup(tempGrade); // Allocate memory and copy the grade



  // write the student's details to the file
  // fwrite(s, sizeof(Student), 1, fp);
  
  // Write the basic student structure to the file
  fwrite(&s->id, sizeof(int), 1, fp); // Write ID
  fwrite(&s->age, sizeof(int), 1, fp); // Write Age
  
  // Write the name and grade (dynamic memory) as separate strings
  int nameLen = strlen(s->name) + 1; // Include null terminator
  fwrite(&nameLen, sizeof(int), 1, fp); // Write the length of the name
  fwrite(s->name, sizeof(char), nameLen, fp); // Write the name
  
  int gradeLen = strlen(s->grade) + 1; // Include null terminator
  fwrite(&gradeLen, sizeof(int), 1, fp); // Write the length of the grade
  fwrite(s->grade, sizeof(char), gradeLen, fp); // Write the grade

  // Free the dynamically allocated memory after writing to the file
  freeStudent(s);


  // Close the file
  fclose(fp);

  printf("Student added successfully!\n");
}


void viewStudents() {
  // int recordCount = 0; // To count how many records are being read

  // Open the file in read mode
  FILE *fp = fopen(FILE_NAME, "rb");
  if (fp == NULL) {
    printf("No student records found.\n");
    return;
  }

  Student *s = createStudent();
  int nameLen, gradeLen; // To store the length of name and grade
  // char name[100];
  // char grade[10];

  printf("\n--- List of Students ---\n");
  printf("ID\tName\t\tAge\tGrade\n");
  printf("----------------------------------------\n");

  // Read and display student's details one by one from the file
  // while(fread(&s, sizeof(Student), 1, fp) == 1) {
  while(fread(&s, sizeof(Student), 1, fp)) {
    // Read name and grade (store as separate lines in the file)
    // fgets(name, sizeof(name), fp);
    // fgets(grade, sizeof(grade), fp);
    

    fread(&s->age, sizeof(int), 1, fp); // Read age
    
    // Read the length of the name and then the name itself
    fread(&nameLen, sizeof(int), 1, fp);
    s->name = (char *)malloc(nameLen * sizeof(char));
    fread(s->name, sizeof(char), nameLen, fp);

    // Read the length of the grade and then the grade itself
    fread(&gradeLen, sizeof(int), 1, fp);
    s->grade = (char *)malloc(gradeLen * sizeof(char));
    fread(s->grade, sizeof(char), gradeLen, fp);

    // Print the student details
    printf("%d\t%-15s\t%d\t%s\n", s->id, s->name, s->age, s->grade);

    // Free the dynamically allocated memory for name and grade
    free(s->name);
    free(s->grade);
    // recordCount++; // Increment the count for each valid record

  }


  // if (recordCount == 0) {
  //   printf("No records to display.\n");
  // }

  freeStudent(s);
  fclose(fp);
}


void searchStudent() {

  FILE *fp;
  fp = fopen(FILE_NAME, "rb");
  if(fp == NULL) {
    printf("No student records found.\n");
    return;
  }

  int searchId; // student ID to search for
  

  Student *s = createStudent();
  int nameLen, gradeLen;
  int found = 0; // Flag to indicate whether the student was found
  

  printf("\n=== Search Student ===\n");
  printf("Enter Student ID to search: ");
  scanf("%d", &searchId);

  // Read through each student in the file to find the matching ID
  while(fread(&s, sizeof(Student), 1, fp)) {

    // Read ID and age
    fread(&s->age, sizeof(int), 1, fp);

    // Read name length and name
    fread(&nameLen, sizeof(int), 1, fp);
    s->name = (char*)malloc(nameLen * sizeof(char));
    fread(s->name, sizeof(char), nameLen, fp);

    // Read grade length and grade
    fread(&gradeLen, sizeof(int), 1, fp);
    &s->grade = (char*)malloc(gradeLen * sizeof(char));
    fread(s->grade, sizeof(char), gradeLen, fp);

    
    if (s->id == searchId) {
      printf("\nStudent Found:\n");
      printf("ID: %d\n", s->id);
      printf("Name: %s\n", s->name);
      printf("Age: %d\n", s->age);
      printf("Grade: %s\n", s->grade);
      found = 1; // Set the flag to indicate student is found
      break;
    }

    // Free memory allocated
    free(s->name);
    free(s->grade);
  }

  if (!found) {
    printf("Student with ID %d not found.\n", searchId);
  }

  fclose(fp);
}


void updateStudent() {
  FILE *fp, *tempFp; // fp - for main file, tempFp - for temporary file
  Student s;
  int searchId;
  int found = 0;

  fp = fopen(FILE_NAME, "rb");
  if (fp == NULL) {
    printf("No student records found.\n");
    return;
  }

  // Open temporary file in write mode to store updated data
  tempFp = fopen("temp.dat", "wb");
  if (tempFp == NULL) {
    printf("Error creating temporary file!\n");
    fclose(fp);
    return;
  }


  printf("\n=== Update Student ===\n");
  printf("Enter Student ID to update: \n");
  scanf("%d", &searchId);
  clearInputBuffer();

  // Read throuh the original file and copy data to the temporary file
  while (fread(&s, sizeof(Student), 1, fp)) {
    if (s.id == searchId) {

      printf("Enter new details for Student ID %d:\n", s.id);
      printf("Enter Name: ");
      // scanf("%[^\n]", &s.name);
      fgets(s.name, sizeof(s.name), stdin); // Input name
      s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline

      printf("Enter Age: ");
      scanf("%d", &s.age);
      clearInputBuffer();

      printf("Enter Grade: ");
      // scanf("%[^\n]", &s.grade);
      fgets(s.grade, sizeof(s.grade), stdin); // Input name
      s.grade[strcspn(s.grade, "\n")] = '\0'; // Remove newline
      
      found = 1; // Mark as found
    }

    fwrite(&s, sizeof(Student), 1, tempFp); // Write each student (updated of not)
  }

  fclose(fp);
  fclose(tempFp);

  if (found) {
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
    printf("Student record updated successfully!\n");
  } else {
    remove("temp.dat");
    printf("Student with ID %d not found.\n", searchId);
  }
}


void deleteStudent() {
  FILE *fp, *tempFp; // fp - for main file, tempFp - for temporary file
  Student s;
  int searchId;
  int found = 0;

  fp = fopen(FILE_NAME, "rb");
  if (fp == NULL) {
    printf("No student records found.\n");
    return;
  }

  // Open temporary file in write mode to store updated data
  tempFp = fopen("temp.dat", "wb");
  if (tempFp == NULL) {
    printf("Error creating temporary file!\n");
    fclose(fp);
    return;
  }


  printf("\n=== Delete Student ===\n");
  printf("Enter Student ID to delete: \n");
  scanf("%d", &searchId);

  // Read throuh the original file and copy data to the temporary file
  while (fread(&s, sizeof(Student), 1, fp)) {
    if (s.id == searchId) {
      found = 1;
      printf("Student with ID %d deleted successfull!\n", s.id);
    } else {
      fwrite(&s, sizeof(Student), 1, tempFp); // Write other students to the temporary file
    }
  }

  fclose(fp);
  fclose(tempFp);

  if (found) {
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
  } else {
    remove("temp.dat");
    printf("Student with ID %d not found.\n", searchId);
  }
}


void clearInputBuffer() {
  int c;
  // consume all characters until a newline
  while ((c = getchar()) != '\n' && c != EOF);
}


// Function to dynamically allocate memory for a new student
// It returns a pointer to the newly allocated Student
Student* createStudent() {
  // Allocate memory for a new Student and check if allocation was successfully
  Student *s = (Student *)malloc(sizeof(Student));
  if (s == NULL) {
    printf("Memory allocation failed!\n");
    exit(EXIT_FAILURE);
  }

  s->name = NULL;
  s->grade = NULL;

  return s;
}


// Function to free the dynamically allocated memory for a student
// This is important to prevent memroy leaks
void freeStudent(Student *s) {
  if (s != NULL) {
    free(s->name); // Free the memory allocated for the name
    free(s->grade); // Free the memory allocated for the grade
    free(s); // Free the memory allocated for the student structure intself
  }
}
