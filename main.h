#ifndef MAIN_H
#define MAIN_H

#define MAX_PATH_LENGTH 1024

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

void execmd(char **argv);
char *get_location(char *command);
void print_environment(void);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
void handle_cd_command(char **argv, int num_tokens);
void handle_semicolon_commands(const char *input);
void change_directory(char *dir);
char *replace_variables(char *command, int child_status);

#endif
