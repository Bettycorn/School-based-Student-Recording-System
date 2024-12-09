# School-based-Student-Recording-System

Psuedocode of the program
//Structure Declaration
- Declare Student Structure with Members: Full Name, Student Number, Sex, Year, and Course
- Declare Instance

//Main Function
- While (true)
- Display menu
- Input UserOpt according to menu
- Case 1: Add a student into the structure array
- Case 2: Display all records in the structure array
- Case 3: Display a specific record from the structure  array using a given Student Number.
- Case 4:Update a specific record from the structure array using a given Student Number.
- Case 5: Delete a student record from the structure array using a given Student Number.
- Case 6: Load data from file
- Case 7: Save all local student record data into a file
- Case 8: Exit
	- If UserOpt invalid
		- print error message

//Case 1: addStudent function
- If studentCount is equal or max (1000)
	- print error: Max student reached
	- Return to Menu
- Input student details (full name, sex, year, student number, & course) and Validate each input
- If not Valid
	- print appropriate message and input again
- If inputs are valid
- Increment student count variable by 1.
- Print “student added”
- Return to Menu



//Case 2: displayStudentRecords function
- Initialize character array currentCourse for course label that can hole 50 elements
- Sort records by Year Level & Course (Call quicksort function)
- Display features (full name, sex, and student number) per student until the last entry

//Case 3: displayRecord function
- Initialize character variable snum that holds 20 elements
- Input snum
- Find corresponding snum using loop
- If corresponding snum is found
	- Print structure members (full name, sex, year, snum, and course)
- If no snum corresponds
	- print not found message

//Case 4: updateRecord function
- Initialize character variable snum that holds 20 elements
- Input snum
- Find corresponding snum using loop
- If corresponding snum is found
	- input structure members (surname, sex, year, snum, and course)
- If no corresponding snum found
	- print not found message

//Case 5: deleteStudent function
- Initialize integer variables i, j, snum
- Input snum
- Find snum using a loop
- If snum is found
		- Shift records to the left
		- Decrement studentCount by 1
		- Print “Student Record Deleted
		- break

- If snum is not found
	- Print not found message

//Case 6: loadFromFile function
- Input filename
- Concatenate “.txt” to filename
- Open file in write mode
- If file returns NULL
	- Display error message
	- Return
- If studentCount < Max and Program reads 5 items from file
- If not duplicate
		- Increment studentCount by 1
- Add student locally
- Increment studentCount by 1
- Close File
- Print Success Message

//Case 7: saveToFile function
- Input filename
- Concatenate “.txt” to filename
- Open file in write mode
- If file returns NULL
	- Display error message
	- Return
- Print local data to file
- Close opened file
- Print Success message

//Case 8: Exit
- exit program


