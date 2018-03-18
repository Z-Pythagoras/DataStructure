#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int point, weight;
}line;

typedef struct {
	char data[20];
	line link[1005];
	int in, out;
}AdList;

AdList map[1005];

int q, p, list[1005], ans[1005];

void TopoSort() {
	int now, tmp, i, j;
	if (!q) return;
	else {
		now = list[q]; ans[++p] = list[q--];
		for (i = 0; i<map[now].out; i++) {
			map[map[now].link[i].point].in--;
			if (!map[map[now].link[i].point].in)
				list[++q] = map[now].link[i].point;
		}
		for (i = 1; i <= q; i++)
			for (j = i; j <= q; j++)
				if (list[j]>list[i]) {
					tmp = list[i];
					list[i] = list[j];
					list[j] = tmp;
			}
		TopoSort();
	}
}

int maxn, cnt, start;
char  road[1005][5005];

void CPM(char lastroad[1005], int cout, int now) {
	char tmp[1005];
	int i;
	strcpy(tmp, lastroad);
	if (now != start)
		strcat(tmp, "-");
	strcat(tmp, map[now].data);
	if (cout > maxn) {
		maxn = cout;
		cnt = 1;
		strcpy(road[cnt], tmp);
	}
	else if (cout == maxn) 
		strcpy(road[++cnt], tmp);
	for (i = 0; i<map[now].out; i++)
		CPM(tmp, cout + map[now].link[i].weight, map[now].link[i].point);
}

int main() {
	char ch;
	int m, n, x, y, w, i, j, k, tmp;
	memset(map, 0, sizeof(map));
	scanf("%d,%d", &m, &n); getchar();
	for (i = 0; i < m; i++)
		for (j = 0, ch = getchar();ch != ',' && ch != '\n'; j++) {
			map[i].data[j] = ch;
			ch = getchar();
		}
	for (i = 0; i < n; i++) {
		if (i) getchar();
		scanf("<%d,%d,%d>", &x, &y, &w);
		map[x].link[map[x].out].point = y;
		map[x].link[map[x].out].weight = w;
		map[x].out++; map[y].in++;
	}
	for (i = 0; i < m; i++)
		for (j = 0; j < map[i].out; j++)
			for (k = j; k < map[i].out; k++)
				if (map[i].link[j].point > map[i].link[k].point) {
					tmp = map[i].link[j].point;
					map[i].link[j].point = map[i].link[k].point;
					map[i].link[k].point = tmp;
					tmp = map[i].link[j].weight;
					map[i].link[j].weight = map[i].link[k].weight;
					map[i].link[k].weight = tmp;
				}

	q = p = 0;
	for (i = 0; i < m; i++)
		if (!map[i].in)
			list[++q] = i;
	TopoSort();

	if (p == m) {
		printf("%s", map[ans[1]].data);
		for (i = 2; i <= p; i++)
			printf("-%s", map[ans[i]].data);
		printf("\n");
		start = ans[1];
		CPM("", 0, start);
		for (i = 1; i <= cnt; i++)
			printf("%s\n", road[i]);
	}
	else
		printf("NO TOPOLOGICAL PATH\n");

	return 0;
}