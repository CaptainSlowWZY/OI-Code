#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
#include <vector>

#define se second
#define pb push_back
#define FORV(TP, I, _) for (std::vector<TP>::iterator I = _.begin(); I != _.end(); ++I)

const int kMaxn = 1e5 + 5, kMod = 998244353, kSize = 1299905;

typedef unsigned long long ULL;
typedef int Arr[kMaxn];

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Ups(int & a, int b) { a = Sub(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1) if (ex & 1) res = Mul(res, bs);
	return res;
}

int n, cntp, ans;
std::vector<int> G[kMaxn];
Arr sz, F, uf, fac, ifc;
int P[kMaxn + 20], np[kSize];
ULL ha[kMaxn], uha[kMaxn];
std::set<ULL> got;

void Solve();

int main() {
	int t, N = 1e5; scanf("%d", &t);
	for (int i = fac[0] = 1; i <= N; ++i) fac[i] = Mul(fac[i - 1], i);
	ifc[N] = FPow(fac[N]);
	for (int i = N - 1; ~i; --i) ifc[i] = Mul(ifc[i + 1], i + 1);
	N = 1299900;
	for (int i = 2; i <= N; ++i) {
		if (!np[i]) P[++cntp] = i;
		for (int j = 1, d; j <= cntp && (d = i * P[j]) <= N; ++j) {
			np[d] = 1;
			if (!(i % P[j])) continue;
		}
	}
	while (t--) Solve();
	return 0;
}

inline ULL Pack(ULL h, int sz) { return 2ull + 3ull * h + 7ull * P[sz + 1]; }

void Dfs1(int u, int fa) {
	ha[u] = sz[u] = F[u] = 1; FORV(int, v, G[u]) if (*v != fa) { Dfs1(*v, u); sz[u] += sz[*v], ha[u] += ha[*v] * P[sz[*v]], Upm(F[u], F[*v]); }
	static int son[kMaxn];
	int cnts = 0;
	FORV(int, v, G[u]) if (*v != fa) son[cnts++] = ha[*v];
	std::sort(son, son + cnts); Upm(F[u], fac[cnts]); son[cnts] = -1;
	for (int i = 0, la = 0; i <= cnts; ++i) if (son[i] != son[la]) { Upm(F[u], ifc[i - la]), la = i; }
	ha[u] = Pack(ha[u], sz[u]);
//	printf(" ha[%d] = %llu\n", u, ha[u]);
}

void Dfs2(int u, int fa) {
	ULL sha = 1 + uha[u] * P[n - sz[u]];
//	printf(" uha[%d] = %llu, uf %d, myh %llu\n", u, uha[u], uf[u], sha);
	int prd = uf[u], cnts = 0;
	static std::map<ULL, int> cnt;
	cnt.clear();
	FORV(int, v, G[u]) if (*v != fa) { ++cnts, sha += ha[*v] * P[sz[*v]], Upm(prd, F[*v]), ++cnt[ha[*v]]; }
	if (u != 1) { Upm(prd, fac[cnts]), ++cnt[uha[u]]; }
	else Upm(prd, fac[cnts - 1]);
	for (std::map<ULL, int>::iterator p = cnt.begin(); p != cnt.end(); ++p) Upm(prd, ifc[p->se]);
//	printf("  prd = %d\n", prd);
	FORV(int, v, G[u]) if (*v != fa) {
	//	printf("   %d as root, hash %llu\n", *v, sha - ha[*v] * P[sz[*v]]);
		uha[*v] = Pack(sha - ha[*v] * P[sz[*v]], n - sz[*v]), uf[*v] = Mul(prd, Mul(cnt[ha[*v]], FPow(F[*v])));
	}
	FORV(int, v, G[u]) if (*v != fa) Dfs2(*v, u);
//	printf(" !u %d, myh %llu, way %d\n", u, Pack(sha, n), Mul(prd, cnts + 1));
	if (u > 1 && !got.count(sha = Pack(sha, n))) { Upa(ans, Mul(prd, cnts + 1)); got.insert(sha); }
}

void Solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) G[i].clear();
	for (int i = 1, x, y; i < n; ++i) { scanf("%d%d", &x, &y); G[x].pb(y); G[y].pb(x); }
	Dfs1(1, 0); got.clear(), got.insert(ha[1]); ans = F[1];
//	printf(" hart %llu, F[1] = %d\n", ha[1], ans);
	Dfs2(uf[1] = 1, 0); printf("%d\n", ans);
}
