#include <algorithm>
#include <cassert>
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
#define rg register
#define SZ(_) (int)_.size()

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef std::pair<LL, int> Pli;
typedef std::pair<int, LL> Pil;
typedef std::pair<LL, LL> Pll;
typedef std::vector<int> Vi;
typedef std::vector<LL> Vl;
typedef std::map<int, int> Mii;
typedef std::map<LL, int> Mli;
typedef std::map<int, LL> Mil;
typedef std::map<LL, LL> Mll;
typedef std::set<int> Si;
typedef std::set<LL> Sl;

const int kInf = 0x3f3f3f3f, kMod = 1e9 + 7;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

template <typename T> inline
void UMin(T & x, const T & y) { if (x > y) x = y; }
template <typename T> inline
void UMax(T & x, const T & y) { if (x < y) x = y; }
inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

const int kMaxn = (1 << 17) + 5;

int n;
Vi G[kMaxn], ans;
int fa[kMaxn];

inline bool IsLeaf(int u) {
	return G[u].size() == 1 && G[u][0] == fa[u];
}
void Dfs(int u);
Pii Find(int u);
int GetDep(int u, int f);

int main() {
	scanf("%d", &n);
	int n0 = n;
	n = (1 << n) - 2;
	for (int a, b, i = n - 1; i; i--) {
		scanf("%d%d", &a, &b);
		G[a].pb(b); G[b].pb(a);
	}
	Pii pu = Find(1),
		pv = Find(pu.fir);
	Dfs(pv.fir);
	int rt = pu.fir;
	for (int i = pv.sec >> 1; i; i--) rt = fa[rt];
	if (pv.sec & 1) {
		if (~GetDep(rt, fa[rt]) && ~GetDep(fa[rt], rt)) {
			ans.pb(rt); ans.pb(fa[rt]);
		}
	} else {
		fa[rt] = 0; Dfs(rt);
		int nos, cnt2, cnt4;
		nos = cnt2 = cnt4 = 0;
		for (int i = 1, deg; i <= n; i++) {
			deg = G[i].size();
			switch (deg) {
				case 1 :
					if (!IsLeaf(i)) nos = 1;
					break;
				case 2 :
					if (i != rt) ++cnt2;
					if (cnt2 > 1) nos = 1;
					else {
						for (auto v : G[i]) {
							if (v == fa[i]) continue;
							if (IsLeaf(v)) ans.pb(i);
						}
					} break;
				case 3 :
					break;
				case 4 :
					if (cnt4++) nos = 1;
					else {
						Vi dep;
						for (auto v : G[i]) {
							if (v == fa[i]) continue;
							int tmp = GetDep(v, i);
							if (tmp == -1) {
								nos = 1; break;
							}
							dep.pb(tmp);
						} std::sort(dep.begin(), dep.end());
						dep.erase(std::unique(dep.begin(),
							dep.end()), dep.end());
						if (dep.size() != 2) nos = 1;
						else if (dep[0] + 1 == dep[1]) ans.pb(i);
					} break;
				default : nos = 1;
			}
			if (nos) break;
		}
		if (cnt2 && cnt4 || ans.size() > 1 || nos) ans.clear();
	}
	printf("%d\n", (int)ans.size());
	if (ans.size()) {
		std::sort(ans.begin(), ans.end());
		for (auto i : ans) printf("%d ", i);
		pch('\n');
	} return 0;
}

Pii Find(int u) {
	static int D[kMaxn];
	std::fill(D, D + n + 1, -1);
	std::queue<int> que;
	D[u] = 0; que.push(u);
	Pii res = {u, 0};
	while (!que.empty()) {
		int t = que.front(); que.pop();
		if (D[t] > res.sec) res = {t, D[t]};
		for (auto v : G[t]) {
			if (~D[v]) continue;
			D[v] = D[t] + 1;
			que.push(v);
		}
	} return res;
}

void Dfs(int u) {
	for (auto v : G[u]) {
		if (v == fa[u]) continue;
		fa[v] = u; Dfs(v);
	}
}

int GetDep(int u, int f) {
	int cnts = 0, d1, d2;
	for (auto v : G[u]) {
		if (v == f) continue;
		if (++cnts == 1) d1 = GetDep(v, u);
		else if (cnts == 2) d2 = GetDep(v, u);
		else return -1;
	}
	if (!cnts) return 1;
	if (cnts == 1 || d1 == -1 ||
		d2 == -1 || d1 != d2) return -1;	
	return d1 + 1;
}
