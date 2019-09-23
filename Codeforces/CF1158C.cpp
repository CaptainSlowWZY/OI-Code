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

const int kInf = 0x3f3f3f3f, kMod = 1e9 + 7, kMaxn = 5e5 + 5;
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

int n, dfs_clock, D[kMaxn], P[kMaxn];
std::vector<int> G[kMaxn];

namespace bit {
	int D[kMaxn];
	inline void Clear() { std::fill(D, D + n + 2, 0); }
	void Add(int p) {
		for (; p <= n + 1; p += p & -p) ++D[p];
	}
	int Sum(int p) {
		int res = 0;
		for (; p; p &= p - 1) res += D[p];
		return res;
	}
}
void Dfs(int u) {
	P[u] = dfs_clock--;
	std::sort(G[u].begin(), G[u].end());
	for (auto v : G[u]) Dfs(v);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		bit::Clear();
		for (int i = 1; i <= n + 1; i++) G[i].clear();
		int nos = 0;
		for (int nxt, i = 1; i <= n; i++) {
			scanf("%d", &nxt);
			if (nxt == -1) nxt = i + 1;
			if (bit::Sum(nxt - 1) - bit::Sum(i) > 0)
				nos = 1;
			bit::Add(nxt);
			G[nxt].pb(i);
		} if (nos) {
			puts("-1");
			continue;
		} dfs_clock = n + 1;
		Dfs(n + 1);
		for (int i = 1; i <= n; i++) printf("%d ", P[i]);	
		pch('\n');
	} return 0;
}
