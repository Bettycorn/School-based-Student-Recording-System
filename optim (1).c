#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Max Student
#define MAX 1000

//Global Student Count Variable
int studentCount = 0;

//Structure for Student Record
struct Student {
    char fullName[50];
    char sex;
    int year;
    char snum[20];
    char course[50];
} students[MAX];

//Function Prototypes
void addStudent();
void displayAllRecords();
void displayRecord();
void updateRecord();
void deleteStudent();
void saveToFile();
void loadFromFile();
void quickSort(int low, int high);
int partition(int low, int high);
void swap(struct Student* a, struct Student* b);
int isDuplicate(char snum[]);
int isValidStudentNum(char snum[]);
int isValidSex(char sex);
int isValidYear(int year);

//Main Function
int main() {
    int userOpt;

    printf("Student Record System.\n");

    while (1) {
        printf("\nSelect Option:\n");
        printf("[1] Add a Student Record\n");
        printf("[2] Display All Records\n");
        printf("[3] Display a Record Given Student Number\n");
        printf("[4] Update a Record Given Student Number\n");
        printf("[5] Delete a Student Record\n");
        printf("[6] Load Records from File\n");
        printf("[7] Save Records to File\n");
        printf("[8] Exit\n");
        printf(">>> ");

        //Check if userOpt is a Valid Integer
        if (scanf("%d", &userOpt) != 1) {
            printf("Invalid Input! Please Enter a Number Between 1 and 8.\n");
            while (getchar() != '\n'); // Clear Invalid Input
            continue;
        }

        //Switch-Case for userOpt
        switch (userOpt) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllRecords();
                break;
            case 3:
                displayRecord();
                break;
            case 4:
                updateRecord();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                loadFromFile();
                break;
            case 7:
                saveToFile();
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid Option! Please Enter a Number Between 1 and 8.\n");
        }
    }

    return 0;
}

//Add Student Function
void addStudent() {
	//Check if Student Count Max Reached
    if (studentCount >= MAX) {
        printf("Maximum Number of Students Reached!\n");
        return;
    }

    printf("\nAdd Student\n");

    //Input Student Number
    while (1) {
        printf("Input Student Number (Format: e.g., 20xx-10xxx): ");
        scanf("%s", students[studentCount].snum);
		
		//Check if not Duplicate and is Valid
        if (!isDuplicate(students[studentCount].snum) && isValidStudentNum(students[studentCount].snum)) {
            break;
        } else {
            printf("*Student Number Must Be UNIQUE / Student Number Must Follow Format (e.g., 20xx-10xxx)*\n\n");
        }
    }

    //Input Full Name
    printf("Input Full Name: ");
    getchar(); //Clear Newline From Previous scanf
    fgets(students[studentCount].fullName, sizeof(students[studentCount].fullName), stdin);
    students[studentCount].fullName[strcspn(students[studentCount].fullName, "\n")] = '\0'; //Remove Newline

    //Input Sex
    while (1) {
        printf("Input Sex (M/F): ");
        scanf(" %c", &students[studentCount].sex);

		//Check if Sex Input is Valid
        if (isValidSex(students[studentCount].sex)) {
            break;
        } else {
            printf("*Invalid Sex! Please enter 'M' or 'F'*\n\n");
        }
    }

    //Input Year
    while (1) {
        printf("Input Year Level: ");

		//Check if Year Input is Valid
        if (scanf("%d", &students[studentCount].year) == 1 && isValidYear(students[studentCount].year)) {
            break;
        } else {
            printf("Invalid Year! Please enter a positive integer (e.g., 1-5).*\n\n");
        
        }
    }

    //Input Course
    printf("Input Course (Acronym only, e.g., BSDS): ");
    getchar(); //Clear Newline From Previous scanf
    fgets(students[studentCount].course, sizeof(students[studentCount].course), stdin);
    students[studentCount].course[strcspn(students[studentCount].course, "\n")] = '\0'; //Remove Newline

    studentCount++;
    printf("*Student Added*\n");
}

