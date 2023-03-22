#include "monty.h"

/**
 * main - calls the monty opcodes
 * @ac: argument count
 * @av: argument vector
 *
 * Return: EXIT_SUCCESS always
 */

int main(int ac, char **av)
{
	stack_t *head = NULL;
	FILE *stream = NULL;
	ssize_t nread;
	int i = 0;

	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	stream = open_file(stream, av[1]);
	read_file(stream, &head);
	printf("RETURNED TO THE MAIN FUNCTION !!!!!!****>\n");
	free_stack(head);
	fclose(stream);
	printf("RETURNED TO THE MAIN FUNCTION !!!!!!****>FREED ALL\n");
	return (EXIT_SUCCESS);
}
/**
 * push - adds a new element to the top of the stack
 * @n: data associated with the new element
 * @head: The address of the top of the stack
 * Return: void
 */

void push(stack_t **head, unsigned int n)
{
	stack_t *new_node = NULL;

	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		dprintf(STDERR_FILENO, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->prev = new_node->next = NULL;
	new_node->n = n;

	if (!*head)
		*head = new_node;
	else
	{
		new_node->next = *head;
		(*head)->prev = new_node;
		*head = new_node;
	}
}
/**
 * pall - prints all the values on the stack, starting from the top
 * of the stack.
 * @head: The address of the top of the stack
 * @n: The element read from a file
 */
void pall(stack_t **head, unsigned int n __attribute__ ((unused)))
{
	stack_t *temp = *head;

	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

/**
 * free_stack - frees memory allocated to every stack_t element
 * @head: The address of the top of the stack
 * @n: The element read from a file
 */

void free_stack(stack_t *head)
{
	stack_t *temp = NULL;

	while (head)
	{
		temp = head;
		head = temp->next;
		free(temp);
	}
}

/**
 * open_file - opens a file using a path from argv[1]
 * @av: file name with path to be opened
 * @file: pointer to the opened file
 *
 * Return: a FILE * to the opened file
 */
FILE *open_file(FILE *file, char *av)
{
	file = fopen(av, "r");
	if (!file)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av);
		exit(EXIT_FAILURE);
	}
	return (file);
}

/**
 * read_file - reads the contents of a file line by line and calls
 * the corresponding function of an opcode
 * @stream: a file FILE * to the opened file
 *
 * Return: a line read from the file represented by the descriptor
 */
void read_file(FILE *stream, stack_t **head)
{
	int line_num = 1, checker, i = 0;
	size_t len = 0;
	ssize_t nread;
	char *line = NULL, **token = NULL;

	while ((nread = getline(&line, &len, stream)) != -1)
	{
		token = tokenize(line, " \n\t");
		printf("Retrieved line of length %s\n", line);
		i = 0;
		while (token[i])
			printf("****%s****->\n", token[i++]);

		checker = check_opcode(token);
		if (checker < 0)
		{
			dprintf(STDERR_FILENO,
				"L%d: unknown instruction %s\n",
				line_num, token[0]);
			free_token(token), free(line), fclose(stream), free_stack(*head);
			exit(EXIT_FAILURE);
		}

		if (token)
			call_funcs(token, head, checker);

		line_num++, free_token(token), token = NULL;
	}
	free(line);
}
int call_funcs(char **token, stack_t **head, int i)
{
        instruction_t check[] = {{"push", push}, {"pall", pall},
				 {NULL, NULL}};
	unsigned int atoi_int = 0;

	if (token[1])
		atoi_int = atoi(token[1]);

	if (check[i].opcode)
	{
		if (strcmp(token[0], check[i].opcode) == 0)
		{
			if (strcmp("push", token[0]) == 0)
			{
				if (atoi_int != 0)
					check[i].f(head, atoi_int);
				else
					return (-1);
			}
			else
				check[i].f(head, atoi_int);
		}
	}
	return (0);
}

int check_opcode(char **token)
{
	unsigned int i = 0, j = 0;
	int checker;
	instruction_t check[] = {{"push", push}, {"pall", pall},
				 {NULL, NULL}};
	while (check[i].opcode)
	{
		checker = strcmp(token[0], check[i].opcode);
		if (checker == 0)
		{
			while (token[j++]);
			j--;

			if (j == 2 && strcmp(check[i].opcode, "push") == 0)
				return (i);
			else if (j == 1 && strcmp(check[i].opcode,
						  "push") != 0)
				return (i);
			else
				return (-1);
		}
		i++;
	}
	return (-1);
}


/**
 * tokenize - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **tokenize(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

void free_token(char **token)
{
	int i = 0;

	if (*token)
	{
		while (token[i])
			free(token[i]), i++;
		free(token);
	}
}
