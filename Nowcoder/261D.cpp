#include <cstdio>

int n, m, k, x;

inline int Mul(int a, int b) { return 1ll * a * b % n; }
inline int Add(int a, int b) { return (a += b) >= n ? a - n : a; }

int main() {
	scanf("%d%d%d%d", &n, &m, &k, &x);

	int res = m % n, bs = 10;
	for (; k; bs = Mul(bs, bs), k >>= 1)
		if (k & 1) res = Mul(res, bs);
	printf("%d\n", Add(res, x));
	return 0;
}
