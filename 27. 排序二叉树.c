#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int data, vis;
	int parent, leftChild, rightChild;
}DuTree;

DuTree sqTree[1005];
int pos = 2, tmp = 0, order[1005], i;

void Insert(int e, int now) {
	if (!sqTree[now].data) {
		sqTree[now].data = e;
		return;
	}
	if (e > sqTree[now].data) {
		if (!sqTree[now].rightChild) {
			sqTree[now].rightChild = pos;
			sqTree[pos].data = e;
			sqTree[pos++].parent = now;
		}
		else
			Insert(e, sqTree[now].rightChild);
	}
	else {
		if (!sqTree[now].leftChild) {
			sqTree[now].leftChild = pos;
			sqTree[pos].data = e;
			sqTree[pos++].parent = now;
		}
		else
			Insert(e, sqTree[now].leftChild);
	}
}

void Print(int deep, int now) {
	if (!sqTree[now].data)
		return;
	if (sqTree[now].leftChild && !sqTree[sqTree[now].leftChild].vis)
		Print(deep + 1, sqTree[now].leftChild);
	else {
		if (!sqTree[now].vis) {
			sqTree[now].vis = 1;
			for (i = 0; i < deep; i++)
				printf("    ");
			printf("%d\n", sqTree[now].data);
			order[tmp++] = sqTree[now].data;
		}
		if (sqTree[now].rightChild && !sqTree[sqTree[now].rightChild].vis)
			Print(deep + 1, sqTree[now].rightChild);
		else
			Print(deep - 1, sqTree[now].parent);
	}
}

int main() {
	int num;
	memset(sqTree, 0, sizeof(sqTree));
	while (scanf("%d", &num) && num)
		Insert(num, 1);
	Print(0, 1);
	printf("\n");
	for (i = 0; i < tmp; i++)
		printf(" %d", order[i]);
	printf("\n");

	return 0;
}