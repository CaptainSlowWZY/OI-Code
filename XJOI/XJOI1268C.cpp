#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long LL;

const int kMod = 1e9 + 7;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }

const int kMaxn = 5e4 + 5, kMaxm = 25;

int n, q, lenm, ans;
int nxt[kMaxm];
char M[kMaxm], S[kMaxn];
LL DP[kMaxn][kMaxm][2];

void Gao(int x, int c, int mat, LL k);
LL Dfs(int x, int c, int mat);

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%s%s", &n, &q, M, S);
		nxt[0] = nxt[1] = 0, lenm = strlen(M);
		for (int i = 0; i < lenm; ++i) M[i] ^= '0';
		M[lenm] = 12;
		for (int i = 0; i < n; ++i)
			if (S[i] != '?') S[i] ^= '0';
		for (int i = 1, j; i < lenm; ++i) {
			for (j = nxt[i]; j && M[j] != M[i]; j = nxt[j]);
			nxt[i + 1] = M[j] == M[i] ? j + 1 : 0;
		}
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= lenm; ++j)
				DP[i][j][0] = DP[i][j][1] = -1;
	//	printf(" Dfs(0, 0, 0)%lld\n", Dfs(0, 0, 0));
		DP[0][0][0] = Dfs(0, 0, 0);
		for (LL k; q--; ) {
			scanf("%lld", &k);
			if (k > DP[0][0][0]) { puts("-1"); continue; }
			ans = 0; Gao(0, 0, 0, k);
			printf("%d\n", ans);
		}
	} return 0;
}

void Gao(int x, int c, int mat, LL k) {
	if (x == n) return;
	if (S[x] != '?') {
		while (c && S[x] != M[c]) c = nxt[c];
		if (S[x] == M[c]) ++c;
	//	printf(" posite %d, at %d\n", S[x], x);
		ans = Add(Mul(ans, 10), S[x]);
		Gao(x + 1, c, mat || c == lenm, k);
		return;
	}
	for (int i = x ? 0 : 1, j; i <= 9; ++i) {
		for (j = c; j && i != M[j]; j = nxt[j]);
		if (i == M[j]) ++j;
		LL nxt = Dfs(x + 1, j, mat || j == lenm);
	//	printf("   if choose %d, at %d; have %lld, k %lld\n", i, x, nxt, k);
		if (nxt >= k) {
			ans = Add(Mul(ans, 10), i);
		//	printf(" choose %d, at %d\n", i, x);
			Gao(x + 1, j, mat || j == lenm, k);
			return;
		} else k -= nxt;
	}
}

#define CUR [x][c][mat]

LL Dfs(int x, int c, int mat) {
	if (x == n) return mat;
	if (S[x] != '?') {
		while (c && S[x] != M[c]) c = nxt[c];
		if (S[x] == M[c]) ++c;
		return Dfs(x + 1, c, mat || c == lenm);
	}
	if (~DP CUR) return DP CUR;
	DP CUR = 0, son CUR[0] = -1, ;
	for (int i = x ? 0 : 1, j; i <= 9; ++i) {
		for (j = c; j && i != M[j]; j = nxt[j]);
		if (i == M[j]) ++j;
		LL tmp = Dfs(x + 1, j, mat || j == lenm);
		if (DP CUR > kInf64 - tmp) break;
		if (son CUR == -1 || tmp > 
		DP CUR += tmp;
	}
	return DP CUR;
}
