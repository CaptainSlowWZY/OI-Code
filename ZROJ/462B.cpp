#include <algorithm>
#include <cstdio>

const int kMaxn = 5005, kInf = 0x3f3f3f3f;

int n, F[kMaxn], H[kMaxn], mxh[kMaxn][kMaxn];
int DP[kMaxn][kMaxn][2];

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", F + i);
	for (int i = 1; i < n; ++i) scanf("%d", H + i);
	for (int i = 1; i < n; ++i) {
		mxh[i][i] = H[i];
		for (int j = i + 1; j < n; ++j)
			mxh[i][j] = std::max(mxh[i][j - 1], H[j]);
	}
	DP[1][n][0] = DP[1][n][1] = 0;
	for (int i = n - 1; i; --i) {
		for (int l = 1; l + i - 1 <= n; ++l) {
			int r = l + i - 1;
			DP[l][r][0] = DP[l][r][1] = kInf;
			if (l > 1) UMin(DP[l][r][0], H[l - 1] +
					std::max(DP[l - 1][r][0] - F[l - 1], 0));
			if (r < n) UMin(DP[l][r][1], H[r] +
					std::max(DP[l][r + 1][1] - F[r + 1], 0));
			UMin(DP[l][r][1], std::max(mxh[l][r - 1],
					DP[l][r][0]));
			UMin(DP[l][r][0], std::max(mxh[l][r - 1],
					DP[l][r][1]));
		}
	}		
	for (int i = 1; i <= n; ++i)
		printf("%d ", std::max(DP[i][i][0] - F[i], 0));
	putchar('\n'); return 0;
}
