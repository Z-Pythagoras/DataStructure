#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct _LNode {
	ElemType data;
	struct _LNode *next;
}LNode, *Linklist;

Linklist head, p, r, s;
int n, k, m;

void InitList() {
	head = (Linklist)malloc(sizeof(LNode));
	head->next = NULL;
}

void CreateListR() {
	r = head;
	for (int i = 0; i < n; i++) {
		s = (Linklist)malloc(sizeof(LNode));
		s->data = i + 1;
		r->next = s;    
		r = s;
		if (s->data == k)
			p = s;
	}
	r->next = head->next;
}

void ListDeleteAndOutput(int ii) {
	for (int i = 1; i < m; i++)
		p = p->next;
	printf("%d", p->data);
	printf("%c", (!(ii % 10) || ii == n) ? '\n' : ' ');
	p->data = p->next->data;
	s = p->next;
	p->next = s->next;
	free(s);
}

int main() {
	InitList();
	scanf("%d,%d,%d", &n, &k, &m);
	if (n < 1 || k < 1 || m < 1)
		printf("n,m,k must bigger than 0.\n");
	else if (k > n)
		printf("k should not bigger than n.\n");
	else {
		CreateListR();
		for (int j = 1; j <= n; j++)
			ListDeleteAndOutput(j);
	}
	free(head);
	return 0;
}