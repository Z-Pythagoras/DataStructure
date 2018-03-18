#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int num, link[1005];
}Point;

int vis[1005];
Point map[1005];

void Bfs(int x) {
	int i, j, cnt = 0, tmp[1005];

	if (!vis[x]) {
		vis[x] = 1;
		printf("%d", x);
	}
	for (i = 0; i < map[x].num; i++) 
		for (j = i; j < map[x].num; j++) 
			if (map[x].link[i] > map[x].link[j]) {
				map[x].link[i] = map[x].link[i] + map[x].link[j];
				map[x].link[j] = map[x].link[i] - map[x].link[j];
				map[x].link[i] = map[x].link[i] - map[x].link[j];
			}

	for (i = 0; i < map[x].num; i++)
		if (!vis[map[x].link[i]]) {
			printf("-%d", map[x].link[i]);
			vis[map[x].link[i]] = 1;
			tmp[cnt++] = map[x].link[i];
		}
	for (i = 0; i < cnt; i++)
		Bfs(tmp[i]);
}

int main() {
	int n, x, y, i;

	scanf("%d", &n);
	memset(vis, 0, sizeof(vis));
	memset(map, 0, sizeof(map));
	while (scanf("%d", &x) && x != -1) {
		scanf("%d", &y);
		map[x].link[map[x].num++] = y;
		map[y].link[map[y].num++] = x;
	}

	for (i = 0; i < n; i++)
		if (!vis[i]) {
			Bfs(i);
			printf("\n");
		}

	return 0;
}