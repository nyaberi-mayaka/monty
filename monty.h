#ifndef MONTY_H
#define MONTY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#define DELIMS " \n\t\a\b"

extern char **token;
extern int flag;
extern int STACK;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;


/**
 * struct error_s - opcode and its error function
 * @opcode: the opcode
 * @f: function to handle the opcode error
 *
 * Description: opcode and its error function
 */
typedef struct error_s
{
	char *opcode;
	int (*f)(stack_t **, unsigned int);
} error_t;

void push(stack_t **head, unsigned int);
void pall(stack_t **head, unsigned int);
void pint(stack_t **head, unsigned int);
void pop(stack_t **head, unsigned int);
void swap(stack_t **head, unsigned int);
void add(stack_t **head, unsigned int line_num);
void nop(stack_t **head, unsigned int line_num);
void sub(stack_t **head, unsigned int line_num);
void divide(stack_t **head, unsigned int line_num);
void mul(stack_t **head, unsigned int line_num);
void mod(stack_t **head, unsigned int line_num);
void pchar(stack_t **head, unsigned int line_num);
void pstr(stack_t **head, unsigned int line_num);
void rotl(stack_t **head, unsigned int line_num);
void rotr(stack_t **head, unsigned int);

int error_call(stack_t **, unsigned int);
int mod_err(stack_t **, unsigned int line_num);
int add_err(stack_t **, unsigned int line_num);
int sub_err(stack_t **, unsigned int line_num);
int div_err(stack_t **, unsigned int line_num);
int pint_err(stack_t **, unsigned int line_num);
int push_err(stack_t **, unsigned int line_num);
int pchar_err(stack_t **, unsigned int line_num);
int mul_err(stack_t **, unsigned int line_num);
int swap_err(stack_t **, unsigned int line_num);
int pop_err(stack_t **, unsigned int line_num);

void free_stack(stack_t *head);
FILE *open_file(char *av);
void read_file(FILE *);
char **tokenize(char *str, char *d);
int is_delim(char c, char *delim);
void free_token(void);
int check_opcode(stack_t **head, unsigned int line_num);
int call_funcs(stack_t **head, int i);
int atoi_int(int, int);
int check_int();
void malloc_failure(void);
void free_memory(stack_t **head, char *line, FILE *fp);

#endif /*MONTY_H*/
