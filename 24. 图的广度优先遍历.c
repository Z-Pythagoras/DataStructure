#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	char data;
	int link[1005], len;
}AdList;

AdList map[1005];
int vis[1005];

void bfs(int num) {
	int k, cnnt = 0, tmp[1005] = { 0 };
	if (!vis[num]) {
		printf("%c", map[num].data);
		vis[num] = 1;
	}
	for (k = map[num].len - 1; k >= 0; k--) 
		if (!vis[map[num].link[k]]) {
			printf("%c", map[map[num].link[k]].data);
			vis[map[num].link[k]] = 1;
			tmp[cnnt++] = map[num].link[k];
		}
	for (k = 0; k < cnnt; k++)
		bfs(tmp[k]);
}

int main() {
	char ch;
	int x, y, i, j, cnt = 0;

	while (scanf("%c", &ch) && ch != '*') {
		map[cnt++].data = ch; getchar();
		map[cnt].len = 0;
	}
	while (scanf("%d,%d", &x, &y) && x != -1) {
		map[x].link[map[x].len++] = y;
		map[y].link[map[y].len++] = x;
	}
	printf("the ALGraph is\n");
	for (i = 0; i < cnt; i++) {
		printf("%c", map[i].data);
		for (j = map[i].len - 1; j >= 0; j--)
			printf(" %d", map[i].link[j]);
		printf("\n");
	}
	memset(vis, 0, sizeof(vis));
	printf("the Breadth-First-Seacrh list:");
	for (i = 0; i < cnt; i++)
		if (!vis[i])
			bfs(i);
	printf("\n");

	return 0;
}