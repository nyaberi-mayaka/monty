#include "monty.h"

/**
 * pstr - prints the char at the top of the stack,
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */

void pstr(stack_t **head, unsigned int line_num __attribute__ ((unused)))
{
	stack_t *temp;

	if (*head)
	{
		temp = *head;
		while (temp)
		{
			if (temp->n < 0 || temp->n > 127 || temp->n == 0)
			{
				printf("\n");
				break;
			}
			printf("%c", temp->n);
			if (!temp->next)
				printf("\n");
			temp = temp->next;
		}
	}
	else
		printf("\n");
}


/**
 * rotl - rotates the stack to the top
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */

void rotl(stack_t **head, unsigned int line_num __attribute__ ((unused)))
{
	stack_t *temp;

	if (*head && (*head)->next)
	{
		temp = *head;

		while (temp->next)
			temp = temp->next;

		temp->next = *head;
		(*head)->prev = temp;
		temp = (*head)->next;
		temp->prev = NULL;
		(*head)->next = NULL;
		*head = temp;
	}
}


/**
 * rotr - rotates the stack to the bottom.
 * @head: address of the top of stack
 * @line_num: line number of the instruction from @file
 */

void rotr(stack_t **head, unsigned int line_num __attribute__ ((unused)))
{
	stack_t *temp;

	if (*head && (*head)->next)
	{
		temp = *head;

		while (temp->next)
			temp = temp->next;

		temp->next = *head;
		(*head)->prev = temp;
		temp->prev->next = NULL;
		temp->prev = NULL;
		*head = temp;
	}
}
