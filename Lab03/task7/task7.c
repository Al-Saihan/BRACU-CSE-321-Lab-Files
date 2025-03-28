#include <stdio.h>

int main(void){
    FILE *file;
    char buffer[60];

    file = fopen("input.txt", "r");
    
    while (!feof(file)){
        fscanf(file, "%s", buffer);
        printf("%s\n", buffer);
    }
}