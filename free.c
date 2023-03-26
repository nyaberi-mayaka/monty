#include "monty.h"

/**
 * free_token - frees a string of tokens
 */

void free_token(void)
{
	int i = 0;

	if (*token)
	{
		while (token[i])
			free(token[i]), i++;
		free(token);
	}
}

/**
 * free_stack - frees memory allocated to every stack_t element
 * @head: The address of the top of the stack
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
 * free_memory - Free the allocaated memory used during program execution.
 * @head: A double pointer to the head of the stack.
 * @line: Line of current instruction.
 * @fp: Pointer to a file from which the instructions are being
 *	read from.
 */
void free_memory(stack_t **head, char *line, FILE *fp)
{
	if (*head != NULL)
		free_stack(*head);
	free(line);
	free_token();
	fclose(fp);
	exit(EXIT_FAILURE);
}
