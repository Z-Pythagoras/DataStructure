/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int    coef, exp;
	struct node  *next;
} NODE;

void multiplication(NODE *, NODE *, NODE *);
void input(NODE *);
void output(NODE *);

void input(NODE * head)
{
	int flag, sign, sum, x;
	char c;

	NODE * p = head;

	while ((c = getchar()) != '\n')
	{
		if (c == '<')
		{
			sum = 0;
			sign = 1;
			flag = 1;
		}
		else if (c == '-')
			sign = -1;
		else if (c >= '0'&& c <= '9')
		{
			sum = sum * 10 + c - '0';
		}
		else if (c == ',')
		{
			if (flag == 1)
			{
				x = sign * sum;
				sum = 0;
				flag = 2;
				sign = 1;
			}
		}
		else if (c == '>')
		{
			p->next = (NODE *)malloc(sizeof(NODE));
			p->next->coef = x;
			p->next->exp = sign * sum;
			p = p->next;
			p->next = NULL;
			flag = 0;
		}
	}
}

void output(NODE * head)
{
	while (head->next != NULL)
	{
		head = head->next;
		printf("<%d,%d>,", head->coef, head->exp);
	}
	printf("\n");
}

int main()
{
	NODE * head1, *head2, *head3;

	head1 = (NODE *)malloc(sizeof(NODE));
	input(head1);

	head2 = (NODE *)malloc(sizeof(NODE));
	input(head2);

	head3 = (NODE *)malloc(sizeof(NODE));
	head3->next = NULL;
	multiplication(head1, head2, head3);

	output(head3);
	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */

void multiplication(NODE *head1, NODE *head2, NODE *head3) {
	NODE * p1 = head1->next, *p2 = head2->next, *p3 = head3;
	while (p1) {
		p2 = head2->next; p3 = head3;
		while (p2) {
			if (!(p1->coef * p2->coef)) {
				p2 = p2->next;
				continue;
			}
			NODE * p = (NODE *)malloc(sizeof(NODE));
			p->coef = p1->coef * p2->coef;
			p->exp = p1->exp + p2->exp;
			while (p3->next && p3->next->exp < p->exp)
				p3 = p3->next;
			if (p3->next && p3->next->exp == p->exp) {
				p3->next->coef += p->coef;
				if (!(p3->next->coef)) {
					p3->next = p3->next->next;
					p2 = p2->next;
					continue;
				}
				p2 = p2->next;
				p3 = p3->next;
				continue;
			}
			p->next = p3->next;
			p3->next = p;
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	if (!(head3->next)) {
		NODE * p = (NODE *)malloc(sizeof(NODE));
		p->coef = 0;    p->exp = 0;
		p->next = head3->next;
		head3->next = p;
	}
}