#include <stdio.h>

int main(void){
    // Creating Initial Array Through The Usage Of N
    int n;

    printf("Enter Array [Filled with Digits] size: ");
    scanf("%d", &n);


    int digits[n];

    for (int i = 0; i < n; i++){
        digits[i] = i;
    }

    // Reversing The Array
    int temp;

    for (int i ; i < (n/2) ; i++){
        temp = digits[i];
        digits[i] = digits[n - 1 - i];
        digits[n - 1 - i] = temp;
    }

    // Printing The Reversed Array

    printf("[ ");

    for (int j = 0; j < n; j++){
        printf("%d ", digits[j]);
    }
    printf("]\n");

    return 0;
}