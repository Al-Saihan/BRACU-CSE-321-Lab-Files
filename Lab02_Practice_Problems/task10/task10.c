#include <stdio.h>

struct student{
    char name[20];
    char id[10];
    char dep[5];
};

int main(void){
    struct student student1;

    printf("Nickname of the student: ");
    scanf("%s", student1.name);
    printf("\n");

    printf("ID of the student: ");
    scanf("%s", student1.id);
    printf("\n");

    printf("Department of the student: ");
    scanf("%s", student1.dep);
    printf("\n");

    printf("Student Information:\n%s [ID : %s] is a Student of %s Department.\n", student1.name, student1.id, student1.dep);
    
    return 0;
}