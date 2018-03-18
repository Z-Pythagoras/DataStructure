#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define maxn 1005

typedef struct Node {
	char data;
	struct Node *lchild;
	struct Node *rchild;
}Binode, *BiTree;

BiTree que[maxn];
int front = 0, rear = 0, cnt = 0;

void push(BiTree e) {
	if (rear + 1 < maxn)
		que[rear++] = e;
}

void pop() {
	if (front < rear)
		front++;
}

BiTree top() {
	if (front < rear)
		return que[front];
}

void CreatBiTree() {
	char ch;
	BiTree T, N;
	while (1) {
		scanf("%c", &ch);
		T = top();
		pop();
		if (ch == '\n')
			break;
		T->data = ch;
		N = (BiTree)malloc(sizeof(Binode));
		N->data = '#';
		T->lchild = N;
		push(N);
		N = (BiTree)malloc(sizeof(Binode));
		N->data = '#';
		T->rchild = N;
		push(N);
	}
}

int Check(BiTree T) {
	if (T->data != '#')
		return 1;
	else
		return 0;
}

void Visit(BiTree T) {
	if (!Check(T))
		return;
	else
		printf("%c", T->data);
}

void Print(BiTree T, int deep) {
	if (!Check(T))
		return;
	else {
		for (int i = 0; i < deep; i++)
			printf("    ");
		Visit(T); printf("\n"); deep++;
		Print(T->lchild, deep); Print(T->rchild, deep);
	}
}

void PreOrder(BiTree T) {
	if (!Check(T))
		return;
	else {
		Visit(T); PreOrder(T->lchild); PreOrder(T->rchild);
	}
}

void InOrder(BiTree T) {
	if (!Check(T))
		return;
	else {
		InOrder(T->lchild);
		if (!Check(T->lchild) && !Check(T->rchild))
			cnt++;
		Visit(T);
		InOrder(T->rchild);
	}
}

void PostOrder(BiTree T) {
	if (!Check(T))
		return;
	else {
		PostOrder(T->lchild); PostOrder(T->rchild); Visit(T);
	}
}

void TransPrint(BiTree T, int deep) {
	if (!Check(T))
		return;
	else {
		for (int i = 0; i < deep; i++)
			printf("    ");
		Visit(T); printf("\n"); deep++;
		TransPrint(T->rchild, deep); TransPrint(T->lchild, deep);
	}
}

void TransPreOrder(BiTree T) {
	if (!Check(T))
		return;
	else {
		Visit(T); TransPreOrder(T->rchild); TransPreOrder(T->lchild);
	}
}

void TransInOrder(BiTree T) {
	if (!Check(T))
		return;
	else {
		TransInOrder(T->rchild); Visit(T); TransInOrder(T->lchild);
	}
}

void TransPostOrder(BiTree T) {
	if (!Check(T))
		return;
	else {
		TransPostOrder(T->rchild); TransPostOrder(T->lchild); Visit(T);
	}
}

int main() {
	BiTree Root = (BiTree)malloc(sizeof(Binode));
	push(Root);
	CreatBiTree();

	printf("BiTree\n"); Print(Root, 0);
	printf("pre_sequence  : "); PreOrder(Root);
	printf("\nin_sequence   : "); InOrder(Root);
	printf("\npost_sequence : "); PostOrder(Root);

	printf("\nNumber of leaf: %d\n", cnt);

	printf("BiTree swapped\n"); TransPrint(Root, 0);
	printf("pre_sequence  : "); TransPreOrder(Root);
	printf("\nin_sequence   : "); TransInOrder(Root);
	printf("\npost_sequence : "); TransPostOrder(Root);
	printf("\n");

	return 0;
}