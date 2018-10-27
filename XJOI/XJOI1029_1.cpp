// XJOI 1029 1
#include <cstdio>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif

typedef long double real;
typedef real arr[60][2600];

arr f, g;
int a, b, c, d;

void dp(real DP[][2600], int n, int m) {
	DP[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= i * m; j++)
		   for (int k = 1; k <= m && k <= j; k++) DP[i][j] += DP[i - 1][j - k];
}

int main() {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	
	if (a * b <= c) return puts("-1"), 0;
	dp(f, a, b);
	dp(g, c, d);
	real tot = 0, totway = 0; 
	for (int i = a; i <= a * b; i++)
		for (int j = c; j < i && j <= c * d; j++) tot += i * f[a][i] * g[c][j], totway += f[a][i] * g[c][j];

	debug("tot=%.10Lf, totway=%.10Lf\n", tot, totway);
	printf("%.10Lf\n", tot / totway);
	return 0;
}

// AC!!!
