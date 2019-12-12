#include <algorithm>
#include <cstdio>
#include <set>

#define fi first
#define se second

typedef long long LL;
typedef std::pair<LL, LL> Pii;

const int kMaxn = 2e5 + 5, kInf = 0x3f3f3f3f;

struct Node {
	LL x, y, v;
	bool operator<(const Node & n) const { return x > n.x; }
} T[kMaxn], G[kMaxn];

int n, m, w, h;
std::set<Pii, std::greater<Pii> > S;

int main() {
	scanf("%d%d%d%d", &n, &m, &w, &h);
	LL tot = 0, x, y;
	for (int i = 0; i < n; ++i) {
		scanf("%lld%lld%lld", &x, &y, &T[i].v); x *= h, y *= w, T[i].x = x - y, T[i].y = x + y; tot += T[i].v;
	}
	for (int i = 0; i < m; ++i) {
		scanf("%lld%lld%lld", &x, &y, &G[i].v); x *= h, y *= w, G[i].x = x - y, G[i].y = x + y;
	} std::sort(T, T + n); std::sort(G, G + m);
	LL flow = 0;
	for (int i = 0, j = 0; i < m; ++i) {
		for (; j < n && T[j].x >= G[i].x; ++j) S.insert(Pii(T[j].y, T[j].v));
		std::set<Pii, std::greater<Pii> >::iterator it = S.lower_bound(Pii(G[i].y, kInf));
		while (it != S.end() && G[i].v > 0) {
			Pii cur = *it;
			S.erase(it);
			if (cur.se > G[i].v) { flow += G[i].v, cur.se -= G[i].v, G[i].v = 0; S.insert(cur); }
			else { flow += cur.se, G[i].v -= cur.se; }
			it = S.lower_bound(Pii(G[i].y, kInf));
		}
	} printf("%lld\n", tot - flow); return 0;
}
