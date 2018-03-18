#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int x, y;
}SS;

SS stack[210];
int map[105][105], mx[4] = { 1,0,-1,0 }, my[4] = { 0,1,0,-1 };
int top;

void push(int a, int b) {
	stack[top].x = a; stack[top++].y = b;
	map[a][b] = 1;
}

int main() {
	int m, n, xx, yy, flag;
	scanf("%d%d", &m, &n);
	for (int i = 0; i <= m + 1; i++)
		for (int j = 0; j <= n + 1; j++)
			map[i][j] = 1;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &map[i][j]);
	if (map[1][1]) {
		printf("There is no solution!\n");
		return 0;
	}
	top = 0; 
	push(1, 1);
	while (1) {
		flag = 1;
		if (!top) {
			printf("There is no solution!\n");
			return 0;
		}
		xx = stack[top - 1].x; yy = stack[top - 1].y;
		if (xx == m && yy == n)
			break;
		for (int k = 0; k < 4; k++)
			if (!map[xx + mx[k]][yy + my[k]]) {
				push(xx + mx[k], yy + my[k]);
				flag = 0;
				break;
			}
		if(flag)
			top--;
	}
	for (int k = 0; k < top; k++)
		printf("<%d,%d> ", stack[k].x, stack[k].y);
	printf("\n");
	return 0;
}