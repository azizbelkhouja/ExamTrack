#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
    char name[50];
    int grade;
    int credits;
    char date[20];
} Exam;

Exam *exams = NULL;
int totalExams = 0;
int allocatedSize = 0;
const char *filename = "exams.txt";

void getCurrentDate(char *dateStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateStr, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void addExam(char *name, int grade, int credits) {
    if (totalExams == allocatedSize) {
        allocatedSize += 10;
        exams = realloc(exams, allocatedSize * sizeof(Exam));
        if (exams == NULL) {
            printf("Memory allocation failed. Exiting program.\n");
            exit(1);
        }
    }

    strcpy(exams[totalExams].name, name);
    exams[totalExams].grade = grade;
    exams[totalExams].credits = credits;
    getCurrentDate(exams[totalExams].date);
    totalExams++;
}

int calculateTotalCredits() {
    int totalCredits = 0;
    for (int i = 0; i < totalExams; i++) {
        totalCredits += exams[i].credits;
    }
    return totalCredits;
}

float calculateAverageGrade() {
    int totalCredits = 0;
    int weightedSum = 0;

    for (int i = 0; i < totalExams; i++) {
        weightedSum += exams[i].grade * exams[i].credits;
        totalCredits += exams[i].credits;
    }

    return totalCredits > 0 ? (float)weightedSum / totalCredits : 0.0;
}

void displayExams() {
    printf("List of Exams:\n");
    for (int i = 0; i < totalExams; i++) {
        printf("%d. %s - Grade: %d, Credits: %d, Date: %s\n", 
               i + 1, exams[i].name, exams[i].grade, exams[i].credits, exams[i].date);
    }
}

void saveExamsToFile() {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < totalExams; i++) {
        fprintf(file, "%s %d %d %s\n", exams[i].name, exams[i].grade, exams[i].credits, exams[i].date);
    }

    fclose(file);
    printf("Exams have been successfully saved to '%s'.\n", filename);
}

void loadExamsFromFile() {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No saved exams found. Starting fresh.\n");
        return;
    }

    char name[50];
    int grade, credits;
    char date[20];

    while (fscanf(file, "%s %d %d %s", name, &grade, &credits, date) == 4) {
        if (totalExams == allocatedSize) {
            allocatedSize += 10;
            exams = realloc(exams, allocatedSize * sizeof(Exam));
            if (exams == NULL) {
                printf("Memory allocation failed. Exiting program.\n");
                fclose(file);
                exit(1);
            }
        }
        strcpy(exams[totalExams].name, name);
        exams[totalExams].grade = grade;
        exams[totalExams].credits = credits;
        strcpy(exams[totalExams].date, date);
        totalExams++;
    }

    fclose(file);
    printf("Exams have been successfully loaded from '%s'.\n", filename);
}

int compareByName(const void *a, const void *b) {
    return strcmp(((Exam*)a)->name, ((Exam*)b)->name);
}

int compareByGrade(const void *a, const void *b) {
    return ((Exam*)b)->grade - ((Exam*)a)->grade;
}

int compareByDate(const void *a, const void *b) {
    return strcmp(((Exam*)a)->date, ((Exam*)b)->date);
}

int compareByCredits(const void *a, const void *b) {
    return ((Exam*)b)->credits - ((Exam*)a)->credits;
}

void sortExams(int choice) {
    switch (choice) {
        case 1:
            qsort(exams, totalExams, sizeof(Exam), compareByName);
            break;
        case 2:
            qsort(exams, totalExams, sizeof(Exam), compareByGrade);
            break;
        case 3:
            qsort(exams, totalExams, sizeof(Exam), compareByDate);
            break;
        case 4:
            qsort(exams, totalExams, sizeof(Exam), compareByCredits);
            break;
        default:
            printf("Invalid sorting option. Please try again.\n");
            return;
    }
    displayExams();
}

void filterByGradeRange(int minGrade, int maxGrade) {
    printf("Exams with grades between %d and %d:\n", minGrade, maxGrade);
    for (int i = 0; i < totalExams; i++) {
        if (exams[i].grade >= minGrade && exams[i].grade <= maxGrade) {
            printf("%d. %s - Grade: %d, Credits: %d, Date: %s\n", 
                   i + 1, exams[i].name, exams[i].grade, exams[i].credits, exams[i].date);
        }
    }
}

