#include <algorithm>
// #include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
// #include <cmath>
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

const int kMaxn = 1005, kMaxv = kMaxn * kMaxn;

Vi G[kMaxv];
int t, n, k, node;
int U[kMaxn][kMaxn], ideg[kMaxv], stat[kMaxv], inq[kMaxv];
Pii P[kMaxv];
std::queue<int> que;

inline void AddEdge(int v, int u) {
	G[u].pb(v); ++ideg[v];
}

int main() {
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &k);
		node = 0;
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < n; j++)
				U[i][j] = ++node;
		}
		for (int i = 1; i <= node; i++) {
			G[i].clear();
			ideg[i] = inq[i] = 0; stat[i] = 2;
		}
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < n; j++) {
				if ((i + j) % n == 0 || i * j % n == 0) continue;
				AddEdge(U[i][j], U[j][(i + j) % n]);
				AddEdge(U[i][j], U[j][i * j % n]);
			}
		}
		for (int i = 1; i <= node; i++) {
			if (ideg[i]) continue;
			que.push(i); stat[i] = inq[i] = 1;
		}
		while (!que.empty()) {
			int u = que.front(); que.pop();
			for (auto v : G[u]) {
				--ideg[v];
				if (!stat[u] && !inq[v]) {
					stat[v] = inq[v] = 1;
					que.push(v);
				} else if (!ideg[v] && !inq[v]) {
					stat[v] = 0, inq[v] = 1;
					que.push(v);
				}
			}
		}
		for (int a, b; k--; ) {
			scanf("%d%d",  &a, &b);
			int t = stat[U[a][b]];
			if (t == 2) puts("draw");
			else puts(t ? "cocktail" : "sys");
		}
	} return 0;
}