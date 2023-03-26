#include "monty.h"

/**
 * pchar_err - checks for pchar opcode errors
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 *
 * Return: 1 on sucess
 *         0 on failure
 */

int pchar_err(stack_t **head, unsigned int line_num)
{
	if (*head)
	{
		if ((*head)->n < 0 || (*head)->n > 127)
		{
			dprintf(STDERR_FILENO, "L%d: can't pchar, value out of range\n", line_num);
			return (-1);
		}
	}
	else
	{
		dprintf(STDERR_FILENO, "L%d: can't pchar, stack empty\n", line_num);
		return (-1);
	}
	return (0);
}

/**
 * mod_err - checks for the mod opcode errors
 * @line_num: line associated with the new opcode
 * @head: The address of the top of the stack
 *
 * Return: 1 on sucess
 *         0 on failure
 */

int mod_err(stack_t **head, unsigned int line_num)
{
	if (strcmp(token[0], "mod") == 0)
	{
		if (!*head || !(*head)->next)
		{
			dprintf(STDERR_FILENO, "L%d: can't mod, stack too short\n", line_num);
			return (-1);
		}

		else if (*head && (*head)->next)
		{
			if ((*head)->n == 0)
			{
				dprintf(STDERR_FILENO, "L%d: division by zero\n", line_num);
				return (-1);
			}
		}
		return (0);
	}
	return (-1);
}


/**
 * mul_err - checks for the mul opcode errors
 * @line_num: line associated with the new opcode
 * @head: The address of the top of the stack
 *
 * Return: 1 on sucess
 *         0 on failure
 */

int mul_err(stack_t **head, unsigned int line_num)
{
	if (strcmp(token[0], "mul") == 0)
	{
		if (!*head || !(*head)->next)
		{
			dprintf(STDERR_FILENO, "L%d: can't mul, stack too short\n", line_num);
			return (-1);
		}
		return (0);
	}
	return (-1);
}


/**
 * div_err - checks for the div opcode errors
 * @line_num: line associated with the new opcode
 * @head: The address of the top of the stack
 *
 * Return: 1 on sucess
 *         0 on failure
 */

int div_err(stack_t **head, unsigned int line_num)
{
	if (strcmp(token[0], "div") == 0)
	{
		if (!*head || !(*head)->next)
		{
			dprintf(STDERR_FILENO, "L%d: can't div, stack too short\n", line_num);
			return (-1);
		}

		else
		{
			if ((*head)->n == 0)
			{
				dprintf(STDERR_FILENO, "L%d: division by zero\n", line_num);
				return (-1);
			}
		}
		return (0);
	}
	return (-1);
}


/**
 * sub_err - checks for the sub opcode errors
 * @line_num: line associated with the new opcode
 * @head: The address of the top of the stack
 *
 * Return: 1 on sucess
 *         0 on failure
 */

int sub_err(stack_t **head, unsigned int line_num)
{
	if (strcmp(token[0], "sub") == 0)
	{
		if (!*head || !(*head)->next)
		{
			dprintf(STDERR_FILENO, "L%d: can't sub, stack too short\n", line_num);
			return (-1);
		}
		return (0);
	}
	return (-1);
}
