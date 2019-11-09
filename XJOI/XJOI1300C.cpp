#include <cstdio>
#include <vector>

#define pb push_back
#define FORV(I, _) for (std::vector<int>::iterator I = _.begin(); I != _.end(); ++I)

const int kMaxn = 1005, kMod = 998244353;

typedef int Arr[kMaxn];

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Ups(int & a, int b) { a = Sub(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

int n, m, S, invs;
Arr P[kMaxn], ifc, fac, sz, cnt;
std::vector<int> G[kMaxn];

inline int C(int n, int r) { return Mul(fac[n], Mul(ifc[r], ifc[n - r])); }
int Dfs(int);

int main() {
#ifndef ACLY
	freopen("techtree.in", "r", stdin);
	freopen("techtree.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for (int fa, i = 2; i <= n; ++i) { scanf("%d", &fa); G[fa].pb(i); }
	for (int i = fac[0] = 1; i <= n; ++i) { S += G[i].empty(); fac[i] = Mul(fac[i - 1], i); }
	invs = FPow(S), ifc[n] = FPow(fac[n]);
	for (int i = n - 1; ~i; --i) ifc[i] = Mul(ifc[i + 1], i + 1);
	Dfs(1);
	int ans = 0;
	for (int i = 1; i <= n; ++i) Upa(ans, P[1][i]);
	printf("%d\n", Mul(ans, invs)); 
#ifndef ACLY
	fclose(stdin); fclose(stdout); 
#endif
	return 0;
}

int Dfs(int u) {
	if (G[u].empty()) {
		cnt[u] = sz[u] = 1, P[u][0] = 1; //P[u][1] = u == m ? invs : 0;
		return u == m;
	}
	static int nxt[kMaxn];
	int rt = 0, t;
	P[u][0] = 1;
	FORV(v, G[u]) {
		t = Dfs(*v);
		for (int i = 0; i <= sz[u] + sz[*v]; ++i) nxt[i] = 0;
		for (int i = 0; i <= sz[u]; ++i)
			for (int j = 0; j <= sz[*v]; ++j)
				Upa(nxt[i + j], Mul(Mul(P[u][i], P[*v][j]), C(i + j, i)));
		rt |= t, sz[u] += sz[*v], cnt[u] += cnt[*v];
		for (int i = 0; i <= sz[u]; ++i) P[u][i] = nxt[i];
	}
	for (int q = Mul(cnt[u], invs), i = sz[u]++; ~i; --i) P[u][i + 1] = Mul(q, P[u][i]);
	P[u][0] = !rt;
	return rt;
}
