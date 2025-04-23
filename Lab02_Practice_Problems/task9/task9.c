#include <stdio.h>
#include <string.h>

int main(void){
    char s1[] = "Al-";
    char s2[] = "Saihan";

    strcat(s1,s2);

    printf("%s\n", s1);

    return 0;
}