#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int data, num;
}sheet;

int cmp(const void *p, const void *q) {
	return (*(sheet *)p).data >= (*(sheet *)q).data ? 1 : -1;
}

int main() {
	int t, key, low, high, mid, pos;
	int i;
	sheet list[1005];

	scanf("%d", &t);
	for (i = 0; i < t; i++)
		scanf("%d%d", &list[i].data, &list[i].num);
	scanf("%d", &key);

	qsort(list, t, sizeof(list[0]), cmp);
	for (i = 0; i < t; i++)
		printf("(%d %d)", list[i].data, list[i].num);
	printf("\n");

	low = 0; high = t - 1; pos = -1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (list[mid].data == key) {
			pos = mid;
			break;
		}
		else if (key > list[mid].data)
			low = mid + 1;
		else
			high = mid - 1;
	}
	if (pos == -1)
		printf("error\n");
	else
		printf("(%d %d)\n", list[pos].data, list[pos].num);

	return 0;
}