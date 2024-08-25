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

// Language strings
typedef struct {
    const char *menuTitle;
    const char *addExamOption;
    const char *viewCreditsOption;
    const char *calculateAverageOption;
    const char *showExamsOption;
    const char *sortOption;
    const char *filterGradeOption;
    const char *filterDateOption;
    const char *saveExitOption;
    const char *enterChoicePrompt;
    const char *examNamePrompt;
    const char *examGradePrompt;
    const char *examCreditsPrompt;
    const char *invalidGradeMessage;
    const char *totalCreditsMessage;
    const char *averageGradeMessage;
    const char *sortByPrompt;
    const char *sortByName;
    const char *sortByGrade;
    const char *sortByDate;
    const char *sortByCredits;
    const char *minGradePrompt;
    const char *maxGradePrompt;
    const char *filterByDatePrompt;
    const char *examsLoadedMessage;
    const char *examsSavedMessage;
    const char *memoryAllocationErrorMessage;
    const char *exitingMessage;
} LanguageStrings;

LanguageStrings english = {
    "Exam Management System",
    "1. Add a New Exam",
    "2. View Total Credits",
    "3. Calculate Average Grade",
    "4. Show All Exams",
    "5. Sort Exams",
    "6. Filter by Grade Range",
    "7. Filter by Date",
    "8. Save and Exit",
    "Enter your choice: ",
    "Enter exam name: ",
    "Enter grade (18-30): ",
    "Enter credits: ",
    "Invalid grade, please enter a value between 18 and 30.",
    "Total Credits: %d\n",
    "Average Grade: %.2f\n",
    "Sort by:\n1. Name\n2. Grade\n3. Date\n4. Credits\nEnter choice: ",
    "Name",
    "Grade",
    "Date",
    "Credits",
    "Enter minimum grade: ",
    "Enter maximum grade: ",
    "Enter date (dd-mm-yyyy): ",
    "Exams have been successfully loaded from '%s'.\n",
    "Exams have been successfully saved to '%s'.\n",
    "Memory allocation failed. Exiting program.\n",
    "Exiting...\n"
};

LanguageStrings italian = {
    "Sistema di Gestione degli Esami",
    "1. Aggiungi un Nuovo Esame",
    "2. Visualizza Crediti Totali",
    "3. Calcola la Media dei Voti",
    "4. Mostra Tutti gli Esami",
    "5. Ordina gli Esami",
    "6. Filtra per Intervallo di Voti",
    "7. Filtra per Data",
    "8. Salva e Esci",
    "Inserisci la tua scelta: ",
    "Inserisci il nome dell'esame: ",
    "Inserisci il voto (18-30): ",
    "Inserisci i crediti: ",
    "Voto non valido, inserisci un valore tra 18 e 30.",
    "Crediti Totali: %d\n",
    "Media dei Voti: %.2f\n",
    "Ordina per:\n1. Nome\n2. Voto\n3. Data\n4. Crediti\nInserisci la scelta: ",
    "Nome",
    "Voto",
    "Data",
    "Crediti",
    "Inserisci il voto minimo: ",
    "Inserisci il voto massimo: ",
    "Inserisci la data (gg-mm-aaaa): ",
    "Esami caricati con successo da '%s'.\n",
    "Esami salvati con successo in '%s'.\n",
    "Allocazione della memoria fallita. Uscita dal programma.\n",
    "Uscita...\n"
};

LanguageStrings *lang;

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
            printf("%s", lang->memoryAllocationErrorMessage);
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
    printf("%s\n", lang->menuTitle);
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
    printf(lang->examsSavedMessage, filename);
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
                printf("%s", lang->memoryAllocationErrorMessage);
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
    printf(lang->examsLoadedMessage, filename);
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
            printf("%s", lang->invalidGradeMessage);
            return;
    }
    displayExams();
}

void filterByGradeRange(int minGrade, int maxGrade) {
    printf(lang->menuTitle, minGrade, maxGrade);
    for (int i = 0; i < totalExams; i++) {
        if (exams[i].grade >= minGrade && exams[i].grade <= maxGrade) {
            printf("%d. %s - Grade: %d, Credits: %d, Date: %s\n", 
                   i + 1, exams[i].name, exams[i].grade, exams[i].credits, exams[i].date);
        }
    }
}

void filterByDate(char *date) {
    printf(lang->menuTitle, date);
    for (int i = 0; i < totalExams; i++) {
        if (strcmp(exams[i].date, date) == 0) {
            printf("%d. %s - Grade: %d, Credits: %d, Date: %s\n", 
                   i + 1, exams[i].name, exams[i].grade, exams[i].credits, exams[i].date);
        }
    }
}

int main(int argc, char *argv[]) {
    int choice, grade, credits, sortChoice, minGrade, maxGrade;
    char examName[50], filterDate[20], languageChoice[10];

    // Language selection
    printf("Select language (en/it): ");
    scanf("%s", languageChoice);
    lang = (strcmp(languageChoice, "it") == 0) ? &italian : &english;

    loadExamsFromFile();

    while (1) {
        printf("\n%s\n", lang->menuTitle);
        printf("%s\n", lang->addExamOption);
        printf("%s\n", lang->viewCreditsOption);
        printf("%s\n", lang->calculateAverageOption);
        printf("%s\n", lang->showExamsOption);
        printf("%s\n", lang->sortOption);
        printf("%s\n", lang->filterGradeOption);
        printf("%s\n", lang->filterDateOption);
        printf("%s\n", lang->saveExitOption);
        printf("%s", lang->enterChoicePrompt);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("%s", lang->examNamePrompt);
                scanf("%s", examName);
                printf("%s", lang->examGradePrompt);
                scanf("%d", &grade);
                while (grade < 18 || grade > 30) {
                    printf("%s", lang->invalidGradeMessage);
                    printf("%s", lang->examGradePrompt);
                    scanf("%d", &grade);
                }
                printf("%s", lang->examCreditsPrompt);
                scanf("%d", &credits);
                addExam(examName, grade, credits);
                break;
            case 2:
                printf(lang->totalCreditsMessage, calculateTotalCredits());
                break;
            case 3:
                printf(lang->averageGradeMessage, calculateAverageGrade());
                break;
            case 4:
                displayExams();
                break;
            case 5:
                printf("%s", lang->sortByPrompt);
                scanf("%d", &sortChoice);
                sortExams(sortChoice);
                break;
            case 6:
                printf("%s", lang->minGradePrompt);
                scanf("%d", &minGrade);
                printf("%s", lang->maxGradePrompt);
                scanf("%d", &maxGrade);
                if (minGrade > maxGrade) {
                    printf("Minimum grade cannot be higher than maximum grade. Please try again.\n");
                } else {
                    filterByGradeRange(minGrade, maxGrade);
                }
                break;
            case 7:
                printf("%s", lang->filterByDatePrompt);
                scanf("%s", filterDate);
                filterByDate(filterDate);
                break;
            case 8:
                saveExamsToFile();
                free(exams);
                printf("%s", lang->exitingMessage);
                return 0;
        }
    }
}
