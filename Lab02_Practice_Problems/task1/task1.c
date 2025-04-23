#include <stdio.h>

int main(void){
    char name[10];
    char date_of_birth[10];
    char phone[11];

    printf("What is your First Name?: ");
    scanf("%s", name);
    printf("\n");

    printf("What is your date of birth? [Format: dd/mm/yy]: ");
    scanf("%s", date_of_birth);
    printf("\n");

    printf("What is your phone number?: ");
    scanf("%s", phone);
    printf("\n");

    printf("User Details:\n");
    printf("Name: %s\n", name);
    printf("Date Of Birth: %s\n", date_of_birth);
    printf("Mobile Number: %s\n", phone);

    return 0;
}