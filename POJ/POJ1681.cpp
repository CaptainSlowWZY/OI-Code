// POJ 1681
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXB = 230;
const int MAXN = 20;
const int DX[] = {-1, 0, 1, 0, 0};
const int DY[] = {0, 0, 0, -1, 1};

int N, totb, totu, A[MAXB][MAXB], id[MAXN][MAXN], ret[MAXB], unc[MAXB];
char S[10];

void solve();

int main() {
	int t;
	for (scanf("%d", &t); t--; ) solve();

	return 0;
}

void solve() {
	memset(A, 0, sizeof A);
	totb = totu = 0;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", S);
		for (int j = 0; j < N; j++) {
			A[totb][N * N] = S[j] == 'y' ? 0 : 1;
			id[i][j] = totb++;
		}
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < 5; k++) {
				int nx = i + DX[k], ny = j + DY[k];
				if (nx >= 0 && nx < N && ny >= 0 && ny < N) A[id[i][j]][id[nx][ny]] = 1;
			}

	// gauss
	for (int i = 0; i < totb; i++) {
		if (!A[i][i]) {
			for (int j = i + 1; j < totb; j++)
				if (A[j][i]) {
					for (int k = i; k <= totb; k++) std::swap(A[j][k], A[i][k]);
					break;
				}
		}
		if (A[i][i]) {
			for (int j = i + 1; j < totb; j++)
				if (A[j][i]) {
					for (int k = i; k <= totb; k++) A[j][k] ^= A[i][k];
				}
		}
		else unc[totu++] = i;
	}

	int ans = 500;
	for (int mask = (1 << totu) - 1; mask >= 0; --mask) {
		for (int i = 0; i < totu; i++) ret[unc[i]] = mask >> i & 1;
		int cnt = 0;
		for (int i = totb - 1; i >= 0; i--) {
			if (!A[i][i]) {
				int sum = 0;
				for (int j = i + 1; j < totb; j++) sum ^= A[i][j] & ret[j];
				if (sum ^ A[i][totb]) {
					cnt = 1000;
					break;
				}
				cnt += ret[i];
				continue;
			}
			ret[i] = A[i][totb];
			for (int j = i + 1; j < totb; j++) ret[i] ^= A[i][j] & ret[j];
			cnt += ret[i];
		}
		ans = std::min(ans, cnt);
	}

	if (ans == 500) puts("inf");
	else printf("%d\n", ans);
}
