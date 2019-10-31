#pragma GCC optimize(2)
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

#define pb push_back

typedef long long LL;

const int kMaxn = 3e5 + 5, kLg = 20, kInf = 0x3f3f3f3f;

struct Blo {
	int le, ri, pos;
	bool operator<(const Blo & b) const {
		return le < b.le || le == b.le && ri < b.ri;
	}
};

int n, eul;
int pw[kLg], Lg[kMaxn << 1], dep[kMaxn];
int T[kLg][kMaxn << 1], pos[kMaxn];
std::vector<int> G[kMaxn];
std::set<Blo> tog;

inline int Low(int u, int v) {
	return dep[u] < dep[v] ? u : v;
}
int Dist(int u, int v);
void Dfs(int u, int fa);

int main() {
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].pb(v); G[v].pb(u);
	} dep[1] = 1; Dfs(1, 0);
	for (int i = pw[0] = 1; i < kLg; ++i)
		pw[i] = pw[i - 1] << 1;
	Lg[0] = -1;
	for (int i = 1; i <= eul; ++i) Lg[i] = Lg[i >> 1] + 1;
	for (int i = 1; i < kLg; ++i) {
		for (int j = 1; j + pw[i] - 1 <= eul; ++j)
			T[i][j] = Low(T[i - 1][j], T[i - 1][j + pw[i - 1]]);
	}
	LL ans = 0;
	for (int i = 1; i <= n; ++i) tog.insert({i, i, i});
	for (int l, r, p; n--; ) {
		scanf("%d%d%d", &l, &r, &p);
		auto hd = tog.lower_bound({l, 0, 0}),
			 tl = tog.upper_bound({r, kInf, 0});
		auto it = hd; --tl;
		if (hd == tog.end() || hd->le > l) --hd;
		if (hd == tl) {
			ans += LL(r - l + 1) * Dist(hd->pos, p);
			Blo a = {hd->le, l - 1, hd->pos},
				c = {r + 1, hd->ri, hd->pos};
			tog.erase(hd);
			if (a.le <= a.ri) tog.insert(a);
			if (c.le <= c.ri) tog.insert(c);
		} else {
			for (; it != tog.end() && it->ri <= r; ) {
				ans += LL(it->ri - it->le + 1) * Dist(it->pos, p);	
				if ((it = tog.erase(it)) == tog.end()) break;
			} if (it != tog.end() && it->le <= r) {
				ans += LL(r - it->le + 1) * Dist(it->pos, p);
				Blo c = {r + 1, it->ri, it->pos};
				tog.erase(it);
				if (c.le <= c.ri) tog.insert(c);
			} hd = tog.lower_bound({l, 0, 0});
			if (hd != tog.begin() && (hd == tog.end() || hd->le > l)) {
				--hd;
				ans += LL(hd->ri - l + 1) * Dist(hd->pos, p);
				Blo a = {hd->le, l - 1, hd->pos};
				tog.erase(hd);
				if (a.le <= a.ri) tog.insert(a);
			}
		} tog.insert({l, r, p});
	} printf("%lld\n", ans);
	return 0;
}

int Dist(int u, int v) {
	int l = pos[u], r = pos[v];
	if (l > r) std::swap(l, r);
	int k = Lg[r - l + 1],
		lca = Low(T[k][l], T[k][r - pw[k] + 1]);
	return dep[u] + dep[v] - (dep[lca] << 1);
}

void Dfs(int u, int fa) {
	T[0][pos[u] = ++eul] = u;
	for (auto v : G[u]) {
		if (v == fa) continue;
		dep[v] = dep[u] + 1; Dfs(v, u);
		T[0][++eul] = u;
	}
}
