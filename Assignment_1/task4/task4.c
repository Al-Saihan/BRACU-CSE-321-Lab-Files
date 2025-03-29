#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t a;

    a = fork();

    if (a < 0)
    {
        printf("Execution/Fork Failure");
        return -1;
    }
    else if (a == 0)
    {
        execv("./sort", argv);
    }
    else
    {
        wait(NULL);
        execv("./oddeven", argv);
    }
}