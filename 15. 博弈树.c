#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ChildList* Child;

typedef struct NODE {
	char Name, Pure; 
	int Height; 
	struct NODE * Father;
	Child List;
}TNode, *Tree;

typedef struct ChildList {
	Tree SubTree;
	Child Next;
}CNode;

Tree PeoVsBot;
char tree[200], IllegalMove[20];

void AddASubTree(Tree father, Tree child) {
	Child TempCell = (Child)malloc(sizeof(CNode));
	TempCell->SubTree = child; TempCell->Next = father->List;
	father->List = TempCell;
}

Tree CreateTree(char name, Tree Father) {
	Tree ATree = (Tree)malloc(sizeof(TNode));
	ATree->Father = Father; ATree->Height = 0; ATree->List = NULL; ATree->Name = name; ATree->Pure = 1;
	if (Father != NULL)
		AddASubTree(Father, ATree);
	return ATree;
}

int PrintTree(int father, int height, Tree GrandFather) {
	printf("%c\n", tree[father]);
	Tree CurrentNode;
	CurrentNode = CreateTree(tree[father], GrandFather);
	if (height == 0)
		PeoVsBot = CurrentNode;
	for (int i = father + 1; 1; i++) {
		if (tree[i] == ')') {
			if (CurrentNode->Father != NULL) {
				if (CurrentNode->Father->Height == 0)
					CurrentNode->Father->Height = CurrentNode->Height + 1;
				else {
					if (CurrentNode->Father->Pure == 1 && ((CurrentNode->Height + 1) % 2 != CurrentNode->Father->Height % 2))
						CurrentNode->Father->Pure = 0;
					if (CurrentNode->Height + 1 > CurrentNode->Father->Height)
						CurrentNode->Father->Height = CurrentNode->Height + 1;
				}
			}
			return i;
		}
		else if (tree[i] == '(')
			i = PrintTree(i + 1, height + 1, CurrentNode);
	}
}

Tree Bot(Tree father) {
	Child Temp = father->List;
	Tree SureStep = NULL, NotSureStep = NULL;
	while (Temp != NULL) {
		if (Temp->SubTree->Pure == 1 && Temp->SubTree->Height % 2 == 0) {
			if (SureStep == NULL)	
				SureStep = Temp->SubTree;
			else if (Temp->SubTree->Height <= SureStep->Height)	
				SureStep = Temp->SubTree;
		}
		else {
			if (NotSureStep == NULL) 
				NotSureStep = Temp->SubTree;
			else if (NotSureStep->Height <= Temp->SubTree->Height)	
				NotSureStep = Temp->SubTree;
		}
		Temp = Temp->Next;
	}
	printf("computer: ");
	if (SureStep == NULL) {
		printf("%c\n", NotSureStep->Name);
		return NotSureStep;
	}
	else {
		printf("%c\n", SureStep->Name);
		return SureStep;
	}
}

Tree Player(Tree Father) {
	printf("player:\n");
	char step = getchar(); getchar();
	int find = 0;
	Child Temp = Father->List;
	Tree PtrToStep;
	while (1) {
		Temp = Father->List;
		while (Temp != NULL) {
			if (Temp->SubTree->Name == step) {
				PtrToStep = Temp->SubTree;
				find = 1;
				break;
			}
			Temp = Temp->Next;
		}
		if (!find) {
			printf("illegal move.\nplayer:\n");
			step = getchar(); getchar();
		}
		else
			return PtrToStep;
	}
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%s", tree);
	if (tree[1] == ')')	
		return 0;
	PrintTree(1, 0, NULL);
	int First, flag;
	Tree CurrentNode;
	char conti;

	while (1) {
		CurrentNode = PeoVsBot;
		flag = 1;
		printf("Who play first(0: computer; 1: player )?\n");
		scanf("%d", &First); getchar();
		if (!First) {
			CurrentNode = Bot(CurrentNode);
			if (CurrentNode->List == NULL) {
				printf("Sorry, you lost.\n");
				flag = 0;
			}
		}
		while (flag) {
			CurrentNode = Player(CurrentNode);
			if (CurrentNode->List == NULL) {
				printf("Congratulate, you win.\n");
				break;
			}
			CurrentNode = Bot(CurrentNode);
			if (CurrentNode->List == NULL) {
				printf("Sorry, you lost.\n");
				break;
			}
		}
		printf("Continue(y/n)?\n");
		conti = getchar(); getchar();
		if (conti == 'n') 
			break;
	}

	return 0;
}