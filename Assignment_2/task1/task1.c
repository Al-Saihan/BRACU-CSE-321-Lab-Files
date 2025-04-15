#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int a = 0;
int b = 1;
int total_numbers, total_searches;

void *fibonacci_sequence(void *nums)
{
    int *array = (int *)nums;

    array[0] = a;
    array[1] = b;
    printf("a[0] = %d\n", array[0]);
    printf("a[1] = %d\n", array[1]);

    for (int i = 2; i < total_numbers; i++)
    {
        array[i] = array[i - 1] + array[i - 2];
        printf("a[%d] = %d\n", i, array[i]);
    }
}

void *fibonacci_search(void *nums)
{
    int *array = (int *)nums;

    int s;

    for (int i = 1; i < total_searches; i++)
    {
        printf("Enter Search %d: ", i);
        scanf("%d", &s);
        printf("Result of search #%d = ", i);
        if ((s >= total_numbers) || (s < 0))
        {
            printf("-1\n");
        }
        else
        {
            printf("%d\n", array[s]);
        }
    }
}

int main(void)
{
    pthread_t thread1, thread2;

    printf("Enter the term of fibonacci sequence: \n");
    scanf("%d", &total_numbers); //

    printf("How many numbers you are willing to search?: \n");
    scanf("%d", &total_searches);

    total_numbers++;
    total_searches++;

    int *numbers = malloc(total_numbers * sizeof(int));

    pthread_create(&thread1, NULL, fibonacci_sequence, (void *)numbers);
    pthread_join(thread1, NULL);

    pthread_create(&thread2, NULL, fibonacci_search, (void *)numbers);
    pthread_join(thread2, NULL);
}
