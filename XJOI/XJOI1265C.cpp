#include <cassert>
#include <cstdio>
#include <queue>
#include <vector>

#define pb push_back

const int kMaxn = 1e5 + 5;

typedef long long LL;
typedef int IAr[kMaxn];

struct Monster {
	LL a, b; int id, t, tg;
	void set() { t = a < b; }
	bool operator<(const Monster & m) const {
		return t != m.t ? t < m.t : (t ?
			(a > m.a) : (b < m.b));
	}
/*	bool operator!=(const Monster & m) const {
		return a != m.a || b != m.b || t != m.t;
	} */
	void operator+=(const Monster & m) {
		LL t = a;
		a = std::max(a, a + m.a - b);
		b = a + b + m.b - (m.a + t);
	}
//	void debug() const { printf(" a %d, b %d, id %d, t %d\n", a, b, id, t); }
} M[kMaxn];

int T, n;
IAr up, fa, used;
std::vector<int> G[kMaxn];
std::priority_queue<Monster> hap;

inline int Find(int x) { return fa[x] == x ? x : (fa[x] = Find(fa[x])); }
void Dfs(int);

int main() {
	scanf("%d", &T);
//	T = 1;
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			used[i] = 0; G[i].clear();
		}
		M[1] = {0, 0, 1, 0};
		assert(hap.empty());
		for (int i = 2; i <= n; ++i) {
			scanf("%lld%lld", &M[i].a, &M[i].b);
			M[i].id = i; M[i].t = 0;
			M[i].set(); hap.push(M[i]);
		}
		for (int i = 1, x, y; i < n; ++i) {
			scanf("%d%d", &x, &y);
			G[x].pb(y); G[y].pb(x);
		} up[1] = 0; Dfs(1);
		for (int i = 1; i <= n; ++i) fa[i] = i;
		for (int f; !hap.empty(); ) {
			Monster u = hap.top(); hap.pop();
			if (used[u.id] || u.t != M[u.id].t) continue;
			used[u.id] = 1;
			M[f = Find(up[u.id])] += u;
			fa[u.id] = f, M[f].t = 1;
			if (f > 1) hap.push(M[f]);
		} printf("%lld\n", std::max(0ll, M[1].a));
	} return 0;
}

void Dfs(int u) {
	for (auto v : G[u]) {
		if (v == up[u]) continue;
		up[v] = u; Dfs(v);
	}
}
