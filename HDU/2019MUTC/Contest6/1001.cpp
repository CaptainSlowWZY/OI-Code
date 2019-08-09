#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>

#define fir first
#define sec second
#define pb push_back

typedef long long LL;
typedef std::map<int, LL, std::greater<int> > MyMap;
typedef std::pair<int, int> Pii;

const int kMaxn = 3e5 + 10;

int n, m, totmp;
LL flow, tota;
int A[kMaxn], son[kMaxn], len[kMaxn];
std::vector<int> G[kMaxn];
std::vector<Pii> C[kMaxn];
MyMap pool[kMaxn];

inline MyMap & NewMap() {
	pool[totmp].clear();
	return pool[totmp++];
}
void Dfs(int);
void Dfs(int, MyMap &, int);

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) {
			G[i].clear(); C[i].clear(); len[i] = 0;
		}
		for (int fi, i = 2; i <= n; i++) {
			scanf("%d", &fi); G[fi].pb(i);
		} tota = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", A + i);
			tota += A[i];
		}
		for (int xi, ki, ci; m--; ) {
			scanf("%d%d%d", &xi, &ki, &ci);
			C[xi].pb(Pii(ki, ci)); // ki: del-dep; ci: cost
		} Dfs(1); flow = totmp = 0; Dfs(1, NewMap(), 0);
		printf("%lld\n", tota - flow);
	} return 0;
}

void Dfs(int u) {
	son[u] = -1;
	for (auto v : G[u]) {
		Dfs(v);
		if (son[u] == -1 || len[v] > len[son[u]]) son[u] = v;
	} len[u] = (~son[u] ? len[son[u]] : 0) + 1;
}

void Dfs(int u, MyMap & rem, int d) {
//	printf(" Dfs2 %d, d = %d\n", u, d);
	if (~son[u]) Dfs(son[u], rem, d + 1);
	for (auto v : G[u]) {
		if (v == son[u]) continue;
		MyMap & remv = NewMap();
		Dfs(v, remv, 0);
		for (auto & pii : remv) {
			if (!pii.sec) continue;
			rem[d + pii.fir + 1] += pii.sec;
		}
	} rem[d] += A[u];
	for (auto & cam : C[u]) {
	//	printf(" camera at %d, k %d, cost %d\n", u, cam.fir, cam.sec);
	//	printf("  print map\n");
	//	for (auto & pii : rem) printf("    [%d] = %lld\n", pii.fir, pii.sec);
		if (rem.empty()) break;
		for (auto it = rem.lower_bound(cam.fir + d);
				cam.sec; ) {
			if (it == rem.end()) break;
		//	printf("  it: fir %d, sec %lld\n", it->fir, it->sec);
			LL f = std::min((LL)cam.sec, it->sec);
			it->sec -= f, cam.sec -= f, flow += f;
			if (!it->sec) {
				rem.erase(it);
				it = rem.lower_bound(cam.fir + d);
			}
		}
	}
}
