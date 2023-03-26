#include "monty.h"


/**
 * divide - divides the second top element of the stack by the top
 * element of the stack.
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */

void divide(stack_t **head, unsigned int line_num __attribute__ ((unused)))
{
	if (*head && (*head)->next)
	{
		(*head)->next->n /= (*head)->n;
		pop(head, line_num);
	}
}


/**
 * mul - multiplies the second top element of the stack with the
 * top element of the stack.
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */

void mul(stack_t **head, unsigned int line_num)
{
	if (*head && (*head)->next)
	{
		(*head)->next->n *= (*head)->n;
		pop(head, line_num);
	}
}


/**
 * mod - computes the rest of the division of the second top element
 * of the stack by the top element of the stack.
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */

void mod(stack_t **head, unsigned int line_num __attribute__ ((unused)))
{
	if (*head && (*head)->next)
	{
		(*head)->next->n %= (*head)->n;
		pop(head, line_num);
	}
}


/**
 * pchar - prints the char at the top of the stack,
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */

void pchar(stack_t **head, unsigned int line_num __attribute__ ((unused)))
{
	if (*head)
		printf("%c\n", (*head)->n);
}
