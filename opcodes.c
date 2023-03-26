#include "monty.h"

/**
 * push - adds a new element to the top of the stack
 * @line_num: line associated with the new opcode
 * @head: The address of the top of the stack
 *
 * Return: void
 */

void push(stack_t **head, unsigned int line_num  __attribute__ ((unused)))
{
	stack_t *new_node = NULL;
	static stack_t *tail;

	new_node = malloc(sizeof(stack_t));
	if (!new_node)
	{
		malloc_failure();
		return;
	}

	new_node->prev = new_node->next = NULL;
	new_node->n = atoi(token[1]);

	if (!*head)
		*head = tail = new_node;
	else
	{
		if (STACK == 115 || STACK == -1)
		{
			new_node->next = *head;
			(*head)->prev = new_node;
			*head = new_node;
		}
		else if (STACK == 113)
		{
			new_node->prev = tail;
			tail->next = new_node;
			tail = new_node;
		}
	}
}


/**
 * pall - prints all the values on the stack, starting from the top
 * of the stack.
 * @head: The address of the top of the stack
 * @n: line associated with the new opcode
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
 * atoi_int - converts a string to an equivalent integer
 * @n: line number of the instruction
 * @check_0: checks if the string contains numeric values, '+', '-'
 *
 * Return: the equivalent intger on success
 *         0 when it fails
 */
int atoi_int(int n, int check_0)
{
	int int_atoi = 0;

	if (*(token + 1))
	{
		int_atoi = atoi(token[1]);
	}
	if (!int_atoi && check_0)
	{
		dprintf(STDERR_FILENO, "L%d: usage: push integer\n", n);
		flag = 1;

	}

	return (int_atoi);
}

/**
 * pint - prints the value at the top of the stack
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */

void pint(stack_t **head, unsigned int line_num __attribute__ ((unused)))
{
	if (*head)
		printf("%d\n", (*head)->n);
}


/**
 * check_int - checks if a string is a string of integers
 *
 * Return: 0 - success
 *         1 - failure
 */
int check_int(void)
{
	int i, flag = 0;

	if (token[1])
	{
		i = 0;
		while (token[1][i])
		{
			if ((token[1][i] >= '0' && token[1][i] <= '9')
			    || token[1][i] == '+' || token[1][i] == '-')
			{
				if (token[1][i] >= '0' && token[1][i] <= '9')
					flag = 1;
				i++;
				continue;
			}
			else
				return (1);

		}
			if (flag)
				return (0);
	}
	return (1);
}
