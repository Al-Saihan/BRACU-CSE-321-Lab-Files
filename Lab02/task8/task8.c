#include <stdio.h>

int main(void){
    char holder;

    printf("Insert a Character: ");
    scanf("%c", &holder);
    printf("\n\n");
    
    printf("The ASCII value of the Character %c is %d\n", holder, holder);

    return 0;
}