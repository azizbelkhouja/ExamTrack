# ExamTrack - Exam Management System

[![Run on Repl.it](https://replit.com/badge/github/azizbelkhouja/ExamTrack)](https://replit.com/github/azizbelkhouja/ExamTrack)

## Overview

The **Exam Management System** is a simple C program designed to help students manage their exam records. It allows users to add new exams, view total credits, calculate the average grade, sort exams, and filter them by grade or date. The system supports both English and Italian languages, allowing for broader accessibility.

## Features

- **Multi-language Support**: Users can choose between English and Italian at the start of the program.
- **Add Exams**: Users can add new exams with details such as name, grade, credits, and the date of the exam.
- **View Total Credits**: The program calculates and displays the total number of credits accumulated by the user.
- **Calculate Average Grade**: The program computes and displays the weighted average grade based on the user's exams.
- **Sort Exams**: Users can sort their exams by name, grade, date, or credits.
- **Filter Exams**: Users can filter exams by a specific grade range or by date.
- **Save and Load Data**: The system saves exam data to a file and loads it upon startup.

## How to Use

### 1. Compile the Program

To compile the program, use the following command:

```bash
gcc -o maim main.c
```

### 2. Run the Program

After compilation, you can run the program with:

```bash
./main
```

### 3. Select Language

At the start, the program will prompt you to choose a language:

```bash
Select language (en/it): 
```

- Type `en` for English.
- Type `it` for Italian.

### 4. Menu Options

Once the language is selected, the main menu will be displayed:

```text
Exam Management System
1. Add a New Exam
2. View Total Credits
3. Calculate Average Grade
4. Show All Exams
5. Sort Exams
6. Filter by Grade Range
7. Filter by Date
8. Save and Exit
Enter your choice: 
```

Choose an option by entering the corresponding number.

#### 4.1 Add a New Exam

The program will prompt you to enter the exam details:

- **Name**: The name of the exam.
- **Grade**: The grade obtained in the exam (must be between 18 and 30).
- **Credits**: The number of credits the exam is worth.

#### 4.2 View Total Credits

Displays the total credits accumulated from all added exams.

#### 4.3 Calculate Average Grade

Calculates and displays the weighted average grade based on all exams.

#### 4.4 Show All Exams

Displays all the exams in the system with their details (name, grade, credits, date).

#### 4.5 Sort Exams

Sorts the exams based on the selected criteria:

- **1**: Name
- **2**: Grade
- **3**: Date
- **4**: Credits

#### 4.6 Filter by Grade Range

Filters exams within a specified grade range. The program will ask for the minimum and maximum grades to filter.

#### 4.7 Filter by Date

Filters exams that were taken on a specific date. Enter the date in `dd-mm-yyyy` format.

#### 4.8 Save and Exit

Saves all exams to `exams.txt` and exits the program.

## File Structure

- **exams.txt**: The file where all exam data is stored. It is loaded on program startup and updated when you save.

## Localization

The program supports two languages:

- **English** (Default)
- **Italian**

You can switch languages by restarting the program and selecting a different language at the prompt.

## Error Handling

- **Memory Allocation**: If the program fails to allocate memory, it will display an error message and exit.
- **Invalid Grade**: If an invalid grade is entered (outside the range of 18-30), the program will prompt the user to enter a valid grade.

## Future Enhancements

- **Improved Date Handling**: Support for different date formats and validation.
- **Enhanced Sorting and Filtering**: Additional options and more granular control over sorting and filtering criteria.
- **Additional Language Support**: Inclusion of more languages based on user demand.

## Contributing

Feel free to contribute to the project by submitting pull requests or opening issues. Contributions for bug fixes, new features, or additional language support are welcome.
