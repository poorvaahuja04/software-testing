#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX_PROGRAMS 20
#define MAX_BRANCHES 20
typedef struct {
    int code;
    char name[50];
} Program;
typedef struct {
    int code;
    char name[50];
} Branch;
// ---------- File Handling ----------
int loadPrograms(Program programs[], const char *filename) {
    FILE *fp  = fopen(filename, "r");
    int count = 0;
    if(fp){
        while(fscanf(fp, "%d %[^\n]", &programs[count].code, programs[count].name) == 2){
            count++;
        }
        fclose(fp);
    }
    return count;
}
void saveProgram(const Program *p, const char *filename){
    FILE *fp = fopen(filename, "a");
    if(fp){
        fprintf(fp, "%d %s\n", p->code, p->name);
        fclose(fp);
    }
}
int loadBranches(Branch branches[], const char *filename) {
    FILE *fp = fopen(filename, "r");
    int count = 0;
    if (fp) {
        while (fscanf(fp, "%d %[^\n]", &branches[count].code, branches[count].name) == 2) {
            count++;
        }
        fclose(fp);
    }
    return count;
}
void saveBranch(const Branch *b, const char *filename) {
    FILE *fp = fopen(filename, "a");
    if (fp) {
        fprintf(fp, "%d %s\n", b->code, b->name);
        fclose(fp);
    }
}
int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}
int getCurrentYear() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}
int combinationExists(int used[][2], int usedCount, int progCode, int branchCode) {
    for (int i = 0; i < usedCount; i++) {
        if (used[i][0] == progCode && used[i][1] == branchCode) {
            return 1;
        }
    }
    return 0;
}
int programExists(Program programs[], int numPrograms, const char *name) {
    for (int i = 0; i < numPrograms; i++) {
        if (strcmp(programs[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}
int branchExists(Branch branches[], int numBranches, const char *name) {
    for (int i = 0; i < numBranches; i++) {
        if (strcmp(branches[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}
int main() {
    Program programs[MAX_PROGRAMS];
    int numPrograms = loadPrograms(programs, "programs.txt");
    Branch branches[MAX_BRANCHES];
    int numBranches = loadBranches(branches, "branches.txt");
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
    //Add new Programs
    printf("\nDo you want to add new Programs? (y/n): ");
    scanf(" %c", &choice);
    while (choice == 'y' || choice == 'Y') {
        if (numPrograms >= MAX_PROGRAMS) {
            printf("Maximum program limit reached.\n");
            break;
        }
        char progName[50];
        printf("Enter Program Name: ");
        scanf(" %[^\n]", progName);
        if (programExists(programs, numPrograms, progName)) {
            printf("Program already exists. Skipping.\n");
        } else {
            Program p;
            p.code = (numPrograms == 0) ? 1 : programs[numPrograms - 1].code + 1;
            strcpy(p.name, progName);
            programs[numPrograms++] = p;
            saveProgram(&p, "programs.txt");
            printf("Program added successfully.\n");
        }
        printf("Add another Program? (y/n): ");
        scanf(" %c", &choice);
    }
    //Add new Branches
    printf("\nDo you want to add new Branches? (y/n): ");
    scanf(" %c", &choice);
    while (choice == 'y' || choice == 'Y') {
        if (numBranches >= MAX_BRANCHES) {
            printf("Maximum branch limit reached.\n");
            break;
        }
        char branchName[50];
        printf("Enter Branch Name: ");
        scanf(" %[^\n]", branchName);

        if (branchExists(branches, numBranches, branchName)) {
            printf("Branch already exists. Skipping.\n");
        } else {
            Branch b;
            b.code = (numBranches == 0) ? 1 : branches[numBranches - 1].code + 1;
            strcpy(b.name, branchName);
            branches[numBranches++] = b;
            saveBranch(&b, "branches.txt");
            printf("Branch added successfully.\n");
        }
        printf("Add another Branch? (y/n): ");
        scanf(" %c", &choice);
    }
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Could not create file.\n");
        return 1;
    }
    fprintf(fp, "Year,ProgramCode,ProgramName,BranchCode,BranchName,RollNumber,StudentName\n");
    int combinations;
    printf("Enter number of Program_Branch combinations to generate: ");
    scanf("%d", &combinations);
    int usedCombinations[100][2];
    int usedCount = 0;
    int currentYear = getCurrentYear();
    for (int c = 1; c <= combinations; c++) {
        int year, progChoice, branchChoice, totalStudents;
        printf("\n--- Combination %d ---\n", c);
        // Year
        do {
            printf("Enter Year of Admission (YYYY, <= %d): ", currentYear);
            scanf("%d", &year);
        } while (year > currentYear);
        // Program
        do {
            printf("\nSelect Program:\n");
            for (int j = 0; j < numPrograms; j++) {
                printf("%02d - %s\n", programs[j].code, programs[j].name);
            }
            printf("Enter Program Code: ");
            scanf("%d", &progChoice);
        } while (progChoice < 1 || progChoice > numPrograms);
        // Branch
        do {
            printf("\nSelect Branch:\n");
            for (int j = 0; j < numBranches; j++) {
                printf("%02d - %s\n", branches[j].code, branches[j].name);
            }
            printf("Enter Branch Code: ");
            scanf("%d", &branchChoice);
        } while (branchChoice < 1 || branchChoice > numBranches);
        // Duplicate check
        if (combinationExists(usedCombinations, usedCount, progChoice, branchChoice)) {
            printf("This Program-Branch combination already used. Skipping.\n");
            c--;
            continue;
        }
        usedCombinations[usedCount][0] = progChoice;
        usedCombinations[usedCount][1] = branchChoice;
        usedCount++;
        // Students
        printf("Enter Total Number of Students: ");
        scanf("%d", &totalStudents);
        printf("\nGenerated Roll Numbers for %s - %s:\n",
               programs[progChoice - 1].name, branches[branchChoice - 1].name);
        for (int serial = 1; serial <= totalStudents; serial++) {
            char studentName[50];
            printf("Enter Name of Student %d: ", serial);
            scanf(" %[^\n]", studentName);

            printf("%04d%02d%02d%03d - %s\n",
                   year, progChoice, branchChoice, serial, studentName);

            fprintf(fp, "%d,%02d,%s,%02d,%s,%04d%02d%02d%03d,%s\n",
                    year, progChoice, programs[progChoice - 1].name,
                    branchChoice, branches[branchChoice - 1].name,
                    year, progChoice, branchChoice, serial, studentName);
        }
    }
    fclose(fp);
    printf("\nRoll numbers with student details saved to '%s'\n", filename);
    return 0;
}
