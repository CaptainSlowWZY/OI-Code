#include <cstdio>

int Gcd(int a, int b) { return b ? Gcd(b, a % b) : a; }

int main() {
	int t, n, m;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		printf("%d\n", Gcd(n - 1, m - 1) + 1);
	} return 0;
}
