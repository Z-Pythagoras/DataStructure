#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int n, i, j, k, len, tmp;
	int arr[1005];

	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	for (i = 0; i < 3; i++) {
		for (len = n / 2; len >= 1; len--) {
			tmp = arr[len];
			for (k = 2 * len; k <= n;) {
				if (k < n && arr[k] < arr[k + 1])
					k++;
				if (tmp >= arr[k])
					k = n + 1;
				else {
					arr[len] = arr[k];
					len = k;
					k *= 2;
				}
			}
			arr[len] = tmp;
		}
		for (j = 1; j <= n; j++)
			printf("%d ", arr[j]);
		printf("\n");
		arr[1] = arr[n--];
	}

	return 0;
}