#include <cstdio>
#include <vector>

const int kMaxm = 1e4 + 5, kMaxv = 1e5 + 5, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upd(int & a, int b) { a = Sub(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

int n, m;
int fac[kMaxv], ifc[kMaxv];
std::vector<int> G[kMaxv];

inline int C(int n, int r) {
	return Mul(fac[n], Mul(ifc[r], ifc[n - r]));
}
int Dfs(int u);

int main() {
	scanf("%d", &m);
	int cnt[4] = {0, 0, 0, 0};
	for (int i = 0, n; i < m; ++i) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) G[i].clear();
		for (int j = 2, fa; j <= n; ++j) {
			scanf("%d", &fa); G[fa].push_back(j);
		} ++cnt[Dfs(1)];
	} int pwo = FPow(2, cnt[1] + cnt[2]),
		ans = FPow(2, m);
	for (int i = fac[0] = 1; i <= cnt[0]; ++i)
		fac[i] = Mul(fac[i - 1], i);
	ifc[cnt[0]] = FPow(fac[cnt[0]]);
	for (int i = cnt[0] - 1; i >= 0; --i)
		ifc[i] = Mul(ifc[i + 1], i + 1);
	for (int i = 0; i <= cnt[0]; i += 2) {
		Upd(ans, Mul(pwo, C(cnt[0], i)));
	} printf("%d\n", ans);
	return 0;
}

int Dfs(int u) {
	if (G[u].empty()) return 1;
	int cnt[4] = {0, 0, 0, 0};
	for (auto v : G[u]) ++cnt[Dfs(v)];
	if (cnt[0] && cnt[1] || cnt[3]) return 2;
	if (cnt[0]) return 1;
	if (cnt[1]) return 0;
	return 3;
}
