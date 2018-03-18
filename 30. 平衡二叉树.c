#include<stdio.h>    
#include<stdlib.h>    
#include<string.h>    
#define MAXSIZE 1005

typedef struct node {
	int bf;
	char data;
	struct node *leftChild, *rightChild;
}AVLTNode, *AVLTree;

void  ins_AVLtree(AVLTree  *avlt, char  K) {
	AVLTree A, B, C, FA, p, fp;
	AVLTree S = (AVLTree)malloc(sizeof(AVLTNode));
	S->data = K; S->bf = 0;
	S->leftChild = S->rightChild = NULL;
	if (*avlt == NULL) {
		*avlt = S;
		return;
	}
	A = *avlt;  FA = NULL;
	p = *avlt;  fp = NULL;
	while (p != NULL) {
		if (p->bf != 0) {
			A = p; FA = fp;
		}
		fp = p;
		if (K < p->data)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if (K < fp->data)
		fp->leftChild = S;
	else
		fp->rightChild = S;
	if (K < A->data) {
		B = A->leftChild;
		A->bf = A->bf + 1;
	}
	else {
		B = A->rightChild;
		A->bf = A->bf - 1;
	}
	p = B;
	while (p != S) {
		if (K < p->data) {
			p->bf = 1;
			p = p->leftChild;
		}
		else {
			p->bf = -1;
			p = p->rightChild;
		}

		if (A->bf == 2 && B->bf == 1) {
			B = A->leftChild;
			A->leftChild = B->rightChild;
			B->rightChild = A;
			A->bf = 0;
			B->bf = 0;
			if (FA == NULL)
				*avlt = B;
			else
				if (A == FA->leftChild)
					FA->leftChild = B;
				else
					FA->rightChild = B;
		}
		else if (A->bf == -2 && B->bf == -1) {
			B = A->rightChild;
			A->rightChild = B->leftChild;
			B->leftChild = A;
			A->bf = 0;
			B->bf = 0;
			if (FA == NULL)
				*avlt = B;
			else if (A == FA->leftChild)
				FA->leftChild = B;
			else
				FA->rightChild = B;
		}
		else if (A->bf == 2 && B->bf == -1) {
			B = A->leftChild;
			C = B->rightChild;
			B->rightChild = C->leftChild;
			A->leftChild = C->rightChild;
			C->leftChild = B;
			C->rightChild = A;
			if (S->data < C->data) {
				A->bf = -1; B->bf = C->bf = 0;
			}
			else if (S->data >C->data) {
				A->bf = C->bf = 0; B->bf = 1;
			}
			else
				A->bf = B->bf = 0;
			if (FA == NULL)
				*avlt = C;
			else
				if (A == FA->leftChild)
					FA->leftChild = C;
				else
					FA->rightChild = C;
		}
		else if (A->bf == -2 && B->bf == 1) {
			B = A->rightChild;
			C = B->leftChild;
			B->leftChild = C->rightChild;
			A->rightChild = C->leftChild;
			C->leftChild = A;
			C->rightChild = B;
			if (S->data <C->data) {
				A->bf = C->bf = 0; B->bf = -1;
			}
			else if (S->data >C->data) {
				A->bf = 1; B->bf = C->bf = 0;
			}
			else
				A->bf = B->bf = 0;
			if (FA == NULL)
				*avlt = C;
			else
				if (A == FA->leftChild)
					FA->leftChild = C;
				else
					FA->rightChild = C;
		}
	}
}

AVLTree CreateAVLT(AVLTNode *valt) {
	char str[MAXSIZE];
	scanf("%s", str);
	for (int i = 0; i < strlen(str); i++)
		ins_AVLtree(&valt, str[i]);
	return valt;
}

void PreOrder(AVLTree root) {
	if (root != NULL) {
		printf("%c", root->data);
		PreOrder(root->leftChild);
		PreOrder(root->rightChild);
	}
}

void InOrder(AVLTree root) {
	if (root != NULL) {
		InOrder(root->leftChild);
		printf("%c", root->data);
		InOrder(root->rightChild);
	}
}

void PostOrder(AVLTree root) {
	if (root != NULL) {
		PostOrder(root->leftChild);
		PostOrder(root->rightChild);
		printf("%c", root->data);
	}
}

void PrintTree(AVLTree bt, int nLayer) {
	if (bt == NULL) return;
	PrintTree(bt->rightChild, nLayer + 1);
	for (int i = 0; i < nLayer; i++)
		printf("    ");
	printf("%c\n", bt->data);
	PrintTree(bt->leftChild, nLayer + 1);
}

int main() {
	AVLTree valt = NULL;
	valt = CreateAVLT(valt);
	printf("Preorder: ");
	PreOrder(valt);
	printf("\nInorder: ");
	InOrder(valt);
	printf("\nPostorder: ");
	PostOrder(valt);
	printf("\nTree:\n");
	PrintTree(valt, 0);

	return 0;
}