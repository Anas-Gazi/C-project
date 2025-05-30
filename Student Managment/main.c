#include<stdio.h>
#include<string.h>
#define MAX_STUDENTS 100

//login part
int login(){
  char username[20],password[20];
  const char correctUser[] = "admin";
  const char correctPass[] = "1234";

  printf("----LOGIN REQUIRED----\n\n");
  printf("Username: ");
  scanf("%s",username);
  printf("Password: ");
  scanf("%s",password);

  if(strcmp(username , correctUser) == 0 &&   strcmp(password, correctPass) == 0){
        printf(" Login successful!\n\n");
        return 1;
     }else{
        printf("Invalid username or password. Exiting...\n");
        return 0;
     }
}

//grade calvulation
char calculateGrade(float marks){
  if(marks>=80) return 'A';
  else if(marks>=70) return 'B';
  else if(marks>=60) return 'C';
  else if(marks>=50) return 'D';
  else return 'F';
}
//student data type
struct student{
  char name[50];
  int id;
  float marks;
  char grade;
};

//counting students
struct student students[MAX_STUDENTS];
int studentCount =0;

// add students
void addstudent(){
  if(studentCount >= MAX_STUDENTS){
    printf("Student limit reached!\n");
    return;
  }
  struct student s;

  printf("Enter Students name: ");
  //while ((getchar()) != '\n');
  //scanf("%[^\n]%*c",s.name); // read full name with space

  scanf(" %[^\n]", s.name);
  printf("Enter id: ");
  scanf("%d",&s.id);
  printf("Enter Marks: ");
  scanf("%f", &s.marks);

  s.grade = calculateGrade(s.marks); // Calculate grade correctly
  students[studentCount] = s; // Save to the global array
  studentCount++;
  printf("Student added successfully!\n\n");
}

//view students
void viewStudents(){
if (studentCount ==0){
        printf("No student to display. \n\n");
        return;
    }
    printf("------Student list--------\n");
    for(int i=0; i<studentCount; i++){
        printf("Student %d:\n", i + 1);
        printf("Name : %s\n", students[i].name);
        printf("ID   : %d\n", students[i].id);
        printf("Marks: %.2f\n", students[i].marks);
        printf("Grade: %c\n\n", students[i].grade);
    }

}
// save students info
void saveToFile(){
 FILE *file= fopen("Students.txt", "w");
  if(file == NULL){
     printf("Error opening file for writing!\n");
     return;
  }
  for(int i=0; i<studentCount; i++){
    fprintf(file, "Name: %s\n", students[i].name);
    fprintf(file, "Id: %d\n", students[i].id);
    fprintf(file, "Marks: %2f\n", students[i].marks);
  }
  fclose(file);
  printf("Student data saved to 'students.txt'.\n");
}

//search studients
void searchStudents(struct student students[], int count){
 char search[100];
 int found =0;
 printf(" Enter student ID or name to search: ");
 scanf("%[^\n]", search); // this will read full line , we can use gets and puts here
 for(int i = 0; i<count; i++){
        char idString[20];
        sprintf(idString, "%d",students[i].id);// convert int to string
    if(strcmp(/*students[i].id*/idString, search) ==0 || strcmp(students[i].name, search)==0){
        printf("\nStudent found: \n");
        printf("Student %d:\n", i + 1);
        printf("Name : %s\n", students[i].name);
        printf("ID   : %d\n", students[i].id);
        printf("Marks: %.2f\n\n", students[i].marks);
        found=1;
        break;
    }
 }if(!found){
   printf("\nStuden not found\n");
 }
}

// short student by marks
void sortStudentsByMarks(struct student students[], int count){
 struct student temp;

 for (int i=0; i<count-1; i++){
    for (int j=i+1; j<count; j++){
        if(students[i].marks < students[j].marks){
            temp = students[i];
            students[i]= students[j];
            students[j]= temp;
        }
    }
 }
 printf("Students sorted by marks (highest to lowest).\n");
}
// delete student

void deleteStudent(struct student students[], int *count) {
    char idstr[20];
    int found = 0;


    printf("Enter the ID of the student to delete: ");
    scanf(" %[^\n]", idstr);

    for (int i = 0; i < *count; i++) {

        char studentIdStr[20];
        sprintf(studentIdStr, "%d", students[i].id);  // Convert int ID to string

        if (strcmp(/*students[i].id*/studentIdStr, idstr) == 0) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            found = 1;
            printf("Student with ID %s deleted.\n", idstr);
            break;
        }
    }

    if (!found) {
        printf("No student found with that ID\n");
    }
}


// main function
int main()
{
    if(!login()){
        return 0;
    }
  int choice;
  do{
    printf("\n\n===== Student Grade Management =====\n");
    printf("1. Add student: \n");
    printf("2. View student: \n");
    printf("3. Save and exit: \n");
    printf("4. Search Student\n");
    printf("5. Sort Students by Marks\n");
    printf("6. Delete student ");
    printf("\nSelect an option by entering a number (1–6): ");
    scanf("%d", &choice);

    if(choice == 1){
      addstudent();
    } else if(choice ==2){
      viewStudents();
     }else if(choice==3){
     saveToFile();
     printf("Exiting the program.\n");
     }else if(choice ==4){
     searchStudents(students, studentCount);
     } else if(choice ==5){
     sortStudentsByMarks(students, studentCount);
     }else if(choice ==6){
     deleteStudent(students, &studentCount);
     }

    // option 2, 3

  }while(choice !=3); // it show menu again & again until user input 3... means save and exist :)
  return 0;
}
