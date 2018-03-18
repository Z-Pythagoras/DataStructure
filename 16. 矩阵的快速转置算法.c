#include <stdio.h>
#include <string.h>

typedef struct {
	int i, j, e;
}Trip;

typedef struct {
	Trip data[1000];
	int mu, nu, tu;
}Matrix;

int main() {
	int num[100], cpot[100], col, t, p, q;
	Matrix M, T;

	scanf("%d%d%d", &M.mu, &M.nu, &M.tu);
	for (int k = 1; k <= M.tu; k++)
		scanf("%d%d%d", &M.data[k].i, &M.data[k].j, &M.data[k].e);
	T.mu = M.mu; T.nu = M.nu; T.tu = M.tu;

	if (T.tu) {
		for (col = 1; col <= M.nu; col++)
			num[col] = 0;
		for (t = 1; t <= M.tu; t++)
			num[M.data[t].j]++;
		cpot[0] = cpot[1] = 1;
		for (col = 2; col <= M.nu; col++)
			cpot[col] = cpot[col - 1] + num[col - 1];
		for (p = 1; p <= M.tu; p++) {
			col = M.data[p].j;
			q = cpot[col];
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			cpot[col]++;
		}
	}

	printf("num:");
	for (int k = 1; k <= M.nu; k++)
		printf("%d,", num[k]);
	printf("\n");
	printf("cpot:");
	for (int k = 0; k < M.nu; k++)
		printf("%d,", cpot[k]);
	printf("\n");
	for (int k = 1; k <= M.tu; k++)
		printf("%d,%d,%d\n", T.data[k].i, T.data[k].j, T.data[k].e);

	return 0;
}