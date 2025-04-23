#include <stdio.h>

int main(void){
    int n;
    int sum = 0;

    printf("Insert a number N: ");
    scanf("%d" , &n);
    printf("\n");

    for (int i = 0; i <= n; i++){
        if (i % 2 == 0){
            sum = sum + i;
        }
    }
    printf("The sum of every numbers between 1 to N (%d) = %d\n", n, sum);
    return 0;
}