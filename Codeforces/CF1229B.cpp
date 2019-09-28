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

const int kMaxn = 1e5 + 5;

typedef std::map<LL, int> Map;

int n, sum;
LL A[kMaxn];
Vi G[kMaxn];

void Dfs(int u, int fa, Map down);

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", A + i);
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d%d", &u, &v);
		G[u].pb(v), G[v].pb(u);
	}
	Dfs(1, 0, Map());
	printf("%d\n", sum);
	return 0;
}

void Dfs(int u, int fa, Map down) {
	Map cur;
	cur[A[u]] = 1;
	for (auto & p : down)
		cur[std::__gcd(A[u], p.fir)] += p.sec;
	for (auto & p : cur)
		sum = Add(sum, p.fir % kMod * p.sec % kMod);
	for (auto v : G[u]) {
		if (v == fa) continue;
		Dfs(v, u, cur);
	}
}
