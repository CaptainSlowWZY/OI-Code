#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>

#define fi first
#define se second
#define pb push_back

typedef std::pair<int, int> Pii;

const int kMod = 1e9 + 7;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1) if (ex & 1) res = Mul(res, bs);
	return res;
}

const int kMaxn = 17, kInv2 = 5e8 + 4, kInv4 = Mul(kInv2, kInv2), kNInv4 = Sub(0, kInv4);

struct Grp { int a, b, c; };

int n, m;
int l2g[(1 << 15) + 5];
std::vector<int> A[kMaxn];
std::vector<Grp> B[kMaxn], C[kMaxn];
std::map<Pii, int> prv, nxt;

inline int LowBit(int x) { return x & -x; }

int main() {
	scanf("%d%d", &n, &m);
	int U = (1 << n) - 1;
	for (int i = 0; i < n; ++i) l2g[1 << i] = i;
	for (int i = 0, t, a1, b1, a2, b2; i < m; ++i) {
		scanf("%d%d%d", &t, &a1, &b1); A[--a1].pb(--b1);
		if (t) {
			scanf("%d%d", &a2, &b2); A[--a2].pb(--b2);
			if (a1 == a2 || b1 == b2) continue;
			if (a1 > a2) { std::swap(a1, a2); std::swap(b1, b2); }
			if (t == 1) B[a1].pb({b1, a2, b2}); else C[a1].pb({b1, a2, b2});
		}
	} prv[{U, U}] = 1;
	int ans = 0;
	while (!prv.empty()) {
		nxt.clear();
		for (auto & p : prv) {
			int su = LowBit(p.fi.fi), u = l2g[su];
			for (auto i : A[u]) if (p.fi.se >> i & 1) Upa(nxt[{p.fi.fi ^ su, p.fi.se ^ 1 << i}], Mul(p.se, kInv2));
			for (auto & g : B[u]) if (p.fi.se >> g.a & 1 && p.fi.fi >> g.b & 1 && p.fi.se >> g.c & 1)
			   Upa(nxt[{p.fi.fi ^ su ^ 1 << g.b, p.fi.se ^ 1 << g.a ^ 1 << g.c}], Mul(p.se, kInv4));
			for (auto & g : C[u]) if (p.fi.se >> g.a & 1 && p.fi.fi >> g.b & 1 && p.fi.se >> g.c & 1)
			   Upa(nxt[{p.fi.fi ^ su ^ 1 << g.b, p.fi.se ^ 1 << g.a ^ 1 << g.c}], Mul(p.se, kNInv4));
		}
		if (nxt.count({0, 0})) { Upa(ans, nxt[{0, 0}]); nxt.erase({0, 0}); }
		std::swap(prv, nxt);
	}
	printf("%d\n", Mul(ans, FPow(2, n)));
	return 0;
}
