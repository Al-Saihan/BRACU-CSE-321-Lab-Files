#include <stdio.h>


float diameter(float rad){
    float d = rad * 2;
    return d;
}

float circumference(float rad){
    float c = 2 * 3.14159 * rad;
    return c;
}

float area(float rad){
    float a = 3.14159 * rad * rad;
    return a;
}

int main(void){
    float radius;
    printf("Insert the radius of a circle: ");
    scanf("%f", &radius);
    printf("\n%f\n", diameter(radius));
    printf("%f\n", circumference(radius));
    printf("%f\n", area(radius));
}