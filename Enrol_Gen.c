#include<stdio.h>
#include<string.h>
typedef struct{
    int code;
    char name[50];
} Program;
typedef struct {
    int code;
    char name[50];
} Branch;
// function to check if file exists
int fileExists(const char *filename){
    FILE *file = fopen(filename, "r");
    if(file){
        fclose(file);
        return 1;
    }
    return 0;
}
int main(){
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
    if(fileExists(filename)){
        printf("File '%s' already exists. Overwrite? (y/n): ", filename);
        scanf(" %c", &choice);
        if(choice != 'y' && choice != 'Y'){
            printf("Operation cancelled. File not overwritten.\n");
            return 0;
        }
    }
    FILE *fp = fopen(filename, "w");
    if(!fp){
        printf("Error: Could not create file. \n");
        return 1;
    }
    fprintf(fp, "Year,ProgramCode,ProgramName,BranchCode,BranchName,RollNumber\n"); 
    int combinations; 
    printf("Enter number of Program_Branch combinations to generate: "); 
    scanf("%d", &combinations); 
    for (int c = 1; c <= combinations; c++) { 
        int year, progChoice, branchChoice, totalStudents; 
        printf("\n--- Combination %d ---\n", c); 
        printf("Enter Year of Admission (YYYY): "); 
        scanf("%d", &year); 
        printf("\nSelect Program:\n"); 
        for (int j = 0; j < numPrograms; j++) { 
            printf("%02d - %s\n", programs[j].code, programs[j].name); 
        } 
        printf("Enter Program Code: "); 
        scanf("%d", &progChoice); 
        printf("\nSelect Branch:\n"); 
        for (int j = 0; j < numBranches; j++) { 
            printf("%02d - %s\n", branches[j].code, branches[j].name); 
        } 
        printf("Enter Branch Code: "); 
        scanf("%d", &branchChoice); 
        printf("Enter Total Number of Students: "); 
        scanf("%d", &totalStudents); 
        printf("\nGenerated Roll Numbers for %s - %s:\n", 
            programs[progChoice - 1].name, branches[branchChoice -1].name); 
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