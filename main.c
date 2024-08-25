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
            printf("Memory allocation failed!\n");
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
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < totalExams; i++) {
        fprintf(file, "%s %d %d %s\n", exams[i].name, exams[i].grade, exams[i].credits, exams[i].date);
    }

    fclose(file);
    printf("Exams saved to %s.\n", filename);
}

void loadExamsFromFile() {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No previous exam data found.\n");
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
                printf("Memory allocation failed!\n");
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
    printf("Exams loaded from %s.\n", filename);
}

// Sorting comparison functions
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
            printf("Invalid choice for sorting.\n");
            return;
    }
    displayExams()
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

int main() {
    int choice, sortChoice;
    char examName[50];
    int grade, credits;
    int minGrade, maxGrade;
    char filterDate[20];

    loadExamsFromFile();
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Exam\n");
        printf("2. View Total Credits\n");
        printf("3. Calculate Average Grade (Media degli esami)\n");
        printf("4. Show All Exams\n");
        printf("5. Sort Exams\n");
        printf("6. Filter Exams by Grade Range\n");
        printf("7. Filter Exams by Date\n");
        printf("8. Save Exams and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter exam name: ");
                scanf("%s", examName);
                do {
                    printf("Enter grade (18-30): ");
                    scanf("%d", &grade);
                    if (grade < 18 || grade > 30) {
                        printf("Invalid grade, please enter a value between 18 and 30.\n");
                    }
                } while (grade < 18 || grade > 30);

                printf("Enter credits: ");
                scanf("%d", &credits);
                addExam(examName, grade, credits);
                break;
            case 2:
                printf("Total Credits: %d\n", calculateTotalCredits());
                break;
            case 3:
                printf("Average Grade (Media degli esami): %.2f\n", calculateAverageGrade());
                break;
            case 4:
                displayExams();
                break;
            case 5:
                printf("Sort by: 1. Name 2. Grade 3. Date 4. Credits\n");
                printf("Enter your choice: ");
                scanf("%d", &sortChoice);
                sortExams(sortChoice);
                break;
            case 6:
                printf("Enter minimum grade: ");
                scanf("%d", &minGrade);
                printf("Enter maximum grade: ");
                scanf("%d", &maxGrade);
                filterByGradeRange(minGrade, maxGrade);
                break;
            case 7:
                printf("Enter date (dd-mm-yyyy): ");
                scanf("%s", filterDate);
                filterByDate(filterDate);
                break;
            case 8:
                saveExamsToFile();
                free(exams);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}
