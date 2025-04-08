#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char buffer[100] = "Random Text";

    int file = open(strcat(argv[1], ".txt"), O_CREAT | O_RDWR | O_TRUNC, 0666);

    printf("\nA new file has been opened, with the name: %s\n\n", argv[1]);
    printf("Start writing anything, to write in to the file!\n\nWrite '-1' to stop the writing process!\n\n");
    while (1)
    {
        if (strcmp("-1\n", buffer) == 0)
        {
            printf("\n---Exiting Program---\n\n");
            break;
        }

        memset(buffer, '\0', sizeof(buffer));
        read(0, buffer, 100);
        write(file, buffer, strlen(buffer));
    }
}