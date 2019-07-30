#include <algorithm>
#include <cstdio>

typedef long long LL;

const int kMod = 1e9;
const int kDx[] = {1, 0}, kDy[] = {0, 1};

int n, m, index;
LL M[85][85];
int id[9][9];
char A[9][12];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", A[i]);
		for (int j = 0; j < m; j++) {
			if (A[i][j] == '*') id[i][j] = -1;
			else id[i][j] = index++;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0, u; j < m; j++) {
			if ((u = id[i][j]) == -1) continue;
			for (int x, y, v, k = 0; k < 2; k++) {
				x = i + kDx[k], y = j + kDy[k];
				if (x < 0 || x >= n || y < 0 || y >= m) continue;
				if ((v = id[x][y]) == -1) continue;
				++M[u][u], ++M[v][v];
				--M[u][v], --M[v][u];
			}
		}
	}

	int N = index - 1, rev = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			int r1 = i, r2 = j;
			for (LL t; M[r2][i]; std::swap(r1, r2)) {
				t = M[r1][i] / M[r2][i];
				for (int k = 0; k < N; k++)
					(M[r1][k] -= M[r2][k] * t % kMod) %= kMod;
			}
			if (r1 ^ i) {
				rev ^= 1;
				for (int k = 0; k < N; k++)
					std::swap(M[r1][k], M[i][k]);
			}
		}
	}
	long long ans = 1;
	for (int i = 0; i < N; i++) (ans *= M[i][i]) %= kMod;
	if (rev) ans = -ans;
	(ans += kMod) %= kMod;
	printf("%lld\n", ans);
	return 0;
}
