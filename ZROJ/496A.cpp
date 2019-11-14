#include <algorithm>
#include <cstdio>

#define fi first
#define se second

typedef std::pair<int, int> Pii;

const int kMod = 1e9 + 7;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }

long long n;
int len, num[70], F[70];
Pii G[70];

int Dfs1(int, int);
Pii Dfs2(int, int);

int main() {
	int t; scanf("%d", &t);
	while (t--) {
		scanf("%lld", &n);
		for (len = 0; n; n >>= 1) num[len++] = n & 1;
		std::reverse(num, num + len);
		for (int i = 0; i <= len; ++i) { F[i] = -1, G[i] = Pii(-1, -1); }
	//	for (int i = 0; i < len; ++i) printf("%d", num[i]); puts("");
		printf("%d\n", Dfs1(0, 1));
	} return 0;
}

// fi - ways, se - pop counts
Pii Dfs2(int u, int lim) {
	if (u == len) return Pii(1, 0);
	if (!lim && ~G[u].fi) return G[u];
	Pii res(0, 0);
	for (int i = lim ? num[u] : 1; ~i; --i) {
		Pii tmp = Dfs2(u + 1, lim && num[u] == i);
		Upa(res.fi, tmp.fi), Upa(res.se, Add(tmp.se, Mul(tmp.fi, i)));
	} return lim ? res : G[u] = res;
}

int Dfs1(int u, int lim) {
	if (u == len) return 0;
	if (!lim && ~F[u]) return F[u];
	int res = 0;
	if (!lim || lim && num[u]) {
		Pii lo = Dfs2(u + 1, 0), ro = Dfs2(u + 1, lim);
		Upa(ro.se, ro.fi);
		res = Add(Mul(lo.fi, ro.se), Mul(lo.se, ro.fi));	
	}
	for (int i = lim ? num[u] : 1; ~i; --i) Upa(res, Dfs1(u + 1, lim && i == num[u]));
	return lim ? res : F[u] = res;
}
