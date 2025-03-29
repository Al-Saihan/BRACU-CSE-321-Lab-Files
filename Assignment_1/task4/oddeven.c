#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int N = argc - 1;
    int array[N];

    // Inserting the numebrs in Int Array
    for (int i = 1; i < argc; i++)
    {
        array[i - 1] = atoi(argv[i]);
    }

    for (int j = 0; j < N; j++)
    {
        if (array[j] % 2 == 1)
        {
            printf("The number %d is Odd.\n", array[j]);
        }
        else
        {
            printf("The number %d is Even.\n", array[j]);
        }
    }
}