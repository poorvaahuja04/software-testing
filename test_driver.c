#include <stdio.h>
#include <stdbool.h>


bool isLeap(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int main() {
    printf("isLeap(2020): %d \n", isLeap(2020));
    printf("isLeap(1900): %d \n", isLeap(1900));
    printf("isLeap(2000): %d \n", isLeap(2000));
    printf("isLeap(2023): %d \n", isLeap(2023));
    return 0;
}
