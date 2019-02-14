// SPOJ
// HIGH - Highways
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

const double EPS = 1e-8;

int N, E;
double A[15][15];

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		memset(A, 0, sizeof A);
		scanf("%d%d", &N, &E);
		for (int u, v; E--; ) {
			scanf("%d%d", &u, &v);
			--u, --v;
			++A[u][u], ++A[v][v], --A[u][v], --A[v][u];
		}

		int con = 0;
		--N;
		for (int i = 0; i < N; i++) {
			int r = i;
			for (int j = i + 1; j < N; j++)
				if (fabs(A[j][i]) > fabs(A[r][i])) r = j;
			if (fabs(A[r][i]) < EPS) {
				puts("0");
				con = 1;
				break;
			}
			if (r != i) {
				for (int j = i; j < N; j++) std::swap(A[r][j], A[i][j]);
			}
			for (int j = N - 1; j >= i; j--)
				for (int k = i + 1; k < N; k++)
					A[k][j] -= A[k][i] / A[i][i] * A[i][j];
		}
		if (con) continue;
		
		double ans = 1;
		for (int i = 0; i < N; i++) ans *= A[i][i];

		printf("%.0lf\n", fabs(ans));
	}
	
	return 0;
}
