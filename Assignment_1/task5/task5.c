#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    pid_t a, b, c, d;
    printf("Parent process ID: 0\n");
    a = fork();

    if (a < 0)
    {
        printf("Fork Failed\n");
    }
    else if (a == 0)
    {
        a = getpid();
        // Edit here: Declare a new variable z above, remove parent process print
        // add z = getppid(), print later down below

        b = fork();
        if (b < 0)
        {
            printf("Fork failed\n");
        }
        else if (b > 0)
        {
            c = fork();
            if (c < 0)
            {
                printf("Fork Failed!\n");
            }
            else if (c > 0)
            {
                d = fork();
                if (d < 0)
                {
                    printf("Fork Failed!\n");
                }
                else if (d > 0)
                {
                    printf("Child process ID: %d\n", a);
                    printf("Grand Child process ID: %d\n", b);
                    printf("Grand Child process ID: %d\n", c);
                    printf("Grand Child process ID: %d\n", d);
                }
            }
        }
    }
}