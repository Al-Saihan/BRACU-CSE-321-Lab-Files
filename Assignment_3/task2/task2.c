#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

struct msg
{
    long int type;
    char txt[6];
};

int main()
{
    struct msg message;
    char buffer[10];

    int ms_id = msgget(4145, 0666 | IPC_CREAT);

    printf("Please enter the workspace name:\n");
    int idx = read(0, buffer, sizeof(buffer));
    buffer[idx] = '\0';

    if (strcmp(buffer, "cse321\n") != 0)
    {
        printf("Invalid workspace name!\n");
        return -1;
    }

    strcpy(message.txt, buffer);
    message.type = 1;

    msgsnd(ms_id, &message, sizeof(message.txt), 0);
    printf("Workspace name sent to otp generator from log in: %s\n", message.txt);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork");
    }
    else if (pid == 0) // OTP Generator
    {
        msgrcv(ms_id, &message, sizeof(message.txt), 1, 0);
        printf("OTP generator received workspace name from log in: %s\n", message.txt);

        char otp[6];
        pid_t a = getpid();
        sprintf(otp, "%d", a);
        strcpy(message.txt, otp);
        message.type = 2; // going to parent(Log In)

        printf("OTP sent to log in from OTP generator: %s\n", message.txt);
        msgsnd(ms_id, &message, sizeof(message.txt), 0);

        message.type = 3; // going to child (Mail)

        msgsnd(ms_id, &message, sizeof(message.txt), 0);
        printf("OTP sent to mail from OTP generator: %s\n", message.txt);

        pid_t pid2 = fork();

        if (pid2 < 0)
        {
            perror("fork2");
        }
        else if (pid2 == 0) // Mail
        {
            msgrcv(ms_id, &message, sizeof(message.txt), 3, 0);
            printf("Mail recieved OTP from OTP generator: %s\n", message.txt);

            message.type = 4; // Going to Parent (Log-In)
            msgsnd(ms_id, &message, sizeof(message.txt), 0);
            printf("OTP sent to log in from mail: %s\n", message.txt);
            return 0;
        }
        else
        {
            wait(NULL);
        }
    }
    else // Coming back to Log-In Parent
    {
        wait(NULL);
        char c1[6];
        char c2[6];

        msgrcv(ms_id, &message, sizeof(message.txt), 2, 0);
        strcpy(c1, message.txt);
        printf("Log in recieved OTP from OTP generator: %s\n", message.txt);

        msgrcv(ms_id, &message, sizeof(message.txt), 4, 0);
        strcpy(c2, message.txt);
        printf("Log in received OTP from mail: %s\n", message.txt);

        if (strcmp(c1, c2) == 0)
        {
            printf("OTP Verified!\n");
        }
        else
        {
            printf("OTP Incorrect!\n");
        }

        msgctl(ms_id, IPC_RMID, NULL);
    }
}