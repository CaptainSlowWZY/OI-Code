#include <cstdio>

int n, A[105], id[105];

int main() {
	scanf("%d", &n);
	int sum = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", A + i);
		sum += A[i];
	}

	int k = 1, have = A[0];
	id[0] = 1;
	for (int i = 1; i < n; i++) {
		if (A[0] < A[i] * 2) continue;
		have += A[i], id[k++] = i + 1;
	}
	if (have > sum / 2) {
		printf("%d\n", k);
		for (int i = 0; i < k; i++) printf("%d ", id[i]);
		putchar('\n');
	} else puts("0");
	return 0;
}
