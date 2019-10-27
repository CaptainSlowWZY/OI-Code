// SB duke
#include <cstdio>
#include <cstring>

#define pch putchar

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }

const int kLen = 4005, kInf = 0x3f3f3f3f;

int n, m;
int nxts[2][kLen], nxtt[2][kLen];
int DP[kLen][kLen], onp[kLen][kLen];
char S[kLen], T[kLen];

void GetNxt(char st[], int len, int (*nxt)[kLen]);

int main() {
	scanf("%d%d%s%s", &n, &m, S + 1, T + 1);
	GetNxt(S, n, nxts); GetNxt(T, m, nxtt);
	memset(DP, 0x3f, sizeof DP);
	DP[0][0] = 0;
	for (int i = 0; i <= n + 1; ++i) {
		for (int j = 0; j <= m + 1; ++j) {
			if (DP[i][j] == kInf) continue;
			for (int c = 0; c < 2; ++c) {
				int x = i <= n ? nxts[c][i + 1] : i,
					y = j <= m ? nxtt[c][j + 1] : j;
				UMin(DP[x][y], DP[i][j] + 1);
			}
		}
	} onp[n + 1][m + 1] = 1;
	for (int i = n + 1; i >= 0; --i) {
		for (int j = m + 1; j >= 0; --j) {
			if (DP[i][j] == kInf) continue;
			for (int c = 0; c < 2; ++c) {
				int x = i <= n ? nxts[c][i + 1] : i,
					y = j <= m ? nxtt[c][j + 1] : j;
				if (DP[i][j] + 1 == DP[x][y])
					onp[i][j] |= onp[x][y];
			}
		}
	}
	for (int i = 0, j = 0; i <= n || j <= m; ) {
		for (int c = 0; c < 2; ++c) {
			int x = i <= n ? nxts[c][i + 1] : i,
				y = j <= m ? nxtt[c][j + 1] : j;
			if (DP[i][j] + 1 == DP[x][y] && onp[x][y]) {
				pch('0' ^ c); i = x; j = y; break;
			}
		}
	} pch('\n');
	return 0;
}

void GetNxt(char st[], int len, int (*nxt)[kLen]) {
	nxt[0][len + 1] = nxt[1][len + 1] = len + 1;
	for (int i = len, c; i; --i) {
		nxt[c = st[i] ^ '0'][i] = i;
		nxt[c ^ 1][i] = nxt[c ^ 1][i + 1];
	}
}
