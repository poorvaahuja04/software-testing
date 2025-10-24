#include<stdio.h>
#include<limits.h>
void Minimum();
int main(){
    Minimum();
    return 0;
}
void Minimum(){
    int array[100];
    int Number;
    int i;
    int tmpData;
    int Minimum = INT_MAX;
    printf("Enter the size of the array: ");
    scanf("%d", &Number);
    for(i=0; i<Number; i++){
        printf("Enter A[%d]=", i+1);
        scanf("%d", &tmpData);
        tmpData = (tmpData < 0) ? -tmpData : tmpData;
        array[i] = tmpData;
    }
    i=1;
    while(i < Number-1){
        if(Minimum > array[i]){
            Minimum = array[i];
        }
        i++;
    }
    printf("Minimum element is: %d", Minimum);
    getchar();
}