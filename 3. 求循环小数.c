/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int         data;
	struct node * next;
} NODE;

void output(NODE *);
void change(int, int, NODE *);

void output(NODE * head)
{
	int k = 0;

	printf("0.");
	while (head->next != NULL && k<50)
	{
		printf("%d", head->next->data);
		head = head->next;
		k++;
	}
	printf("\n");
}

int main()
{
	int n, m;
	NODE * head;

	scanf("%d%d", &n, &m);
	head = (NODE *)malloc(sizeof(NODE));
	head->next = NULL;
	head->data = -1;
	change(n, m, head);
	output(head);
	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */
void change(int n, int m, NODE *head) {
	int nn = n, mod[50] = { 0 }, i = 0, j = 0;
	NODE * p = NULL, *q = head;
	do {
		mod[i++] = nn *= 10;
		for (p = head->next, j = 0; p != NULL && j < i - 1; p = p->next) {
			if (mod[j++] == nn) {
				q->next = p;
				return;
			}
		}
		NODE * tmp = (NODE *)malloc(sizeof(NODE));
		tmp->data = nn / m;
		nn %= m;
		q->next = tmp;
		q = tmp;
		q->next = NULL;
	} while (nn && i < 50);
}