#include "monty.h"

/**
 * malloc_failure - error if you cannot allocate memory anymore
 */
void malloc_failure(void)
{
	dprintf(STDERR_FILENO, "Error: malloc failed\n");
	flag = 1;
}

/**
 * error_call - checks if there is an error in the opcode given
 * @line_num: line associated with the new opcode
 * @head: The address of the top of the stack
 *
 * Return: 1 on sucess
 *         0 on failure
 */

int error_call(stack_t **head, unsigned int line_num)
{
	int i = 0;
	error_t opcodes[] = {{"push", push_err}, {"pint", pint_err},
			     {"pop", pop_err}, {"swap", swap_err},
			     {"add", add_err}, {"sub", sub_err},
			     {"div", div_err}, {"mul", mul_err},
			     {"mod", mod_err}, {"pchar", pchar_err},
			     {NULL, NULL}};

	if (token[0])
	{
		while (opcodes[i].opcode)
		{
			if (strcmp(opcodes[i].opcode, token[0]) == 0)
				return (opcodes[i].f(head, line_num));

			i++;
		}
	}
	return (0);
}


/**
 * push_err - checks for the push opcode errors
 * @line_num: line associated with the new opcode
 * @head: The address of the top of the stack
 *
 * Return: 1 on sucess
 *         0 on failure
 */

int push_err(stack_t **head, unsigned int line_num)
{
	(void) head;
	if (strcmp(token[0], "push") == 0)
	{
		if (!(token + 1) || check_int())
		{
			dprintf(STDERR_FILENO, "L%d: usage: push integer\n", line_num);
			return (-1);
		}
		return (0);
	}
	return (-1);
}

/**
 * pint_err - checks for the pint opcode errors
 * @line_num: line associated with the new opcode
 * @head: The address of the top of the stack
 *
 * Return: void
 */
int pint_err(stack_t **head, unsigned int line_num)
{
	if (strcmp(token[0], "pint") == 0)
	{
		if (!*head)
		{
			dprintf(STDERR_FILENO, "L%d: can't pint, stack empty\n", line_num);
			return (-1);
		}
		return (0);
	}
	return (-1);
}


/**
 * pop_err - checks for the pop opcode errors
 * @line_num: line associated with the new opcode
 * @head: The address of the top of the stack
 *
 * Return: 1 on sucess
 *         0 on failure
 */

int pop_err(stack_t **head, unsigned int line_num)
{
	if (strcmp(token[0], "pop") == 0)
	{
		if (!*head)
		{
			dprintf(STDERR_FILENO, "L%d: can't pop an empty stack\n", line_num);
			return (-1);
		}
		return (0);
	}
	return (-1);
}
