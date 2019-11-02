#include <algorithm>
#include <cstdio>

const int kMaxn = 1e3 + 5, kMod = 998244353;

typedef int Arr[kMaxn];

Arr fac, ifc, pw, num, DP[kMaxn], _g[kMaxn];

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
inline int Inv(int a) { return Mul(ifc[a], fac[a - 1]); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

int n, m, k, ans, ar;

void Dfs(int, int, int);

int main() {
	scanf("%d%d%d", &n, &m, &k);
	if (n > m) std::swap(n, m); ar = n * m;
	for (int i = fac[0] = pw[0] = 1; i <= ar; ++i) {
		fac[i] = Mul(fac[i - 1], i); pw[i] = Mul(pw[i - 1], k);
	} ifc[ar] = FPow(fac[ar]);
	for (int i = ar - 1; ~i; --i) ifc[i] = Mul(ifc[i + 1], i + 1);
	for (int i = 1; i <= m; ++i) {
		for (int j = i; j <= m; ++j)
			_g[i][j] = _g[j][i] = std::__gcd(i, j);
	} Dfs(n, n, 0); printf("%d\n", Mul(Mul(ifc[n], ifc[m]), ans));
	return 0;
}

void Gao(int la) {
	int res = fac[n], cur = num[la] = 0;
	for (int i = 1; i <= la; ++i) {
		Upm(res, Inv(num[i - 1]));
		if (num[i] == num[cur]) continue;
		Upm(res, ifc[i - cur]), cur = i;
	}
	for (int i = 0; i <= m; ++i)
		for (int j = 0; j <= m; ++j) DP[i][j] = 0;
	DP[m][m] = 1;
	for (int i = m, alp; ~i; --i) {
		for (int j = m; j; --j) if (DP[i][j]) {
			for (int k = alp = 0; k < la; ++k)
				alp += _g[j][num[k]];
			cur = DP[i][j];
			for (int k = 0; k * j <= i; ++k) {
				Upa(DP[i - k * j][j - 1], Mul(cur, ifc[k]));
				Upm(cur, Mul(Inv(j), pw[alp]));
			}
		}
	} Upa(ans, Mul(res, Mul(DP[0][0], fac[m])));
}

void Dfs(int x, int y, int d) {
	if (!x) return Gao(d); if (!y) return; Dfs(x, y - 1, d);
	if (x >= y) { num[d++] = y; Dfs(x - y, y, d); }
}
