#include <stdio.h>
#include <string.h>

typedef struct {
	int i, j, e;
}Trip;

typedef struct {
	Trip data[1000];
	int rpos[1000];
	int mu, nu, tu;
}Matrix;

int main() {
	int arow, brow, col, qcc, tp, p, t, q;
	int ctemp[1000], num[1000];
	Matrix A, B, Q;

	scanf("%d%d%d", &A.mu, &A.nu, &A.tu);
	for (int k = 1; k <= A.tu; k++)
		scanf("%d%d%d", &A.data[k].i, &A.data[k].j, &A.data[k].e);

	scanf("%d%d%d", &B.mu, &B.nu, &B.tu);
	for (int k = 1; k <= B.tu; k++)
		scanf("%d%d%d", &B.data[k].i, &B.data[k].j, &B.data[k].e);

	for (col = 1; col <= A.mu; col++)
		num[col] = 0;
	for (int k = 1; k <= A.tu; k++)
		num[A.data[k].i]++;
	A.rpos[1] = 1;
	for (col = 2; col <= A.mu; col++)
		A.rpos[col] = A.rpos[col - 1] + num[col - 1];

	for (col = 1; col <= B.mu; col++)
		num[col] = 0;
	for (int k = 1; k <= B.tu; k++)
		num[B.data[k].i]++;
	B.rpos[1] = 1;
	for (col = 2; col <= B.mu; col++)
		B.rpos[col] = B.rpos[col - 1] + num[col - 1];

	Q.mu = A.mu; Q.nu = B.nu; Q.tu = 0;
	if (A.tu * B.tu)
		for (arow = 1; arow <= A.mu; arow++) {
			memset(ctemp, 0, sizeof(ctemp));
			Q.rpos[arow] = Q.tu + 1;
			if (arow < A.mu)
				tp = A.rpos[arow + 1];
			else
				tp = A.tu + 1;
			for (p = A.rpos[arow]; p < tp; p++) {
				brow = A.data[p].j;
				if (brow < B.mu)
					t = B.rpos[brow + 1];
				else
					t = B.tu + 1;
				for (q = B.rpos[brow]; q < t; q++) {
					qcc = B.data[q].j;
					ctemp[qcc] += A.data[p].e * B.data[q].e;
				}
			}

			for (qcc = 1; qcc <= Q.nu; qcc++)
				if (ctemp[qcc]) {
					Q.tu++;
					Q.data[Q.tu].i = arow;
					Q.data[Q.tu].j = qcc;
					Q.data[Q.tu].e = ctemp[qcc];
				}
		}

	printf("%d\n%d\n%d\n", Q.mu, Q.nu, Q.tu);
	for (int k = 1; k <= Q.tu; k++)
		printf("%d,%d,%d\n", Q.data[k].i, Q.data[k].j, Q.data[k].e);

	return 0;
}