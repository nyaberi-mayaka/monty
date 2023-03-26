#include "monty.h"

/**
 * pop - removes the top element of the stack.
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */
void pop(stack_t **head, unsigned int line_num __attribute__ ((unused)))
{
	stack_t *temp = *head;

	if (*head)
	{
		*head = temp->next;
		if (*head)
			(*head)->prev = NULL;
		free(temp);
	}
}
/**
 * swap - swaps the top two elements of the stack.
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */

void swap(stack_t **head, unsigned int line_num __attribute__ ((unused)))
{
	int temp;

	if (*head && (*head)->next)
	{
		temp = (*head)->next->n;
		(*head)->next->n = (*head)->n;
		(*head)->n = temp;
	}
}


/**
 * add - adds the top two elements of the stack.
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */

void add(stack_t **head, unsigned int line_num __attribute__ ((unused)))
{
	if (*head && (*head)->next)
	{
		(*head)->next->n += (*head)->n;
		pop(head, line_num);
	}
}


/**
 * nop - doesn’t do anything.
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */
void nop(stack_t **head __attribute__ ((unused)),
	 unsigned int line_num __attribute__ ((unused)))
{
}


/**
 * sub - subtracts the top element of the stack from the second
 * top element of the stack.
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */

void sub(stack_t **head, unsigned int line_num __attribute__ ((unused)))
{
	if (*head && (*head)->next)
	{
		(*head)->next->n -= (*head)->n;
		pop(head, line_num);
	}
}
