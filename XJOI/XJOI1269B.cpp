#pragma GCC optimize(2)
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

#define fir first
#define sec second
#define FORTO(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].nxt].to)

typedef long long LL;
typedef std::pair<LL, int> Pli;
typedef std::vector<int> Vi;

const int kMod = 998244353, kInv2 = 499122177;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}
template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}

const int kMaxk = 22, kMaxn = 1e5 + 5;

struct Edge { int to, w, nxt; } E[kMaxn << 2];

int n, m, k, cnte;
int S[kMaxk], back[kMaxn];
LL dis[kMaxk][kMaxn];

namespace solver1 {
	void Solve();
}
inline void AddEdge(int u, int v, int w) {
	E[++cnte] = {v, w, back[u]}, back[u] = cnte;
	E[++cnte] = {u, w, back[v]}, back[v] = cnte;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < k; ++i) scanf("%d", S + i);
	for (int x, y, z; m--; ) {
		scanf("%d%d%d", &x, &y, &z);
		AddEdge(x, y, z);
	}
	solver1::Solve();
	return 0;
}

namespace solver1 {
	std::priority_queue<Pli, std::vector<Pli>, std::greater<Pli> > hap;

	void Dijkstra(int s, LL D[]) {
		std::fill(D, D + n + 1, kInf64);
		D[s] = 0; hap.push({0, s});
		while (!hap.empty()) {
			Pli p = hap.top(); hap.pop();
			if (p.fir > D[p.sec]) continue;
			FORTO(p.sec) {
				if (p.fir + E[e].w < D[v]) {
					D[v] = p.fir + E[e].w;
					hap.push({D[v], v});
				}
			}
		}
	}

	LL A[kMaxn], B[kMaxn];
	int flag[(1 << 20) + 5];
	Vi sset;

	void Solve() {
		std::fill(B, B + n + 1, kInf64);
		for (int i = 0; i < k; ++i) {
			Dijkstra(S[i], dis[i]);
			for (int j = 1; j <= n; ++j)
				UMin(B[j], dis[i][j]);
		}
		LL o = 0;
		for (int i = 1; i <= n; ++i)
			UMax(o, B[i]);
		for (int i = 1; i <= n; ++i) {
			int m = 0;
			for (int j = 0; j < k; ++j)
				if (dis[j][i] > o) m |= 1 << j;
			if (!m) continue;
			sset.push_back(m);
		/*	flag[m] = 1;
			for (int s = m & m - 1; s != m; s = s - 1 & m)
				flag[s] = 1; */
		}
		std::sort(sset.begin(), sset.end());
		sset.erase(std::unique(sset.begin(),
					sset.end()), sset.end());
		for (auto s : sset) {
			if (flag[s]) continue;
			flag[s] = 1;
			for (int i = s & s - 1; i != s; i = i - 1 & s)
				flag[i] = 1;
		}
		int tot = 1 << k;
		for (int i = tot - 1; i >= 0; --i)
			tot -= flag[i];
/*		int tot = 0;
		for (int m = (1 << k) - 1; m >= 0; --m) {
			std::fill(A, A + n + 1, kInf64);
			for (int i = 0; i < k; ++i) {
				if (m >> i & 1 ^ 1) continue;
				for (int j = 1; j <= n; ++j)
					UMin(A[j], dis[i][j]);
			}
			LL t = 0;
			for (int i = 1; i <= n; ++i)
				UMax(t, A[i]);
			if (t == o) ++tot;
		} */
		printf("%d\n", Mul(tot, FPow(kInv2, k)));
	}
}
