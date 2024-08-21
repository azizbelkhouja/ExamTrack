#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_EXAMS 100

typedef struct {
    char name[50];
    int grade;
    int credits;
    char date[20];
} Exam;

Exam exams[MAX_EXAMS];
int totalExams = 0;

void getCurrentDate(char *dateStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateStr, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void addExam(char *name, int grade, int credits) {
    if (totalExams < MAX_EXAMS) {
        strcpy(exams[totalExams].name, name);
        exams[totalExams].grade = grade;
        exams[totalExams].credits = credits;
        getCurrentDate(exams[totalExams].date);
        totalExams++;
    } else {
        printf("Cannot add more exams, maximum limit reached.\n");
    }
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

int main() {
    int choice;
    char examName[50];
    int grade, credits;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Exam\n");
        printf("2. View Total Credits\n");
        printf("3. Calculate Average Grade (Media degli esami)\n");
        printf("4. Show All Exams\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                if (totalExams >= MAX_EXAMS) {
                    printf("Max exams reached. Cannot add more.\n");
                } else {
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
                }
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
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
}
