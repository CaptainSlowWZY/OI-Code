#include <cstdio>

int n, m;
int A[505][505], row[505], col[505], cnt;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			scanf("%d", A[i] + j);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0, Bi; j < m; j++) {
			scanf("%d", &Bi);
			A[i][j] ^= Bi;
			if (A[i][j]) {
				++row[i];
				++col[j];
				++cnt;
			}
		}
	}

	int fail = 0;
	if (cnt & 1) fail = 1;
	for (int i = 0; i < n; i++)
		if (row[i] & 1) fail = 1;
	for (int j = 0; j < m; j++)
		if (col[j] & 1) fail = 1;
	puts(fail ? "No" : "Yes");
	return 0;
}
