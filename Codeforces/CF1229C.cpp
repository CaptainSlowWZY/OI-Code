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
#define SIZE(_) (int)_.size()

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

const int kMaxn = 1e5 + 5;

typedef std::set<int> Si;

int n, m, q;
int sal[kMaxn], out[kMaxn];
Vi G[kMaxn];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0, a, b; i < m; i++) {
		scanf("%d%d", &a, &b);
		if (a > b) std::swap(a, b);
		G[a].pb(b), ++out[b];
	}
	LL ans = 0;
	for (int i = 1; i <= n; i++)
		ans += 1ll * SIZE(G[i]) * out[i];
	printf("%lld\n", ans);
	scanf("%d", &q);
	for (int v, i = 1; i <= q; i++) {
		scanf("%d", &v);
		sal[v] = n + i;
		ans -= 1ll * SIZE(G[v]) * out[v];
		for (auto u : G[v]) {
			ans += out[u] - SIZE(G[u]) - 1;
			--out[u], ++out[v], G[u].pb(v);
		} G[v].clear();
		printf("%lld\n", ans);
	} return 0;
}
