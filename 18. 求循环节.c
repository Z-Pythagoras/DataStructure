/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int         data;
	struct node * next;
} NODE;

NODE * find(NODE *, int *);
void outputring(NODE *);
void change(int, int, NODE *);

void outputring(NODE * pring)
{
	NODE * p;
	p = pring;
	if (p == NULL)
		printf("NULL");
	else
		do
		{
			printf("%d", p->data);
			p = p->next;
		} while (p != pring);
		printf("\n");
		return;

}

int main()
{
	int n, m;
	NODE * head, *pring;

	scanf("%d%d", &n, &m);
	head = (NODE *)malloc(sizeof(NODE));
	head->next = NULL;
	head->data = -1;

	change(n, m, head);
	pring = find(head, &n);
	printf("ring=%d\n", n);
	outputring(pring);

	return 0;
}

/* Here is waiting for you.
void change( int n, int m, NODE * head )
{
}

NODE * find( NODE * head, int * n )
{
}
*/

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */
void change(int n, int m, NODE *head) {
	int nn = n, mod[10000] = { 0 }, i = 0, j = 0;
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
	} while (nn && i < 10000);
}

NODE * find(NODE * head, int * n) {
	int cnt = 0, t = 10000, flag = 1;
	NODE *slow, *fast;
	slow = fast = head;
	while (t--) {
		if (fast == NULL || fast->next == NULL) {
			*n = 0;
			return NULL;
		}
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			break;
	}
	slow = head;
	while (slow != fast) {
		slow = slow->next;
		fast = fast->next;
	}
	head = slow;
	do {
		cnt++;
		slow = slow->next;
		fast = fast->next->next;
	} while (slow != fast);

	*n = cnt;
	return head;
}