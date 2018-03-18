#include <stdio.h> 
#include <string.h>
#include <malloc.h>

typedef struct node {
	char data;
	struct node *left, *right;
}BiTNode, *BiTree;

char inorder[100], postorder[100];

int Search(int m, int n, char ch) {
	for (int i = 0; i <= n; i++)
		if (ch == inorder[i])
			return i;
}

BiTree createtree(int m1, int n1, int len) {
	BiTree root = (BiTree)malloc(sizeof(BiTNode));
	int m2 = m1 + len - 1, n2 = n1 + len - 1, i;
	if (len < 1)
		return NULL;
	root->data = postorder[n2];
	i = Search(m1, m2, postorder[n2]);
	root->left = createtree(m1, n1, i - m1);
	root->right = createtree(i + 1, n1 + i - m1, m2 - i);
	return root;
}

int main() {
	int n, i = 1, j = 0;
	BiTree root, p, a[100];
	gets(inorder); gets(postorder);
	n = strlen(inorder);
	a[0] = p = root = createtree(0, 0, n);
	for (j = 0; j < i; j++) {
		if (p->left != NULL)
			a[i++] = p->left;
		if (p->right != NULL)
			a[i++] = p->right;
		p = a[j + 1];
	}
	for (i = 0; i < j; i++)
		printf("%c", a[i]->data);
	printf("\n");

	return 0;
}