void filterByDate(char *date) {
    printf("Exams on %s:\n", date);
    for (int i = 0; i < totalExams; i++) {
        if (strcmp(exams[i].date, date) == 0) {
            printf("%d. %s - Grade: %d, Credits: %d, Date: %s\n", 
                   i + 1, exams[i].name, exams[i].grade, exams[i].credits, exams[i].date);
        }
    }
}

int getValidInt(const char *prompt, int min, int max) {
    int value;
    char input[50];
    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        if (sscanf(input, "%d", &value) == 1 && value >= min && value <= max) {
            return value;
        }
        printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
    }
}

void getValidString(const char *prompt, char *output, int maxLength) {
    char input[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input. Please try again.\n");
            continue;
        }
        input[strcspn(input, "\n")] = 0;
        if (strlen(input) > 0 && strlen(input) < maxLength) {
            strcpy(output, input);
            return;
        }
        printf("Invalid input. Please enter a non-empty string shorter than %d characters.\n", maxLength);
    }
}

void handleCommandLineArguments(int argc, char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "add") == 0 && argc == 5) {
            char *examName = argv[2];
            int grade = atoi(argv[3]);
            int credits = atoi(argv[4]);

            if (grade < 18 || grade > 30 || credits <= 0) {
                printf("Invalid grade or credits. Grade should be between 18 and 30. Credits should be positive.\n");
            } else {
                addExam(examName, grade, credits);
                saveExamsToFile();
                printf("Exam added via command-line.\n");
            }
        } else if (strcmp(argv[1], "stats") == 0) {
            printf("Total Credits: %d\n", calculateTotalCredits());
            printf("Average Grade: %.2f\n", calculateAverageGrade());
        } else {
            printf("Unknown command or incorrect arguments. Use 'add <name> <grade> <credits>' to add an exam or 'stats' to view stats.\n");
        }
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    int choice, sortChoice;
    char examName[50];
    int grade, credits;
    int minGrade, maxGrade;
    char filterDate[20];

    loadExamsFromFile();
    handleCommandLineArguments(argc, argv);

    while (1) {
        printf("\n--- Exam Management System ---\n");
        printf("1. Add a New Exam\n");
        printf("2. View Total Credits\n");
        printf("3. Calculate Average Grade\n");
        printf("4. Show All Exams\n");
        printf("5. Sort Exams\n");
        printf("6. Filter by Grade Range\n");
        printf("7. Filter by Date\n");
        printf("8. Save and Exit\n");
        printf("Enter your choice: ");
        choice = getValidInt("", 1, 8);

        switch (choice) {
            case 1:
                getValidString("Enter exam name: ", examName, sizeof(examName));
                grade = getValidInt("Enter grade (18-30): ", 18, 30);
                credits = getValidInt("Enter credits: ", 1, 30);
                addExam(examName, grade, credits);
                break;
            case 2:
                printf("Total Credits: %d\n", calculateTotalCredits());
                break;
            case 3:
                printf("Average Grade: %.2f\n", calculateAverageGrade());
                break;
            case 4:
                displayExams();
                break;
            case 5:
                printf("Sort by:\n1. Name\n2. Grade\n3. Date\n4. Credits\nEnter choice: ");
                sortChoice = getValidInt("", 1, 4);
                sortExams(sortChoice);
                break;
            case 6:
                minGrade = getValidInt("Enter minimum grade: ", 18, 30);
                maxGrade = getValidInt("Enter maximum grade: ", 18, 30);
                if (minGrade > maxGrade) {
                    printf("Minimum grade cannot be higher than maximum grade. Please try again.\n");
                } else {
                    filterByGradeRange(minGrade, maxGrade);
                }
                break;
            case 7:
                getValidString("Enter date (dd-mm-yyyy): ", filterDate, sizeof(filterDate));
                filterByDate(filterDate);
                break;
            case 8:
                saveExamsToFile();
                free(exams);
                printf("Exiting...\n");
                return 0;
        }
    }
}
