#include <stdio.h>

const int inf = 0x3f3f3f3f;

typedef  struct {
	unsigned int weight;
	unsigned int parent, leftChild, rightChild;
}HTNode, *HuffmnTree;

HTNode hufmanTree[100005];

int main() {
	int n, m, i, j;
	int min1, min2, x1, x2, ans, cnt, tmp;

	scanf("%d", &n);
	m = 2 * n - 1;
	for (i = 1; i <= n; i++) {
		scanf("%d", &hufmanTree[i].weight);
		hufmanTree[i].parent = hufmanTree[i].leftChild = hufmanTree[i].rightChild = 0;
	}
	for (i = n + 1; i <= m; i++) {
		min1 = min2 = inf;
		for (j = 1; j < i; j++)
			if (hufmanTree[j].weight < min1 && !hufmanTree[j].parent) {
				min1 = hufmanTree[j].weight;
				x1 = j;
			}
		for (j = 1; j < i; j++)
			if (hufmanTree[j].weight < min2 && !hufmanTree[j].parent && j != x1) {
				min2 = hufmanTree[j].weight;
				x2 = j;
			}
		hufmanTree[x1].parent = hufmanTree[x2].parent = i;
		hufmanTree[i].leftChild = x1; hufmanTree[i].rightChild = x2; hufmanTree[i].parent = 0;
		hufmanTree[i].weight = hufmanTree[x1].weight + hufmanTree[x2].weight;
	}
	ans = 0;
	for (i = 1; i <= n; i++) {
		if (hufmanTree[i].parent) {
			tmp = hufmanTree[i].parent; cnt = 1;
			while (1) {
				if (hufmanTree[tmp].parent) {
					tmp = hufmanTree[tmp].parent;
					cnt++;
				}
				else 
					break;
			}
			ans += cnt * hufmanTree[i].weight;
		}
	}
	printf("WPL=%d\n", ans);

	return 0;
}