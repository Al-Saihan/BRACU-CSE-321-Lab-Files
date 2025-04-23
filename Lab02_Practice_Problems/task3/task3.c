#include <stdio.h>

int main(void){
    int radius;
    float PI = 3.14159;

    printf("Insert the radius of the Circle: ");
    scanf("%d", &radius);

    printf("\nCircle: Radius: %d || Diameter: %d\n", radius, 2 * radius);
    printf("Perimeter of the Circle: %f\n", 2 * (PI * radius));
    printf("Area of the Circle: %f\n", (PI * (radius * radius)));

    return 0;
}