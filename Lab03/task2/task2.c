#include <stdio.h>

int main(void){
    int a;
    int b;
    int c;

    printf("Enter 3 angles, followed by spaces: ");

    scanf("%d %d %d", &a, &b, &c);
    printf("\n");

    if ((a+b+c) == 180){
        printf("A triangle can be formed with the given angles!\n");
    }
    else {
        printf("A triangle can NOT be formed with the given angles!\n");
    }

    return 0;
}