#include <stdio.h>
#include <stdbool.h>
bool isLeap(int year);
int LastOfMonth(int month, int year);
bool ValidDate(int d, int m, int y);
void IncrementDate(int *d, int *m, int *y);
void PrintDate(int d, int m, int y);
void GetDate(int *d, int *m, int *y);
bool isLeap(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}
int LastOfMonth(int month, int year) {
    switch(month) {
        case 1: return 31;
        case 2: return (isLeap(year) ? 29 : 28);
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return -1;
    }
}
bool ValidDate(int d, int m, int y) {
    if (y < 1900 || y > 2100) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > LastOfMonth(m, y)) return false;
    return true;
}
void IncrementDate(int *d, int *m, int *y) {
    if (*d < LastOfMonth(*m, *y)) {
        (*d)++;
    } else {
        *d = 1;
        if (*m < 12) {
            (*m)++;
        } else {
            *m = 1;
            (*y)++;
        }
    }
}
void PrintDate(int d, int m, int y) {
    if (ValidDate(d, m, y))
        printf("Next Date: %02d/%02d/%d\n", d, m, y);
    else
        printf("Invalid Date!\n");
}
void GetDate(int *d, int *m, int *y) {
    printf("Enter Date (DD MM YYYY): ");
    scanf("%d %d %d", d, m, y);
}
int main() {
    int d, m, y;
    GetDate(&d, &m, &y);

    if (!ValidDate(d, m, y)) {
        printf("Invalid Input Date!\n");
        return 0;
    }

    IncrementDate(&d, &m, &y);
    PrintDate(d, m, y);
    return 0;
}
