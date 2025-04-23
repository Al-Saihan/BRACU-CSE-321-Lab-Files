#include <stdio.h>

int main(void){
    int a;
    int b;
    int temp;

    printf("Insert a number A: ");
    scanf("%d", &a);
    printf("\n");
    printf("Insert a number B: ");
    scanf("%d", &b);
    printf("\n");

    printf("Now swapping A and B\n\n");

    temp = a;
    a = b;
    b = temp;
    
    printf("New value of A: %d\n", a);
    printf("New value of B: %d\n", b);

    return 0;
}