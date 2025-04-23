#include <stdio.h>

int main(void){
    int height = 7;
    int width = 5;

    printf("Rectangle: Height: %d || Width: %d\n", height, width);
    printf("Perimeter of the rectangle: %d\n", 2 * (height + width));
    printf("Area of the rectangle: %d\n", (height * width));
    
    return 0;
}