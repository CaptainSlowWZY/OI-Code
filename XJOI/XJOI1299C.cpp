#include <cstdio>
#include <cstring>

const int kLen = 1005, kMod = 123456789;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline void Upa(int & a, int b) { a = Add(a, b); }

char S[kLen];
int len, m, dp[kLen][kLen];

int Dfs(int p, int s, int l);

int main() {
	scanf("%s%d", S, &m);
	while (S[len]) S[len++] ^= '0';
	memset(dp, 0xff, sizeof dp);
	printf("%d\n", Sub(Dfs(0, 0, 1), 1));
	return 0;
}

int Dfs(int p, int s, int l) {
	if (p == len) return !s;
	if (~dp[p][s] && !l) return dp[p][s];
	int res = 0;
	for (int i = l ? S[p] : 9; ~i; --i) Upa(res, Dfs(p + 1, (s + i) % m, l && i == S[p]));
	return l ? res : (dp[p][s] = res);
}
