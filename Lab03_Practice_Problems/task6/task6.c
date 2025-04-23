#include <stdio.h>

int swap(int *a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


int main(void){
    int arr[6] = {1,2,3,4,5,6};
    int p1;
    int p2;

    printf("The Default Array Is 1 2 3 4 5 6\n");
    printf("Enter 2 positions to swap!\n");
    printf("Position 1: ");
    scanf("%d", &p1);
    printf("\nPosition 2: ");
    scanf("%d", &p2);

    swap(&arr[p1], &arr[p2]);

    printf("\nNew Array: ");

    for (int i = 0; i < 6; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");    
}