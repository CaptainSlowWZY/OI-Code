#include <algorithm>
#include <cctype>
#include <cstdio>
#include <vector>

#define pb push_back
#define gch getchar
#define CNT __builtin_popcount

const int kMaxn = 23, kMod = 998244353, kU = (1 << 21) + 5;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upd(int & a, int b) { a = Add(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

int n, m, p, u;
int W[kMaxn], sum[kU], G[kMaxn], fa[kMaxn];
int F[kMaxn][kU], DP[kMaxn][kU];

namespace fast_io {
	template <typename T> inline void Read(T & x);
}
bool Euler(int s);
void Fmt(int ar[], int (*Opr)(int, int));

int main() {
	using fast_io::Read;
	Read(n); Read(m); Read(p);
	for (int u, v; m--; ) {
		Read(u); Read(v);
		G[--u] |= 1 << --v; G[v] |= 1 << u;
	}
	for (int i = 0; i < n; ++i) Read(W[i]);

	u = (1 << n) - 1;
	for (int s = 1; s <= u; ++s) {
		if (!p) { sum[s] = 1; continue; }
		for (int i = 0; i < n; ++i)
			if (s >> i & 1) {
				sum[s] = Add(sum[s ^ 1 << i], W[i]);
				break;
			}
	}
	for (int s = 0, sz; s <= u; ++s) {
		if (p > 1) sum[s] = Mul(sum[s], sum[s]);
		F[sz = CNT(s)][s] = Euler(s);
		if (F[sz][s]) F[sz][s] = sum[s];
//		printf(" F[%d][%d] %d\n", sz, s, F[sz][s]);
		sum[s] = FPow(sum[s]);
	}
	for (int i = 0; i <= n; ++i) Fmt(F[i], Add);
	DP[0][0] = 1; Fmt(DP[0], Add);
	for (int i = 1; i <= n; ++i) {
		int *cur = DP[i];
		for (int j = 0; j < i; ++j) {
			int *a = DP[j], *b = F[i - j];
			for (int s = 0; s <= u; ++s)
				Upd(cur[s], Mul(a[s], b[s]));
		} Fmt(cur, Sub);
		for (int s = 0; s <= u; ++s)
			cur[s] = Mul(cur[s], CNT(s) == i ? sum[s] : 0);
		if (i < n) Fmt(cur, Add);
	} printf("%d\n", DP[n][u]);
	return 0;
}

inline int Find(int x) { return fa[x] == x ? x : (fa[x] = Find(fa[x])); }

inline void Merge(int u, int v) { fa[Find(u)] = Find(v); }

bool Euler(int s) {
	if (CNT(s) == 1 || !s) return false;
	std::vector<int> V;
	for (int i = 0; i < n; ++i)
		if (s >> i & 1) { V.pb(i); fa[i] = i; }
	for (auto u : V) {
		int deg = 0;
		for (auto v : V) {
			if (G[u] >> v & 1) {
				Merge(u, v); ++deg;
			}
		} if (deg & 1) return true;
	} int cnt = 0;
	for (auto u : V) cnt += fa[u] == u;
	return cnt > 1;
}

void Fmt(int ar[], int (*Opr)(int, int)) {
	for (int i = 0; i < n; ++i)
		for (int s = 0; s <= u; ++s)
			if (s >> i & 1) ar[s] = Opr(ar[s], ar[s ^ 1 << i]);
}

namespace fast_io {
	template <typename T> inline
		void Read(T & x) {
			char ch = gch();
			for (x = 0; !isdigit(ch); ch = gch());
			for (; isdigit(ch); ch = gch())
				x = (x << 1) + (x << 3) + (ch ^ '0');
		}
}