//Display All Records
void displayAllRecords() {
	
	//Check if No Records
    if (studentCount == 0) {
        printf("*No Records*\n");
        return;
    }

	//Sort by Year and Course
    quickSort(0, studentCount - 1);

    int currentYear = -1;
    char currentCourse[50];
    int studentIndex = 0;

	//Loop to Display All Records
	int i;
    for (i = 0; i < studentCount; i++) {
        if (students[i].year != currentYear || strcmp(students[i].course, currentCourse) != 0) {
            printf("\n%d Year Level - %s\n", students[i].year, students[i].course);
            currentYear = students[i].year;
            strcpy(currentCourse, students[i].course);
            studentIndex = 1;
        } else {
            studentIndex++;
        }

        printf("  Student %d:\n", studentIndex);
        printf("    Full Name: %s\n", students[i].fullName);
        printf("    Sex: %c\n", students[i].sex);
        printf("    Snum: %s\n\n", students[i].snum);
    }
}

//Display Record By Student Number
void displayRecord() {
    int found = 0;
    char snum[20];

	//Input Student Number
    printf("\nInput Student Number: ");
    scanf("%s", snum);

	//Find Corresponding Student Number
	int i;
    for (i = 0; i < studentCount; i++) {
        if (strcmp(students[i].snum, snum) == 0) {
            printf("   Full Name: %s\n", students[i].fullName);
            printf("   Sex: %c\n", students[i].sex);
            printf("   Year: %d\n", students[i].year);
            printf("   Student Number: %s\n", students[i].snum);
            printf("   Course: %s\n", students[i].course);
            found = 1;
            break;
        }
    }

	//No Record Found
    if (!found) {
        printf("*No Record Found*\n");
    }
}

//Update Record by Student Number
void updateRecord() {
    int found = 0;
    char snum[20], newSnum[20];

	//Input Student Number
    printf("\nInput Student Number: ");
    scanf("%s", snum);

	//Find Student Number
	int i;
    for (i = 0; i < studentCount; i++) {
        if (strcmp(students[i].snum, snum) == 0) {
            found = 1;

            //Update Student Number
            while (1) {
                printf("Input New Student Number: ");
                scanf("%s", newSnum);

				//Check if not Duplicate and is Valid
                if (isValidStudentNum(newSnum) && (strcmp(newSnum, snum) == 0 || !isDuplicate(newSnum))) {
                    strcpy(students[i].snum, newSnum);
                    break;
                } else {
                    printf("*Student Number Must Be UNIQUE / Student Number Must Follow Format (e.g., 20xx-10xxx)*\n\n");
                }
            }

            //Update Full Name
            printf("Input New Full Name: ");
            getchar(); //Clear Newline From Previous scanf
            fgets(students[i].fullName, sizeof(students[i].fullName), stdin);
            students[i].fullName[strcspn(students[i].fullName, "\n")] = '\0'; //Remove Newline 

            //Update Sex
            while (1) {
                printf("Input New Sex (M/F): ");
                scanf(" %c", &students[i].sex);

				//Check if Sex Input is Valid
                if (isValidSex(students[i].sex)) {
                    break;
                } else {
                    printf("*Invalid Sex! Please enter 'M' or 'F'*\n\n");
                }
            }

            //Update Year
            while (1) {
                printf("Input New Year: ");
                
                //Check if Year Input is Valid
                if (scanf("%d", &students[i].year) == 1 && isValidYear(students[i].year)) {
                    break;
                } else {
                    printf("*Invalid Year! Please enter a positive integer (e.g., 1-5).*\n\n");
                }
            }

            //Update Course
            printf("Input New Course (Acronym only, e.g., BSDS): ");
            getchar(); //Clear Newline From Previous scanf
            fgets(students[i].course, sizeof(students[i].course), stdin);
            students[i].course[strcspn(students[i].course, "\n")] = '\0'; //Remove Newline

            printf("*Record %s Updated*\n", snum);
            break;
        }
    }
	
	//No Record Found
    if (!found) {
        printf("*No Record Found*\n");
    }
}

