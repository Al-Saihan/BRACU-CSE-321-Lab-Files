#include <stdio.h>
#include <ctype.h>

int main(void){
    char x;

    printf("Enter a chracter: ");
    scanf("%c", &x);
    x = tolower(x);


    if (!isalpha(x)){
        printf("Invalid character, please insert an alphabet!\n");
        return -1;
    }
    else if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u'){
        printf("This character is a vowel!\n");
    }
    else{
        printf("This character is a consonant!\n");
    }


    
    return 0;
}