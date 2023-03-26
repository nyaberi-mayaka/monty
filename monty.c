#include "monty.h"

char **token = NULL;
int flag = 0;
int STACK = -1;


/**
 * main - calls the monty opcodes
 * @ac: argument count
 * @av: argument vector
 *
 * Return: EXIT_SUCCESS always
 */

int main(int ac, char **av)
{
	FILE *stream = NULL;

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	stream = open_file(av[1]);
	read_file(stream);
	fclose(stream);
	return (EXIT_SUCCESS);
}


/**
 * open_file - opens a file using a path from argv[1]
 * @av: file name with path to be opened
 *
 * Return: a FILE * to the opened file
 */
FILE *open_file(char *av)
{
	FILE *stream = fopen(av, "r");

	if (!stream)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av);
		exit(EXIT_FAILURE);
	}
	return (stream);
}

/**
 * read_file - reads the contents of a file line by line and calls
 * the corresponding function of an opcode
 * @stream: a file FILE * to the opened file
 *
 * Return: a line read from the file represented by the descriptor
 */
void read_file(FILE *stream)
{
	stack_t *head = NULL;
	unsigned int line_num = 1;
	size_t len = 0;
	ssize_t nread;
	char *line = NULL;
	int checker;

	while ((nread = getline(&line, &len, stream)) != -1)
	{
		token = tokenize(line, DELIMS);
		if (token)
		{
			if (token[0][0] == '#')
			{
				free_token();
				continue;
			}
			checker = check_opcode(&head, line_num);
			if (checker < 0 || flag)
			{
				flag = 0;
				if (checker == -2)
					dprintf(STDERR_FILENO,
						"L%d: unknown instruction %s\n",
						line_num, token[0]);
				free_memory(&head, line, stream);
			}
			free_token(), token = NULL;
		}

		line_num++;
	}
	free(line), free_stack(head);
}


/**
 * check_opcode - checks if a token is a valid opcode and calls the
 *                corresponding function
 * @head: pointer to the top of the list
 * @line_num: The line number of the opcode in the opened file
 * Return: index of the opcode function on success
 *         -2 when push fails
 *         -1 when the others fail
 */

int check_opcode(stack_t **head, unsigned int line_num)
{
	unsigned int i = 0;
	int checker;
	instruction_t check[] = {{"push", push}, {"pall", pall},
				 {"pint", pint}, {"pop", pop},
				 {"swap", swap}, {"add", add},
				 {"nop", nop}, {"sub", sub},
				 {"div", divide}, {"mod", mod},
				 {"mul", mul}, {"pchar", pchar},
				 {"pstr", pstr}, {"rotl", rotl},
				 {"rotr", rotr}, {NULL, NULL}};

	if (strcmp("stack", token[0]) == 0)
		STACK = 115;
	else if (strcmp("queue", token[0]) == 0)
		STACK = 113;
	else
	{
		while (check[i].opcode)
		{
			checker = strcmp(token[0], check[i].opcode);
			if (checker == 0)
			{
				checker = error_call(head, line_num);
				if (!checker)
				{
					check[i].f(head, line_num);
					return (i);
				}
				else
					return (checker);
			}
			i++;
		}
		return (-2);
	}
	return (0);
}
