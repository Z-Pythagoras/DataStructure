#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct _DuLNode {
	ElemType data;
	struct _DuLNode *prior, *next;
}DuLNode, *DuLinklist;

int n, k, m;
DuLinklist head, p, q, r, s, pp, qq;

void InitList() {
	head = (DuLinklist)malloc(sizeof(DuLNode));
	head->data = 0;
	head->next = head->prior = NULL;
}

void CreateListR(int nn) {
	r = s = head;
	for (int i = 1; i <= nn; i++) {
		s = (DuLinklist)malloc(sizeof(DuLNode));
		s->data = i;
		s->prior = r;
		r->next = s;
		r = s;
		if (s->data == k)
			pp = qq = s;
	}
	r->next = head;
	head->prior = r;
}

void ElemDelete(DuLinklist a) {
	a->prior->next = a->next;
	a->next->prior = a->prior;
}

void Joseph() {
	while(n) {
		p = pp;
		q = qq;
		for (int i = 1; i < m; i++) {
			p = p->next;    q = q->prior;
			if (p == head)
				p = p->next;
			if (q == head)
				q = q->prior;
		}
		pp = p->next;
		qq = q->prior;
		if (pp == head)
			pp = pp->next;
		if (qq == head)
			qq = qq->prior;
		if (p == q) {
			n -= 1;
			printf("%d,", p->data);
			ElemDelete(p);
		}
		else {
			n -= 2;
			printf("%d-%d,", p->data, q->data);
			ElemDelete(p);
			ElemDelete(q);
		}
	}
	printf("\n");
}

int main() {
	InitList();
	scanf("%d,%d,%d", &n, &k, &m);
	if (!n || !k || !m)
		printf("n,m,k must bigger than 0.\n");
	else if (k > n)
		printf("k should not bigger than n.\n");
	else {
		CreateListR(n);
		Joseph();
	}
	return 0;
}
