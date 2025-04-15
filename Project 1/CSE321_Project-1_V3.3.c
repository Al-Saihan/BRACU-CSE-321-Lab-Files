#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

// ! == == == == == == GLOBAL VARIABLES == == == == == ==

// * Shell Input Handling
char command[256];
char *command_arguments[20];
int command_arg_count = 0;

// * Semicolon and && Parsing
char *f_commands[20];
int f_commands_count = 0;
char *p_commands[20];
int p_commands_count = 0;
int status = 0;

// * History
#define MAX_HISTORY 20
char *history[MAX_HISTORY];
int history_count = 0;
volatile sig_atomic_t current_foreground_pid = -1;

// ! == == == == == == FUNCTION DECLARATIONS == == == == == ==

// * Command Parsing and Execution -- Al Saihan Tajvi
void split_command_by_semicolon(char *command);
void split_command_by_AND_operator(char *command);
void process_command_input(char *command);
int execute_command();

// * Redirection, Piping and Built-in handling -- Farhan Zarif
void handle_redirection(char **args);
void execute_pipe();
int execute_built_in_command();

// * New Functions: History & Signals - Sadik Mina Dweep
void add_to_history(const char *cmd);
void print_history();
void handle_sigint(int sig);

// * Additional Functions
void print_details();

// ! == == == == == == MAIN FUNCTION == == == == == ==

int main()
{
    printf("Hello World! Welcome to the UNIX Shell!\n\n");

    printf("Type 'ABOUT' to check program details, features, and contributions.\n");
    printf("Type 'EXIT' to close the program.\n\n");
    printf("NOTE: Please seperate each part of your command with a space!\n\n");

    signal(SIGINT, handle_sigint);

    while (1)
    {
        printf("UNIX Shell > ");
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            printf("Error reading command, terminating the process.\n");
            return 1;
        }

        add_to_history(command);

        if (strcmp(command, "EXIT\n") == 0)
        {
            printf("Thank You for using our shell! Closing the program!\n");
            break;
        }

        if (strcmp(command, "history\n") == 0)
        {
            print_history();
            continue;
        }

        if (strcmp(command, "ABOUT\n") == 0)
        {
            print_details();
            continue;
        }

        split_command_by_semicolon(command);
        printf("\n");
    }

    for (int i = 0; i < history_count; i++)
    {
        free(history[i]);
    }

    return 0;
}

// ! == == == == == == HELPER FUNCTIONS == == == == == ==

void split_command_by_semicolon(char *command)
{
    char *token;
    f_commands_count = 0;
    token = strtok(command, ";");

    while (token != NULL && f_commands_count < 20)
    {
        f_commands[f_commands_count++] = token;
        token = strtok(NULL, ";");
    }

    f_commands[f_commands_count] = NULL;

    for (int i = 0; i < f_commands_count; i++)
    {
        split_command_by_AND_operator(f_commands[i]);
    }
}

// ! - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void split_command_by_AND_operator(char *command)
{
    char *token;
    p_commands_count = 0;
    token = strtok(command, "&&");

    while (token != NULL && p_commands_count < 20)
    {
        p_commands[p_commands_count++] = token;
        token = strtok(NULL, "&&");
    }

    p_commands[p_commands_count] = NULL;

    for (int i = 0; i < p_commands_count; i++)
    {
        if (i == 0 || status == 0)
        {
            process_command_input(p_commands[i]);
        }
        else
        {
            break;
        }
    }
}

// ! - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void process_command_input(char *command)
{
    char *token;
    command_arg_count = 0;
    token = strtok(command, " \n");

    while (token != NULL && command_arg_count < 20)
    {
        command_arguments[command_arg_count++] = token;
        token = strtok(NULL, " \n");
    }

    command_arguments[command_arg_count] = NULL;

    int built_in_executed = execute_built_in_command();

    if (built_in_executed)
    {
        status = 0;
        return;
    }

    int has_pipe = 0;
    for (int i = 0; command_arguments[i] != NULL; i++)
    {
        if (strcmp(command_arguments[i], "|") == 0)
        {
            has_pipe = 1;
            break;
        }
    }

    if (has_pipe)
    {
        execute_pipe();
    }
    else
    {
        execute_command();
    }
}

// ! - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int execute_command()
{
    if (command_arg_count == 0)
    {
        status = 2;
        return 2;
    }

    pid_t pid;
    status = 0;
    pid = fork();

    if (pid < 0)
    {
        printf("Execution failed\n");
        status = 3;
        return 3;
    }
    else if (pid == 0)
    {

        handle_redirection(command_arguments);
        execvp(command_arguments[0], command_arguments);
        perror("Execution failure: execvp() failed");
        exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
        status = WEXITSTATUS(status);
        return status;
    }
}

// ! - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void handle_redirection(char **args)
{
    int fd;

    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "<") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "File Missing! Please give the file name for input redirection!");
                exit(1);
            }
            fd = open(args[i + 1], O_RDONLY);
            if (fd < 0)
            {
                perror("File can't be opened!");
                exit(1);
            }
            dup2(fd, 0);
            close(fd);
            args[i] = NULL;
        }
        else if (strcmp(args[i], ">") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "File Missing! Please give the file name for output redirection!");
                exit(1);
            }
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, 1);
            close(fd);
            args[i] = NULL;
        }
        else if (strcmp(args[i], ">>") == 0)
        {
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, "File Missing! Please give the file name for output redirection!");
                exit(1);
            }
            fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, 1);
            close(fd);
            args[i] = NULL;
        }
    }
}

// ! - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void execute_pipe()
{
    int pipe_count = 0;
    int i = 0;
    while (command_arguments[i] != NULL)
    {
        if (strcmp(command_arguments[i], "|") == 0)
        {
            pipe_count++;
        }
        i++;
    }

    int command_begin[pipe_count + 5];
    command_begin[0] = 0;
    int j = 0;
    int k = 1;
    while (command_arguments[j] != NULL)
    {
        if (strcmp(command_arguments[j], "|") == 0)
        {
            command_begin[k] = j + 1;
            command_arguments[j] = NULL;
            k++;
        }
        j++;
    }

    int pipefds[pipe_count][2];

    for (int i = 0; i < pipe_count; i++)
    {
        pipe(pipefds[i]);
    }

    int command_count = pipe_count + 1;

    for (int i = 0; i < command_count; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            if (i > 0)
            {
                dup2(pipefds[i - 1][0], 0);
            }
            if (i < pipe_count)
            {
                dup2(pipefds[i][1], 1);
            }
            for (int j = 0; j < pipe_count; j++)
            {
                close(pipefds[j][0]);
                close(pipefds[j][1]);
            }
            char **current_args = &command_arguments[command_begin[i]];

            handle_redirection(current_args);
            if (execvp(current_args[0], current_args) == -1)
            {
                fprintf(stderr, "%s: command not found\n", current_args[0]);
                exit(1);
            }
        }
    }

    for (int i = 0; i < pipe_count; i++)
    {
        close(pipefds[i][0]);
        close(pipefds[i][1]);
    }

    for (int i = 0; i < command_count; i++)
    {
        wait(NULL);
    }
}

// ! - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int execute_built_in_command()
{
    if (command_arguments[0] == NULL)
    {
        return 0;
    }

    if (strcmp(command_arguments[0], "cd") == 0)
    {
        char *target_dir = NULL;
        int cd_error = 0;

        if (command_arguments[1] == NULL)
        {
            if (chdir(getenv("HOME")) != 0)
            {
                perror("cd");
                cd_error = 1;
            }
        }
        else if (command_arguments[2] != NULL)
        {
            fprintf(stderr, "Too many arguments!");
            cd_error = 1;
        }
        else
        {
            target_dir = command_arguments[1];
        }

        if (!cd_error && target_dir != NULL)
        {
            if (chdir(target_dir) != 0)
            {
                perror("shell: cd");
                cd_error = 1;
            }
        }
        return 1;
        status = cd_error;
    }
    return 0;
}

// ! - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void add_to_history(const char *cmd)
{
    if (cmd == NULL || strlen(cmd) <= 1)
        return;

    if (history_count < MAX_HISTORY)
    {
        history[history_count++] = strdup(cmd);
    }
    else
    {
        free(history[0]);
        for (int i = 1; i < MAX_HISTORY; i++)
        {
            history[i - 1] = history[i];
        }
        history[MAX_HISTORY - 1] = strdup(cmd);
    }
}

// ! - - - - - - - - - - - - - - - - - - - - - - - - - - - -

void print_history()
{
    for (int i = 0; i < history_count; i++)
    {
        printf("%d: %s", i + 1, history[i]);
    }
}

void handle_sigint(int sig)
{
    printf("\nCaught SIGINT (Ctrl+C). Stopping Command Execution. Use 'EXIT' to quit.\n");
    printf("UNIX Shell > ");
    fflush(stdout);
}

void print_details()
{
    printf("\n\n== == == == == == A B O U T == == == == == ==\n\n");
    printf("This program is developed by:\n");
    printf("I) Al Saihan Tajvi | Student ID: 23301219\n");
    printf("II) Farhan Zarif | 23301692\n");
    printf("III) Sadik Mina Dweep | 22101837\n\n");

    printf("Features Contribution:\n");
    printf("1. Al Saihan Tajvi\n");
    printf("   Task 1: Display a command prompt (e.g., sh>) and read user input.\n");
    printf("   Task 2: Parse and execute system commands using fork() and exec() system calls.\n");
    printf("   Task 5: Support multiple commands in-line separated by semicolon (;).\n");
    printf("   Task 6: Support execution of multiple commands in sequence using logical AND (&&).\n\n");

    printf("2. Farhan Zarif\n");
    printf("   Task 4: Support command piping (|) for any number of pipes.\n");
    printf("   Task 3: Support input (<) and output (>, >>) redirection using dup() and dup2().\n\n");

    printf("3. Sadik Mina Dweep\n");
    printf("   Task 8: Implement signal handling (CTRL+C) using signal() and sigaction() to terminate the currently running command without exiting the shell.\n");
    printf("   Task 7: Maintain and support history of executed commands.\n\n");
}