#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

struct shared
{
    char sel[100];
    int b;
};

int main()
{
    char selection[100];

    int sm_id;
    sm_id = shmget((key_t)4145, 1024, 0666 | IPC_CREAT);

    if (sm_id == -1)
    {
        perror("Shared Memory");
        return -1;
    }

    struct shared *bank = (struct shared *)shmat(sm_id, NULL, 0);

    int p;
    int fd[2];
    p = pipe(fd);

    if (p == -1)
    {
        perror("Pipe");
        return -2;
    }

    printf("Provide Your Input From Given Options:\n");
    printf("1. Type a to Add Money.\n");
    printf("2. Type w to Withdraw Money.\n");
    printf("3. Type c to Check Balance.\n\n");

    fgets(selection, sizeof(selection), stdin);
    strcpy(bank->sel, selection);
    bank->b = 1000;
    printf("\nYour selection: %s\n", selection);
    bank->sel[2] = '\0';

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork");
        return -3;
    }
    else if (pid > 0)
    {
        wait(NULL);
        close(fd[1]);
        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));
        printf("%s", buffer);
        close(fd[0]);
        shmctl(sm_id, IPC_RMID, NULL);
    }
    else
    {
        close(fd[0]);
        if (strcmp(bank->sel, "a\n") == 0)
        {
            int deposit;
            printf("Enter amount to be added:\n");
            scanf("%d", &deposit);

            if (deposit <= 0)
            {
                printf("Adding failed, Invalid amount.\n");
            }

            else
            {
                bank->b = bank->b + deposit;
                printf("Balanced added successfully!\n");
                printf("Updated balance after addition:\n");
                printf("%d\n", bank->b);
            }
        }

        else if (strcmp(bank->sel, "w\n") == 0)
        {
            int withdraw;
            printf("Enter amount to be withdrawn:\n");
            scanf("%d", &withdraw);

            if ((withdraw <= 0) || (withdraw > bank->b))
            {
                printf("Withdrawal failed\n");
            }

            else
            {
                bank->b = bank->b - withdraw;
                printf("Balance withdrawn successfully!\n");
                printf("Updated balance after withdrawal:\n");
                printf("%d\n", bank->b);
            }
        }

        else if (strcmp(bank->sel, "c\n") == 0)
        {
            printf("Your current balance is:\n");
            printf("%d\n", bank->b);
        }

        else
        {
            printf("Invalid Selection.\n");
        }

        char goodbye[100] = "Thank you for using!\n";
        write(fd[1], goodbye, strlen(goodbye) + 1);
        close(fd[1]);
    }
}