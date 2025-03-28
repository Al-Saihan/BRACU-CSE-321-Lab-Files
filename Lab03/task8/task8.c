#include <stdio.h>
#include <stdlib.h>


void printArray(int *arr, int size){
    for (int j = 0; j < size; j++){
        printf("%d ", arr[j]);
    }
}


int main(int argc, char *argv[]){
    int N = argc - 1;
    int array[N];

    for (int i = 1; i < argc; i++){
        array[i - 1] = atoi(argv[i]);
    }
    
    printf("Given Array: ");
    printArray(array, N);
    printf("\n");


    // Sorting Process -- Bubble Sort
    for (int y = 0; y < N-1; y++){
        for (int x = 0; x < N-1; x++){
            if (array[x] > array[x+1]){
                int temp = array[x];
                array[x] = array[x+1];
                array[x+1] = temp;
            }
        }
    }


    printf("Sorted Array: ");
    printArray(array, N);
    printf("\n");
}