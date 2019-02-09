// BZOJ 1019
#include <cstdio>

int N, g[3][35];
long long f[3][35];

int main() {
	scanf("%d", &N);
	char IN[5];
	for (int i = 0; i < 3; i++) f[i][1] = 1, g[i][1] = -1;
	for (int i = 0; i < 6; i++) {
		scanf("%s", IN);
		IN[0] -= 'A', IN[1] -= 'A';
		if (g[IN[0]][1] == -1) g[IN[0]][1] = IN[1];
	}

	for (int i = 2; i <= N; i++)
		for (int j = 0; j < 3; j++) {
			int a = g[j][i - 1], b = 3 - j - a;
			if (g[a][i - 1] == b) f[j][i] = f[j][i - 1] + f[a][i - 1] + 1, g[j][i] = b;
			else f[j][i] = 2LL * f[j][i - 1] + 2 + f[a][i - 1], g[j][i] = a;
		}
	printf("%lld\n", f[0][N]);
	return 0;
}
