#include <stdio.h>

int main(void){
    int seconds;

    printf("Enter an Integer to represent time in seconds: ");
    scanf("%d", &seconds);

    printf("Converting:\n");

    int minutes = seconds / 60;
    seconds = seconds % 60;

    int hours = minutes / 60;
    minutes = minutes % 60;

    printf("Hours:   %d\nMinutes: %d\nSeconds: %d\n", hours, minutes, seconds);

    return 0;
}