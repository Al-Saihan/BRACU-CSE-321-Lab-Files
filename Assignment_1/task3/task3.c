#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    pid_t a, b, c, p;
    p = getpid();
    char buffer[16];

    int temp = open("./temp.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
    printf("Please wait a while for the final output!\n");
    a = fork();
    b = fork();
    c = fork();

    write(temp, "+", 1);

    if (getpid() % 2 == 1)
    {
        write(temp, "+", 1);
        fork();
    }
    sleep(2);

    if (p == getpid())
    {
        lseek(temp, 0, SEEK_SET);
        int bytes = read(temp, buffer, sizeof(buffer));
        buffer[bytes] = '\0';
        printf("Total Processes: %d\n", strlen(buffer));
    }
}