#include "main.h"

/**
 *	execmd - The main function
 *	@argv: array
 */

void execmd(char **argv)
{
	char *command = NULL, *actual_command = NULL;

	if (argv)
	{
		command = argv[0];

		actual_command = get_location(command);

		if (execve(actual_command, argv, NULL) == -1)
		{
			perror("Error");
		};
	}
}
