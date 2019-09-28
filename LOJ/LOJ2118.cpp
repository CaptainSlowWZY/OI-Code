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

const int kMaxn = 2e6 + 5;

int n, m, ans;
int C[kMaxn];
Vi G[kMaxn];

void Dfs(int u);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", C + i);
	for (int i = 0, v, ki; i < n; i++) {
		scanf("%d", &ki);
		C[i] += ki;
		while (ki--) {
			scanf("%d", &v);
			G[i].pb(v);
		}
	}
	Dfs(0);
	printf("%d\n", ans);
	return 0;
}

void Dfs(int u) {
	for (auto v : G[u]) Dfs(v);
	Vi tmp;
	for (auto v : G[u]) tmp.pb(C[v]);
	std::sort(tmp.begin(), tmp.end());
	for (auto i : tmp) {
		if (C[u] + i - 1 <= m) {
			++ans; C[u] += i - 1;
		} else break;
	}
}
