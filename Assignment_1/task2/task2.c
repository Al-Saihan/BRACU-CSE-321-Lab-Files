#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t a, b;

    a = fork();

    if (a < 0)
    {
        printf("Fork [Parent/Child] Failed!\n");
    }
    else if (a == 0)
    {
        b = fork();
        if (b < 0)
        {
            printf("Fork [Child/Grandchild] Failed\n");
        }
        else if (b == 0)
        {
            printf("I am grandchild\n");
        }
        else
        {
            wait(NULL);
            printf("I am child\n");
        }
    }
    else
    {
        wait(NULL);
        printf("I am parent\n");
    }
}