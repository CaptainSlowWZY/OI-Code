#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>

#define se second
#define FORTO(e, v, _) for (int e = back[_], v = E[e].to; e; v = E[e = E[e].next].to)

typedef long long LL;
typedef unsigned long long ULL;

const int kMaxw = 1e4 + 5, kMaxn = 1e5 + 5;

struct Edge { int to; ULL w; int next; } E[kMaxn << 1];

int totp, mp[kMaxw], P[1300];
int n, cnte, back[kMaxn];
std::map<ULL, int> cnt;
std::map<int, ULL> V;

void Dfs(int, int, ULL);
ULL Fact(int);
inline void AddE(int u, int v, ULL w) {
	E[++cnte] = (Edge){v, w, back[u]}, back[u] = cnte;
	E[++cnte] = (Edge){u, w, back[v]}, back[v] = cnte;
}

int main() {
	srand(time(NULL));
	for (int i = 2; i <= (int)1e4; ++i) {
		if (!mp[i]) P[totp++] = mp[i] = i;
		for (int j = 0, d; j < totp && (d = i * P[j]) <= (int)1e4; ++j) {
			mp[d] = P[j];
			if (i % P[j] == 0) break;
		}
	} scanf("%d", &n);
	for (int i = 1, w, u, v; i < n; ++i) { scanf("%d%d%d", &u, &v, &w); AddE(u, v, Fact(w)); }
	Dfs(1, 0, 0);
	LL ans = 0;
	for (std::map<ULL, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) ans += 1ll * it->se * (it->se - 1);
	printf("%lld\n", ans);
	return 0;
}

void Dfs(int u, int fa, ULL xs) {
	++cnt[xs];
	FORTO(e, v, u) if (v != fa) Dfs(v, u, xs ^ E[e].w);
}

ULL Val(int p) {
	if (!V.count(p)) return V[p] = (ULL)rand() << 31 | rand();
	return V[p];
}

ULL Fact(int x) {
	ULL res = 0;
	for (int i = 0; i < totp && P[i] <= x; ++i) for (; !(x % P[i]); x /= P[i]) res ^= Val(P[i]);
	if (x > 1) res ^= Val(x);
	return res;
}
