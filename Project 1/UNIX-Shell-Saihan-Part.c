#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

// ! == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==

// * Buffer to store the full prompt
char command[256];

// * Array to store each substring of each individual command, divided by spaces or newlines
char *command_arguments[20];
int command_arg_count = 0;

// * Array to store each substring of "full" individual command, divided by semicolons
char *f_commands[20];
int f_commands_count = 0;

// * Array to store each substring of "partial" individual command, divided by logical AND operator
char *p_commands[20];
int p_commands_count = 0;
int status = 0;

// ! == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==

// * Function Prototypes [Usages given below, before the function intialization]
void split_command_by_semicolon(char *command);
void split_command_by_AND_operator(char *command);
void process_command_input(char *command);
int execute_command();

// ! == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==

// * Main Function
int main()
{
    printf("Hello World! Welcome to the UNIX Shell!\n\n");
    printf("This program is my personal contribution to our CSE321 project.\n\n");

    printf("Features:\n1. Display a command prompt (e.g., sh> ) and read user input.\n");
    printf("2. Parses the input command and execute it using fork() and exec() system calls.\n");
    printf("3. Supports built-in commands like 'cd' to change directories.\n");
    printf("4. Supports command-line arguments for the commands.\n");
    printf("5. Supports command chaining using semicolons (;) and logical AND operator (&&).\n");
    printf("6. Supports exit command to terminate the shell.\n");
    printf("7. Supports basic error handling for invalid commands and arguments.\n\n");

    printf("Lackings:\n1. No support for command history.\n");
    printf("2. No support for command completion.\n");
    printf("3. No support for command piping.\n");
    printf("4. No support for command redirection... etc.\n");

    printf("\nType 'EXIT' to close the program.\n");

    // * Infinite loop to keep the shell running
    while (1)
    {
        printf("\n");
        printf("UNIX Shell > ");

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            printf("Error reading command, terminating the process.\n");
            return 1;
        }

        if (strcmp(command, "EXIT\n") == 0)
        {
            printf("Thank You for using our shell! Closing the program!\n");
            break;
        }

        split_command_by_semicolon(command);
    }
}

// ! == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==

// * Function to split the command into arguments and then execute it
void process_command_input(char *command)
{
    // * Splits the command into arguments based on spaces and newlines
    char *token;
    command_arg_count = 0;
    token = strtok(command, " \n");

    while (token != NULL && command_arg_count < 20)
    {
        command_arguments[command_arg_count] = token;
        token = strtok(NULL, " \n");
        command_arg_count++;
    }

    // * Marks the end of the command arguments
    command_arguments[command_arg_count] = NULL;

    // * Execute the command
    execute_command();
}

// ! == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==

// * Function to split the given prompts into individual commands based on Semi-Colon
void split_command_by_semicolon(char *command)
{
    // * Splits the command into arguments based on semicolons
    char *token;
    f_commands_count = 0;
    token = strtok(command, ";");

    while (token != NULL && f_commands_count < 20)
    {
        f_commands[f_commands_count] = token;
        token = strtok(NULL, ";");
        f_commands_count++;
    }

    // * Marks the end of the command arguments
    f_commands[f_commands_count] = NULL;

    // * Afterwards, sends all the commands to be split by AND operator
    for (int i = 0; i < f_commands_count; i++)

    {
        split_command_by_AND_operator(f_commands[i]);
    }
}

// ! == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==

// * Function to split the given prompts into individual commands based on Semi-Colon
void split_command_by_AND_operator(char *command)
{
    // * Splits the command into arguments based on &&
    char *token;
    p_commands_count = 0;
    token = strtok(command, "&&");

    while (token != NULL && p_commands_count < 20)
    {
        p_commands[p_commands_count] = token;
        token = strtok(NULL, "&&");
        p_commands_count++;
    }

    // * Marks the end of the command arguments
    p_commands[p_commands_count] = NULL;

    // * Constantly run each of the indivual command, Stops when Status != 0
    for (int i = 0; i < p_commands_count; i++)
    {
        if (i == 0) // * First command always runs
        {
            process_command_input(p_commands[i]);
        }
        else if (status == 0) // * Rest of the commands run if status == 0, Or else, "break"
        {
            process_command_input(p_commands[i]);
        }
        else
        {
            break;
        }
    }
}

// ! == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==

// * Fork a child process to execute the command
int execute_command()
{
    // * Return if the command is empty
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
        // ! Different process for "cd" command
        if (strcmp(command_arguments[0], "cd") == 0)
        {
            if (command_arg_count == 2)
            {
                if (chdir(command_arguments[1]) == -1)
                {
                    printf("Invalid directory\n");
                    return -1;
                }
            }
            else if (command_arg_count == 1)
            {
                return chdir(getenv("HOME"));
            }
            else
            {
                printf("Too many arguments\n");
                return -1;
            }
        }
        // ! For commands except "cd"
        else
        {
            return execvp(command_arguments[0], command_arguments);
        }
    }
    else
    {
        // * Parent process waits for the child process to finish and returns the status
        waitpid(pid, &status, 0);
        status = WEXITSTATUS(status);
        return status;
    }
}