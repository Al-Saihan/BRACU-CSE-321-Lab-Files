#include <stdio.h>

int main(void){
    int n;

    printf("Insert a numerical value of N: ");
    scanf("%d", &n);

    int n_array[n];
    int temp;

    for (int i = 0; i < n; i++){
        printf("Insert Integer In Index %d: ", i);
        scanf("%d", &temp);
        printf("\n");

        n_array[i] = temp;
    }

    printf("Printing the array in reverse: [ ");

    for (int j = (n - 1); j >= 0; j--){
        printf("%d ", n_array[j]);
    }
    printf("]\n");

    return 0;
}