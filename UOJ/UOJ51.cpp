#include <cmath>
#include <cstdio>
#include <cstring>

const int kRt =	31625, kLg = 31;
int n, m, ex[kRt], P[kRt][kLg];

int main() {
	scanf("%d%d", &n, &m);	
	int rt = floor(sqrt(n + 0.5));
	memset(P, 1, sizeof P);
	for (int i = rt; i > 1; --i) {
		for (int pw = 1; n / i >= pw; pw *= i, ++ex[i]);
		for (int j = ex[i]; j; --j) P[i][j] = !P[i + 1][j] || !P[i][j + 1];
	}
	for (int a, b; m--; ) {
		scanf("%d%d", &a, &b);
		if (b == 1 && a > rt) { puts(n - a & 1 ? "Yes" : "No"); continue; }
		if (a > rt || b > ex[a]) { puts("No"); continue; }
		puts(P[a][b] ? "Yes" : "No");
	} return 0;
}
