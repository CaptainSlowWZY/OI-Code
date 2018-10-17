// BZOJ 1791
// IOI 2008 Island
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#include <stack>
#include <queue>

#define fir first
#define sec second
#define pb push_back
// #define _DEBUG_MD_

typedef std::pair<int, int> P;
typedef long long LL;

const int MAXN = 1e6 + 10;
const LL INF_64 = 0x3f3f3f3f3f3f3f3f;

typedef int IntAr[MAXN];

struct Edge {
	int to, cost, next, tag;
} E[MAXN << 1];

int N, tote = 1;
IntAr vis, last, on_lp, dep, pre;
LL sumD[MAXN << 1], mxdep[MAXN], D[MAXN];
P Q[MAXN << 1];
std::stack<P> stk;
std::vector<P> loop;
std::vector<int> subT[MAXN];

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}
inline void add_edge(int u, int v, int c) {
	E[++tote].to = v, E[tote].cost = c, E[tote].next = last[u], last[u] = tote;
	E[++tote].to = u, E[tote].cost = c, E[tote].next = last[v], last[v] = tote;
}
bool find_lp(int s);
LL BFS(int s);
LL BFS_again(int s);

int main() {
	using FastIO::read;
	read(N);
	for (int li, to, i = 1; i <= N; i++) {
		read(to), read(li);
		add_edge(i, to, li);
	}
	memset(D, 0x3f, sizeof D);
	LL ans = 0;
	for (int i = 1; i <= N; i++)
		if (!vis[i]) {
			loop.clear();
			if (!find_lp(i)) {
				BFS(i);
				ans += BFS_again(i);
				continue;
			}
			LL dmt = 0;
			int now = 1, sz = loop.size();
#ifdef _DEBUG_MD_
			printf("\ni=%d, size of loop: %d\n", i, sz);
#endif
			for (int i = 0; i < sz; i++) {
				mxdep[now] = BFS(loop[i].fir);
				dmt = std::max(dmt, BFS_again(loop[i].fir));
#ifdef _DEBUG_MD_
				printf("v: %d, dep: %lld, cost to next: %d\n", loop[i].fir, mxdep[now], loop[i].sec);
#endif
				sumD[now + 1] = loop[i].sec, sumD[++now + sz] = loop[i].sec;
			}
			for (int i = 1; i <= sz * 2; i++) sumD[i] += sumD[i - 1];
			int hd = 0, tl = 0;
			for (int i = 1; i <= sz * 2; i++) {
				while (hd < tl && i - Q[hd].fir >= sz) ++hd;
				if (hd < tl) dmt = std::max(dmt, mxdep[i > sz ? i - sz : i] + mxdep[Q[hd].sec] + sumD[i] - sumD[Q[hd].fir]);
				LL tmp = -sumD[i] + mxdep[i > sz ? i - sz : i];
				while (hd < tl && tmp > -sumD[Q[tl - 1].fir] + mxdep[Q[tl - 1].sec]) --tl;
				Q[tl++] = P(i, i > sz ? i - sz : i);
			}
#ifdef _DEBUG_MD_
			printf("diamter = %lld\n", dmt);
#endif
			ans += dmt;
		}
	printf("%lld\n", ans);
	return 0;
}

bool find_lp(int s) {
	// When doing DFS, we put the vertex on current link into a stack as pairs.
	// The first element is the index of the vertex,
	// The second element is the weight of the edge from the vertex to its father in DFS tree.
	std::queue<int> Q;
#ifdef _DEBUG_MD_
	printf("find loop: s=%d\n", s);	
#endif
	bool fd = false;
	for (Q.push(s), dep[s] = 0, vis[s] = 1; !Q.empty(); ) {
		int u = Q.front(); Q.pop();
		for (int v, e = last[u]; e; e = E[e].next) {
			if (E[e].tag) continue;
			if (vis[v = E[e].to]) {
				if (fd) continue;
				fd = 1;
/*				for (; !stk.empty() && stk.top().fir != v; stk.pop()) on_lp[stk.top().fir] = 1, loop.pb(stk.top());
                if (!stk.empty() && stk.top().fir == v) stk.pop();
                on_lp[v] = 1, loop.pb(P(v, E[e].cost));*/
                int v1 = u, v2 = v;
                for (dep[v1] < dep[v2] ? (std::swap(v1, v2), 0) : 0; dep[v1] > dep[v2]; on_lp[v1] = 1, v1 = E[pre[v1]].to);
                for (; v1 != v2; on_lp[v1] = on_lp[v2] = 1, v1 = E[pre[v1]].to, v2 = E[pre[v2]].to);
				on_lp[v1] = 1;
				for (v2 = v; v2 != v1; v2 = E[pre[v2]].to) loop.pb(P(E[pre[v2]].to, E[pre[v2]].cost));
				std::reverse(loop.begin(), loop.end());
				for (loop.pb(P(v, E[e].cost)), v2 = u; v2 != v1; v2 = E[pre[v2]].to) loop.pb(P(v2, E[pre[v2]].cost));
                continue;
			}
			E[e].tag = E[e ^ 1].tag = vis[v] = 1, pre[v] = e ^ 1, dep[v] = dep[u] + 1, Q.push(v);
		}
	}
	return fd;
}

LL BFS(int s) {
	std::queue<int> Q;
	for (Q.push(s), D[s] = 0; !Q.empty(); ) {
		int u = Q.front();
		subT[s].pb(u), Q.pop();
		for (int v, e = last[u]; e; e = E[e].next)
			if (!on_lp[v = E[e].to]) {
				if (D[v] > D[u] + E[e].cost) {
					D[v] = D[u] + E[e].cost;
					Q.push(v);
				}
			}
	}
	LL res = 0;
	for (std::vector<int>::iterator it = subT[s].begin(); it != subT[s].end(); ++it) res = std::max(res, D[*it]);
	return res;
}

LL BFS_again(int s) {
	LL mxd = 0;
	int ns = -1;
	for (std::vector<int>::iterator it = subT[s].begin(); it != subT[s].end(); ++it) {
		if (D[*it] > mxd) ns = *it, mxd = D[ns];
		D[*it] = INF_64;
	}
	if (ns == -1) return 0;
	std::queue<int> Q;
	for (Q.push(ns), D[ns] = 0, on_lp[s] = 0; !Q.empty(); ) {
		int u = Q.front(); Q.pop();
		for (int v, e = last[u]; e; e = E[e].next)
			if (!on_lp[v = E[e].to]) {
				if (D[v] > D[u] + E[e].cost) {
					D[v] = D[u] + E[e].cost;
					Q.push(v);
				}
			}
	}
	on_lp[s] = 1;
	LL res = 0;
	for (std::vector<int>::iterator it = subT[s].begin(); it != subT[s].end(); ++it) res = std::max(res, D[*it]);
	return res;
}

// AC!!!
