#include <cstdio>

const int kMaxn = 2e5 + 5, kMod = 998244353;

inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}
inline void Tag(int & a, int b) { a = Mul(a, b); }

int n, m;
int fa[kMaxn], W[kMaxn];

int Find(int x) {
	if (fa[x] == x) return x;
	int f = Find(fa[x]);
	if (f ^ fa[x]) Tag(W[x], W[fa[x]]);
	return fa[x] = f;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		fa[i] = i; W[i] = 1;
	}
	int frac13 = FPow(3), frac23 = Mul(2, frac13),
		pow3 = FPow(3, n);
	for (int o, u, v; m--; ) {
		scanf("%d%d", &o, &u);
		if (o == 1) {
			scanf("%d", &v);
			Tag(W[u], frac23);
			Tag(W[v], frac13);
			Tag(W[v], FPow(W[u]));
			fa[v] = u;
		} else {
			v = Find(u);
			int ans = Mul(pow3, W[u]);
			if (u ^ v) ans = Mul(ans, W[v]);
			printf("%d\n", ans);
		}
	} return 0;
}
