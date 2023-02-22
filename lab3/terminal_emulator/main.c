#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "run_command.h"

int main(int argc, char **argv)
{
    using_history();

    char *cur_dir = getenv("HOME");
    printf("Current directory: %s\n", cur_dir);
    chdir(cur_dir);

    while (1)
    {
        char *input = readline(">");

        char *output = run_command(input);

        printf("%s", output);

        printf("Current directory: %s\n", getcwd(NULL, 0));

        free(input);
        free(output);
    }
}