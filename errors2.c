#include "monty.h"


/**
 * swap_err - checks for the swap opcode errors
 * @line_num: line associated with the new opcode
 * @head: The address of the top of the stack
 *
 * Return: 1 on sucess
 *         0 on failure
 */

int swap_err(stack_t **head, unsigned int line_num)
{
	if (strcmp(token[0], "swap") == 0)
	{
		if (!*head || !(*head)->next)
		{
			dprintf(STDERR_FILENO, "L%d: can't swap, stack too short\n", line_num);
			return (-1);
		}
		return (0);
	}
	return (-1);
}



/**
 * add_err - checks for the add opcode errors
 * @line_num: line associated with the new opcode
 * @head: The address of the top of the stack
 *
 * Return: 1 on sucess
 *         0 on failure
 */

int add_err(stack_t **head, unsigned int line_num)
{
	if (strcmp(token[0], "add") == 0)
	{
		if (!*head || !(*head)->next)
		{
			dprintf(STDERR_FILENO, "L%d: can't add, stack too short\n", line_num);
			return (-1);
		}
		return (0);
	}
	return (-1);
}
