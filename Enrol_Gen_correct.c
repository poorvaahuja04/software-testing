#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    int code;
    char name[50];
} Program;

typedef struct {
    int code;
    char name[50];
} Branch;

// function to check if file exists
int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// function to get current year
int getCurrentYear() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

// function to check if combination already used
int combinationExists(int used[][2], int usedCount, int progCode, int branchCode) {
    for (int i = 0; i < usedCount; i++) {
        if (used[i][0] == progCode && used[i][1] == branchCode) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Program programs[] = {
        {1, "B.Tech"},
        {2, "M.Tech"},
        {3, "Ph.D"}
    };
    int numPrograms = sizeof(programs) / sizeof(programs[0]);

    Branch branches[] = {
        {1, "CSE"},
        {2, "IT"},
        {3, "ECE"},
        {4, "MAE"},
        {5, "AI & DS"}
    };
    int numBranches = sizeof(branches) / sizeof(branches[0]);

    char filename[] = "IGDTUW_RollNumbers.csv";
    char choice;

    // Check if file exists
    if (fileExists(filename)) {
        printf("File '%s' already exists. Overwrite? (y/n): ", filename);
        scanf(" %c", &choice);
        if (choice != 'y' && choice != 'Y') {
            printf("Operation cancelled. File not overwritten.\n");
            return 0;
        }
    }

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Could not create file.\n");
        return 1;
    }

    fprintf(fp, "Year,ProgramCode,ProgramName,BranchCode,BranchName,RollNumber\n");

    int combinations;
    printf("Enter number of Program_Branch combinations to generate: ");
    scanf("%d", &combinations);

    int usedCombinations[100][2];
    int usedCount = 0;
    int currentYear = getCurrentYear();

    for (int c = 1; c <= combinations; c++) {
        int year, progChoice, branchChoice, totalStudents;

        printf("\n--- Combination %d ---\n", c);

        // Year validation
        do {
            printf("Enter Year of Admission (YYYY, <= %d): ", currentYear);
            scanf("%d", &year);
            if (year > currentYear) {
                printf("Invalid year. Please enter a year <= %d.\n", currentYear);
            }
        } while (year > currentYear);

        // Program selection with validation
        do {
            printf("\nSelect Program:\n");
            for (int j = 0; j < numPrograms; j++) {
                printf("%02d - %s\n", programs[j].code, programs[j].name);
            }
            printf("Enter Program Code: ");
            scanf("%d", &progChoice);
            if (progChoice < 1 || progChoice > numPrograms) {
                printf("Invalid Program Code. Try again.\n");
            }
        } while (progChoice < 1 || progChoice > numPrograms);

        // Branch selection with validation
        do {
            printf("\nSelect Branch:\n");
            for (int j = 0; j < numBranches; j++) {
                printf("%02d - %s\n", branches[j].code, branches[j].name);
            }
            printf("Enter Branch Code: ");
            scanf("%d", &branchChoice);
            if (branchChoice < 1 || branchChoice > numBranches) {
                printf("Invalid Branch Code. Try again.\n");
            }
        } while (branchChoice < 1 || branchChoice > numBranches);

        // Duplicate combination check
        if (combinationExists(usedCombinations, usedCount, progChoice, branchChoice)) {
            printf("This Program-Branch combination already has roll numbers generated. Skipping.\n");
            c--; // so that total combinations match
            continue;
        }

        // Save combination to used list
        usedCombinations[usedCount][0] = progChoice;
        usedCombinations[usedCount][1] = branchChoice;
        usedCount++;

        printf("Enter Total Number of Students: ");
        scanf("%d", &totalStudents);

        printf("\nGenerated Roll Numbers for %s - %s:\n",
               programs[progChoice - 1].name, branches[branchChoice - 1].name);

        for (int serial = 1; serial <= totalStudents; serial++) {
            printf("%04d%02d%02d%03d\n", year, progChoice, branchChoice, serial);
            fprintf(fp, "%d,%02d,%s,%02d,%s,%04d%02d%02d%03d\n",
                    year, progChoice, programs[progChoice - 1].name,
                    branchChoice, branches[branchChoice - 1].name,
                    year, progChoice, branchChoice, serial);
        }
    }

    fclose(fp);
    printf("\nRoll numbers saved to '%s'\n", filename);
    return 0;
}
