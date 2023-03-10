#ifndef RUN_COMMAND_H
#define RUN_COMMAND_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <readline/history.h>
#include "list.h"

char *run_command(char *command)
{
    // split command by | and > and save to array
    List redirects;
    init(&redirects);
    char *token = strtok(command, ">");

    while (token != NULL)
    {
        add(&redirects, token);
        token = strtok(NULL, ">");
    }

    add_history(command);
    // run command using system and save output to char*
    char *output = (char *)malloc(1024);
    output[0] = '\0';

    FILE *fp = NULL;

    if (command[0] == 'r' && command[1] == 'm')
    {
        fp = popen("./my_rm", "r");
    }
    else if (command[0] == 'm' && command[1] == 'v')
    {
        fp = popen("./my_mv", "r");
    }
    else if (command[0] == 'd' && command[1] == 'i' && command[2] == 'r')
    {
        fp = popen("./my_dir", "r");
    }
    else
    {
        fp = popen(command, "r");
    }

    // read all output until EOF and save to output
    int a = fread(output, 1, 1024, fp);
    pclose(fp);

    if (strcmp(command, "clear") == 0)
    {
        output[0] = '\0';
        system("clear");
    }

    if (strcmp(command, "exit") == 0)
        exit(0);

    if (command[0] == 'c' && command[1] == 'd')
        chdir(command + 3);

    for (int i = 0; i < redirects.size; i++)
    {
        char *redirect = redirects.content[i];
        char *file_name = strtok(redirect, " ");
        char *file_command = strtok(NULL, " ");

        if (file_command == NULL)
            file_command = output;

        FILE *file = fopen(file_name, "w");
        fwrite(file_command, 1, strlen(file_command), file);
        fclose(file);
    }

    return output;
}

#endif