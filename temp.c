#include <stdio.h>
#include <limits.h>
void Minimum();
int main(){
    Minimum();
    return 0;
}
void Minimum(){
    int array[100];
    int min = INT_MAX;
    int Number;
    int i;
    int tmpData;
    printf("Enter the size of the array (1-100): ");
    scanf("%d", &Number);
    for (i = 0; i < Number; i++) {
        printf("Enter A[%d]=", i + 1);
        while(1){
            char term;
            int result = scanf("%d%c", &tmpData, &term);
            if (result == 2 && term == '\n'){
                break;
            }
            else printf("Invalid input! Enter an integer: ");
            while (getchar() != '\n');
        }
        array[i] = tmpData;
    }
    i=0;
    while(i < Number){
        if(min > array[i]){
            min = array[i];
        }
        i++;
    }
    printf("Minimum element is: %d\n", min);
}