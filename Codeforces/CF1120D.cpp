#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define fir first
#define sec second
#define pb push_back
#define pch putchar

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef std::vector<int> Vi;

const int kInf = 0x3f3f3f3f, kMod = 1e9 + 7;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

struct Edge {
	int u, v, c, nd;
	bool operator<(const Edge & e) const {
		return c < e.c;
	}
};

const int kMaxn = 2e5 + 5;

int n, lclock, totl;
int C[kMaxn], idfn[kMaxn], odfn[kMaxn], fa[kMaxn];
Vi G[kMaxn], ans;
std::vector<Edge> E;

inline int Find(int x) { return x == fa[x] ? x : (fa[x] = Find(fa[x])); }
inline void Merge(int x, int y) { fa[Find(x)] = Find(y); }
void Dfs(int, int);

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", C + i);
	for (int i = 1, a, b; i < n; i++) {
		scanf("%d%d", &a, &b);
		G[a].pb(b), G[b].pb(a);
	}

	Dfs(1, 0);
	for (int i = 1; i <= n; i++)
		E.push_back({idfn[i], odfn[i], C[i], i});
	std::sort(E.begin(), E.end());
	int cur = 0, cnt = 0;
	LL cost = 0;
	ans.push_back(E[0].nd);
	for (int i = 1; i <= totl; i++) fa[i] = i;
	for (int i = 1; i < (int)E.size(); i++) {
	//	printf(" i %d, [%d, %d], c %d\n", i, E[i].u, E[i].v, E[i].c);
		if (E[i].c != E[cur].c) {
			for (int j = cur; j < i; j++) {
				if (Find(E[j].u) == Find(E[j].v)) continue;
			/*	printf(" Add [%d, %d], cost %d, id %d\n",
						E[j].u, E[j].v, E[j].c, E[j].nd); */
				Merge(E[j].u, E[j].v);
				cost += E[j].c;
				if (++cnt == totl) break;
			} cur = i;
			if (cnt == totl) break;
		}
		if (Find(E[i].u) != Find(E[i].v)) {
			ans.push_back(E[i].nd);
		}
	}
	if (cnt < totl) {
		for (int i = cur; i < (int)E.size(); i++) {
			if (Find(E[i].u) == Find(E[i].v)) continue;
			Merge(E[i].u, E[i].v);
			cost += E[i].c;
			if (++cnt == totl) break;
		}
	} printf("%lld %d\n", cost, (int)ans.size());
	std::sort(ans.begin(), ans.end());
	for (auto i : ans) printf("%d ", i);
	pch('\n');
	return 0;
}

void Dfs(int u, int fa) {
	idfn[u] = lclock;
	int leaf = 1;
	for (auto v : G[u]) {
		if (v == fa) continue;
		Dfs(v, u); leaf = 0;
	}
	if (leaf) ++lclock;
	totl += leaf;
	odfn[u] = lclock;
}
