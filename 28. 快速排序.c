#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  

#define maxn 1005

int mid3[maxn], cnt = 0;

void Median3(int list[], int low, int high) {
	int mid = (low + high) / 2;

	if (list[low] > list[mid]) {
		int tmp = list[low]; list[low] = list[mid]; list[mid] = tmp;
	}
	if (list[low] > list[high]) {
		int tmp = list[low]; list[low] = list[high]; list[high] = tmp;
	}
	if (list[mid] > list[high]) {
		int tmp = list[mid]; list[mid] = list[high]; list[high] = tmp;
	}
	int tmp = list[mid]; list[mid] = list[high - 1]; list[high - 1] = tmp;

	mid3[cnt++] = list[high - 1];
}

void InsertSort(int list[], int low, int high) {
	int tmp;

	for (low = 2; low <= high; low++) {
		list[0] = list[low];
		tmp = low - 1;
		while (list[0]<list[tmp]) {
			list[tmp + 1] = list[tmp];
			tmp--;
		}
		list[tmp + 1] = list[0];
	}
}

void QuickSort(int list[], int low, int high) {
	int i, j, tmp;

	Median3(list, low, high);
	i = low;
	j = high - 1;
	int x = list[j];
	while (1) {
		while (list[++i] < x);
		while (list[--j] > x);
		if (i < j) {
			tmp = list[i]; list[i] = list[j]; list[j] = tmp;
		}
		else break;
	}
	list[high - 1] = list[i]; list[i] = x;
	if (low + 5 <= i)
		QuickSort(list, low, i - 1);
	else
		InsertSort(list, low, i - 1);
	if (i + 5 <= high)
		QuickSort(list, i + 1, high);
	else
		InsertSort(list, i + 1, high);
}

int main() {
	char str[20];
	int i = 1, j = 1, k = 0, num[maxn];

	while (1) {
		scanf("%s", str);
		if (strcmp(str, "#") == 0)
			break;
		num[i++] = atoi(str);
	}
	
	if (i - 1 > 5)
		QuickSort(num, 1, i - 1);
	else
		InsertSort(num, 1, i - 1);
	printf("After Sorting:\n");
	while (j < i) {
		printf("%d ", num[j]);
		j++;
	}

	printf("\nMedian3 Value:\n");
	if (cnt) {
		while (k < cnt)
			printf("%d ", mid3[k++]);
		printf("\n");
	}
	else
		printf("none\n");

	return 0;
}