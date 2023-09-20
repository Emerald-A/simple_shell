#include "main.h"

/**
*	main- The main function holds the shell
*	@ac: int
*	@argv: string
*
*	return: Returns (0)
*/

int main(int ac, char **argv)
{char *prompt = "my_shell> ", *lineptr = NULL, *lineptr_copy = NULL;
	const char *delim = " \n";
	size_t n = 0, nchars_read;
	int num_tokens = 0, i, child_status;
	char *token, current_dir[MAX_PATH_LENGTH];
	pid_t child_pid;
	bool is_piped = false;

	(void)ac;
	while (1 && !is_piped)
	{
		if (!isatty(STDIN_FILENO))
			is_piped = true;
		if (getcwd(current_dir, MAX_PATH_LENGTH) != NULL)
		{
			printf("%s%s", current_dir, prompt);
		}
		else
		{
			perror("getcwd");
			printf("%s", prompt);
		}
		nchars_read = getline(&lineptr, &n, stdin);
		if (nchars_read == SIZE_MAX)
		{
			printf("Exiting shell...\n");
			free(lineptr);
			return (-1);
		}
		lineptr_copy = malloc(sizeof(char) * nchars_read);
		if (lineptr_copy == NULL)
		{perror("tsh: memory allocation error");
			return (-1);
		}
		strcpy(lineptr_copy, lineptr);
		token = strtok(lineptr, delim);
		while (token != NULL)
		{num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;
		argv = malloc(sizeof(char *) * num_tokens);

		token = strtok(lineptr_copy, delim);
		for (i = 0; token != NULL; i++)
		{argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		if (strcmp(argv[0], "exit") == 0)
		{printf("Exiting shell...\n");
			free(lineptr);
			return (0);
		}
		if (strcmp(argv[0], "env") == 0)
			print_environment();
		if (strcmp(argv[0], "cd") == 0)
			handle_cd_command(argv, num_tokens);
		child_pid = fork();
		if (child_pid == -1)
		{perror("Error (fork)");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{execmd(argv);
			exit(EXIT_FAILURE);
		}
		if (waitpid(child_pid, &child_status, 0) == -1)
			perror("Error (wait)");

		free(argv);
	}
free(lineptr_copy);
free(lineptr);

return (0);
}

/**
*	print_environment- The main function for env
*
*	return: Returns (0)
*/

void print_environment()
{
	extern char **environ;
	char **env_var = environ;

	while (*env_var != NULL)
	{
		printf("%s\n", *env_var);
		env_var++;
	}
}

/**
*	change_directory- The main function that changes directory
*	dir: the character
*
*	return: Returns (0)
*/

void change_directory(char *dir)
{
	if (chdir(dir) != 0)
	{
		perror("cd");
	}
}

/**
*   main- The main function holds the shell
*   @int: num_tokens
*   @argv: the array variable
*
*	return: Returns (0)
*/

void handle_cd_command(char **argv, int num_tokens)
{
	if (num_tokens == 1)
	{
		change_directory(getenv("HOME"));
	}
	else if (num_tokens == 2)
	{
		change_directory(argv[1]);
	}
	else
	{
		fprintf(stderr, "Usage: cd [DIRECTORY]\n");
	}
}
