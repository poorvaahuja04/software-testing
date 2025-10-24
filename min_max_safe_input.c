#include <stdio.h>
#include <float.h>
void MinMax();
int main() {
    MinMax();
    return 0;
}
void MinMax() {
    double array[100];
    double min = DBL_MAX, max = -DBL_MAX;
    int Number;
    int i;
    double tmpData;
    printf("Enter the size of the array (1-100): ");
    while (scanf("%d", &Number) != 1 || Number <= 0 || Number > 100) {
        printf("Invalid size! Enter a whole number between 1 and 100: ");
        while (getchar() != '\n');
    }
    for (i = 0; i < Number; i++) {
        printf("Enter A[%d]: ", i + 1);
        while(1){
            char term;
            int result = scanf("%lf%c", &tmpData, &term);
            if (result == 2 && term == '\n') {
                break;
            }
            else {
                printf("Invalid input! Enter a real number: ");
            }
        }
        array[i] = tmpData;
        if (tmpData < min){
            min = tmpData;
        }
        if (tmpData > max){
            max = tmpData;
        }
    }
    printf("Minimum value: %.6lf\n", min);
    printf("Maximum value: %.6lf\n", max);
}