#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int a = 0;
int b = 1;

void *fibonacci_sequence(void *terms, void *arr)
{
    int *N = terms;

    return NULL;
}

void *fibonacci_search(void *searches)
{
    return NULL;
}

int main(void)
{
    pthread_t thread1, thread2;
    int total_terms, total_searches;
    void *numbers = malloc(sizeof(int) * 8);

    printf("Enter the term of fibonacci sequence: \n");
    scanf("%d\n", total_terms);

    printf("How many numbers you are willing to search?: \n");
    scanf("%d\n", total_searches);

    pthread_create(&thread1, NULL, fibonacci_sequence, (void *)total_terms, *numbers);
    pthread_join(thread1, NULL);

    pthread_create(&thread2, NULL, fibonacci_search, NULL);
    pthread_join(thread2, NULL);
}
