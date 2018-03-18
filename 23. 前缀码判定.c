#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *leftChild, *rightChild;
}BiTNode,*BiTree;

int main() {
	int n, l, i, flag = 1;
	char str[10005];
	BiTree root = (BiTree)malloc(sizeof(BiTNode)), p;

	root->data = 0; root->leftChild = root->rightChild = NULL;
	scanf("%d", &n);
	while (n--) {
		scanf("%s", str);
		l = strlen(str);
		p = root;
		for (i = 0; i < l; i++) {
			if (str[i] == '1') {
				if (p->rightChild == NULL) {
					p->rightChild = (BiTree)malloc(sizeof(BiTNode));
					p = p->rightChild;
					p->leftChild = p->rightChild = NULL;
					if (i == l - 1)
						p->data = 1;
					else
						p->data = 0;
				}
				else if (p->rightChild->data || i == l - 1) {
					flag = 0; break;
				}
				else
					p = p->rightChild;
			}
			else {
				if (p->leftChild == NULL) {
					p->leftChild = (BiTree)malloc(sizeof(BiTNode));
					p = p->leftChild;
					p->leftChild = p->rightChild = NULL;
					if (i == i - 1)
						p->data = 1;
					else
						p->data = 0;
				}
				else if (p->leftChild->data || i == l - 1) {
					flag = 0; break;
				}
				else
					p = p->leftChild;
			}
			if (!flag)
				break;
		}
		if (!flag)
			break;
	}
	if (flag)
		printf("YES\n");
	else
		printf("%s\n", str);

	return 0;
}