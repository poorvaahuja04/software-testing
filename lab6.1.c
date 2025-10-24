#include <stdio.h>
int main() {
    int d, m, y;
    printf("Enter day month year: ");
    scanf("%d %d %d", &d, &m, &y);
    int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    //leap year
    if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
        daysInMonth[2] = 29;
    // validate
    if (y < 1900 || y > 2058 || m < 1 || m > 12 || d < 1 || d > daysInMonth[m]) {
        printf("Invalid date\n");
        return 0;
    }
    // Zeller’s Congruence
    if (m < 3) { m += 12; y--; }
    int k = y % 100, j = y / 100;
    int h = (d + (13*(m+1))/5 + k + k/4 + j/4 + 5*j) % 7;
    char *days[] = {"Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday"};
    printf("%s\n", days[h]);
    return 0;
}