//Delete Student Record
void deleteStudent() {
    int found = 0;
    char snum[20];

	//Input Student Number to Delete
    printf("\nInput Student Number: ");
    scanf("%s", snum);

	//Find Record
	int i, j;
    for (i = 0; i < studentCount; i++) {
    	
    	//Shift Succeeding Students to the Left of the Array Instance
        if (strcmp(students[i].snum, snum) == 0) {
            found = 1;
            for (j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            
            //-1 Student
            studentCount--;
            printf("*Record %s Deleted*\n", snum);
            break;
        }
    }
	
	//No Record Found
    if (!found) {
        printf("*No Record Found*\n");
    }
}

//Save to File
void saveToFile() {
    char filename[50];
    int i;

    //Input File Name
    printf("Enter Filename: ");
    scanf("%s", filename);
    strcat(filename, ".txt");

    //Open File
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error Opening File!\n");
        return;
    }

    //Print Records in File
    for (i = 0; i < studentCount; i++) {
        fprintf(file, "%s %c %d %s %s\n",
                students[i].fullName,
                students[i].sex,
                students[i].year,
                students[i].snum, 
                students[i].course);
    }

	//Close File
    fclose(file);
    printf("*All Local Records Saved in File*\n");
}

//Load File
void loadFromFile() {
    char filename[50];
    
    //Input File Name
    printf("Enter Filename to Load Records: ");
    scanf("%s", filename);
    strcat(filename, ".txt");

	//Open File
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No File Found.\n\n");
        return;
    }
	
	char tempFullName[50];
	char tempSex;
	int tempYear;
	char tempSnum[20];
	char tempCourse[30];
	
    //Count Existing Students
    while (studentCount < MAX && fscanf(file, "%s %c %d %s %s", 
           tempFullName, 
           &tempSex, 
           &tempYear, 
           tempSnum, 
           tempCourse) == 5) {
           	
        if (!isDuplicate(tempSnum)) {
            //Add Student to Local if not Duplicate
            strcpy(students[studentCount].fullName, tempFullName);
            students[studentCount].sex = tempSex;
            students[studentCount].year = tempYear;
            strcpy(students[studentCount].snum, tempSnum);
            strcpy(students[studentCount].course, tempCourse);
            studentCount++;
        }
        
    }

	//Close File
    fclose(file);
    printf("*Previous Records Loaded*\n\n");
}

//QuickSort Function for Sorting by Year and Course
void quickSort(int low, int high) {
	
	//QuickSort Algorithm
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

//Partition Function for QuickSort
int partition(int low, int high) {
    struct Student pivot = students[high];
    int i = low - 1, j;

    for (j = low; j < high; j++) {
    	//If Current Record's Year is Less than or Equal to Pivot, Swap
        if (students[j].year < pivot.year ||
            (students[j].year == pivot.year && strcmp(students[j].course, pivot.course) < 0)) {
            i++;
            swap(&students[i], &students[j]);
        }
    }
    swap(&students[i + 1], &students[high]);
    return i + 1;
}

//Swap Function for QuickSort
void swap(struct Student* a, struct Student* b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

//Check if Student Number is Unique Function
int isDuplicate(char snum[]) {
	int i;
    for (i = 0; i < studentCount; i++) {
        if (strcmp(students[i].snum, snum) == 0) {
            return 1;
        }
    }
    return 0;
}

//Check if Student Number is Valid Function
int isValidStudentNum(char snum[]) {
    int i;
    int length = strlen(snum);

    //Check Length = 10
    if (length != 10) {
        return 0; //Invalid length
    }

    //Check Each Character is Digit and has Hyphen
    for (i = 0; i < length; i++) {
        if (!isdigit(snum[i]) && snum[i] != '-') {
            return 0; //Invalid Character
        }
    }

    return 1; //Valid
}

//Check if Sex is Valid Function
int isValidSex(char sex) {
    return (sex == 'M' || sex == 'F');
}

//Check if Year is Valid Function
int isValidYear(int year) {
    return (year >= 1 && year <= 5);
}
