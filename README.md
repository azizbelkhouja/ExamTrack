# ExamTrack - Student Exam Management System

[![Run on Repl.it](https://replit.com/badge/github/azizbelkhouja/ExamTrack)](https://replit.com/github/azizbelkhouja/ExamTrack)


ExamTrack is a lightweight C-based console application designed to help students manage and organize their exams. With ExamTrack, students can easily add exam details, track grades, calculate total earned credits, and view their average grade (media degli esami). The system also records the date each exam is added, providing a comprehensive overview of academic progress over time.

## Features

- **Add Exams**: Input the exam name, grade (18-30), credits, and automatically store the date of entry.
- **View Total Credits**: Calculate and display the total credits earned across all exams.
- **Calculate Average Grade**: Compute the weighted average grade based on the credits of each exam.
- **List All Exams**: Display a detailed list of all exams with their names, grades, credits, and dates.

## Getting Started

### Prerequisites

To compile and run ExamTrack, you need a C compiler. For example, you can use GCC (GNU Compiler Collection):

- **Linux/MacOS**: GCC is often pre-installed. You can check by running `gcc --version` in the terminal.
- **Windows**: You can install GCC as part of MinGW (Minimalist GNU for Windows) or use an IDE like Code::Blocks that includes a compiler.

### Installation

1. **Clone the repository**:
    ```bash
    git clone https://github.com/azizbelkhouja/ExamTrack.git
    cd ExamTrack
    ```

2. **Compile the program**:
    ```bash
    gcc -o main main.c
    ```

3. **Run the program**:
    ```bash
    ./main
    ```

## Usage

Once you run ExamTrack, a menu will appear with the following options:

1. **Add Exam**: Enter the exam name, grade, and credits. The program will also record the date of entry.
2. **View Total Credits**: Displays the sum of all credits earned from your exams.
3. **Calculate Average Grade**: Computes and displays the weighted average grade (media degli esami).
4. **Show All Exams**: Lists all exams along with their names, grades, credits, and the dates they were added.
5. **Exit**: Closes the application.
