#include <stdio.h>

int main(void){
    int digits[10];

    for (int i = 0; i < 10; i++){
        digits[i] = i;
    }
    printf("An Array Containing All Decimal Digits:\n[");

    int temp;
    for (int j = 0; j < 9; j++){
        printf("%d ", digits[j]);
        temp = j;
    }

    printf("%d]\n" , digits[temp+1]);

    return 0;
}
