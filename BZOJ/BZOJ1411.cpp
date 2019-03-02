#include <cstdio>
#include <algorithm>

const int kMaxn = 1e5 + 10;

int n, A[2][kMaxn], ans[kMaxn << 1];
long long T;

inline int Id(long long x) {
	return (x % n + n) % n;
}

int main() {
	scanf("%d%lld", &n, &T);
	for (int i = 0; i < n; i++) {
		scanf("%d", &A[0][i]);
		--A[0][i];
	}

	int *prv = A[0], *nxt = A[1];
	for (int i = 1; i <= 60; i++)
		if (T >> i & 1) {
			for (int j = 0; j < n; j++)
				nxt[j] = prv[Id(j - (1LL << i - 1))] ^ prv[Id(j + (1LL << i - 1))];
			std::swap(nxt, prv);
		}
	if (T & 1) {
		for (int i = 0; i < n; i++)
			ans[i * 2 + 1] = (prv[i] ^ prv[Id(i + 1)]) + 1;
	}
	else {
		for (int i = 0; i < n; i++)
			ans[i << 1] = prv[i] + 1;
	}

	for (int i = 0; i < n * 2; i++) printf("%d ", ans[i]);
	putchar('\n');
	return 0;
}
