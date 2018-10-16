// darksoul
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <map>

#define fir first
#define sec second
#define pb push_back
// #define _DEBUG_MD_

typedef std::pair<int, int> P;
typedef long long LL;

const int MAXN = 1e6 + 10;
const LL INF_64 = 0x7f7f7f7f7f7f7f7f;

struct Edge {
	int to, cost, next;
} E[MAXN << 1];

int N, tote, last[MAXN], vis[MAXN], on_lp[MAXN], findf;
LL sumD[MAXN << 1], mxdep[MAXN], D[MAXN << 1];
P Q[MAXN << 1];
std::vector<P> loop;
std::stack<P> Stk;
std::vector<int> subT[MAXN];
std::map<P, int> Mp;

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
}
void dfs(int u, int fa);
LL BFS(int s);
LL BFS_again(int s);

int main() {
	using FastIO::read;
	read(N);
	int istr = 0;
	for (int i = 0, ui, vi, ai; i < N; i++) {
		read(ui), read(vi), read(ai);
		if (ui == vi) {
			istr = 1;
			continue;
		}
		int & it = Mp[P(ui, vi)];
		if (!it) it = ai, Mp[P(vi, ui)] = ai;
		else {
			istr = 1;
			if (ai < it) Mp[P(vi, ui)] = it = ai;
		}
	}
	for (auto it : Mp) add_edge(it.fir.fir, it.fir.sec, it.sec);
	memset(D, 0x7f, sizeof D);
	if (istr) {
		BFS(1);
		printf("%lld\n", BFS_again(1) + 1);
		return 0;
	}
	dfs(1, 0);
	LL tot_len = 0, ans = 0;
	int last = 0, sz = loop.size();
#ifdef _DEBUG_MD_
	putchar('\n');
	for (auto pi : loop) printf(" point:%d, dist to next: %d\n", pi.fir, pi.sec);
	putchar('\n');
#endif
	for (auto pi : loop) {
		tot_len += pi.sec, ++last;
		sumD[last + 1] = sumD[last + sz + 1] = pi.sec;
		mxdep[last] = BFS(pi.fir);
#ifdef _DEBUG_MD_
		LL tmp = BFS_again(pi.fir);
		printf("\n the diameter in subtree %d: %lld\n", pi.fir, tmp);
		ans = std::max(ans, tmp);
#endif
#ifndef _DEBUG_MD_
		ans = std::max(ans, BFS_again(pi.fir));
#endif
	}
#ifdef _DEBUG_MD_
	putchar('\n');
	for (int i = 1; i <= sz; i++) printf("max_dep_%d=%lld\n", i, mxdep[i]);
	printf("  length of loop: %lld, size of loop: %d \n", tot_len, sz);
	putchar('\n');
#endif
	sz <<= 1;
	for (int i = 1; i <= sz; i++) sumD[i] += sumD[i - 1];
	int hd = 0, tl = 0;
	for (int i = 1; i <= (sz >> 1); i++) {
		while (hd < tl && -sumD[Q[tl - 1].fir] + mxdep[Q[tl - 1].sec] <= -sumD[i - 1] + mxdep[i]) --tl;
		Q[tl++] = P(i, i);
	}
	for (int i = (sz >> 1) + 1; i <= sz; i++) {
		while (hd < tl && sumD[i] - sumD[Q[hd].fir] > tot_len / 2) ++hd;
#ifdef _DEBUG_MD_
		printf("\ni=%d, sumD=%lld\n", i, sumD[i]);
		puts("Queue:");
		for (int j = hd; j < tl; j++) printf("  %d: mxdep=%lld, sumD=%lld\n", j, mxdep[Q[j].sec], sumD[Q[j].fir]);
#endif
		if (hd < tl) {
			ans = std::max(ans, sumD[i] - sumD[Q[hd].fir] + mxdep[i - sz / 2] + mxdep[Q[hd].sec]);
#ifdef _DEBUG_MD_
			printf("!!! ans=%lld\n", ans);
#endif
		}
		while (hd < tl && -sumD[Q[tl - 1].fir] + mxdep[Q[tl - 1].sec] <= -sumD[i - 1] + mxdep[i - sz / 2]) --tl;
		Q[tl++] = P(i, i - sz / 2);
	}
	printf("%lld\n", ans + 1);
	return 0;
}

void dfs(int u, int fa) {
	vis[u] = 1;
	for (int v, e = last[u]; e; e = E[e].next)
		if ((v = E[e].to) != fa) {
			if (vis[v]) {
				if (findf) continue;
#ifdef _DEBUG_MD_
				printf("!!find loop! u: %d, v: %d\n", u, v);
#endif
				for (; !Stk.empty() && Stk.top().fir != v; Stk.pop()) on_lp[Stk.top().fir] = 1, loop.pb(Stk.top());
				on_lp[v] = 1, loop.pb(P(v, E[e].cost));
				if (!Stk.empty() && Stk.top().fir == v) Stk.pop();
				findf = 1;
			}
			else {
				Stk.push(P(v, E[e].cost));
				dfs(v, u);
				if (!Stk.empty() && Stk.top().fir == v) Stk.pop();
			}
		}
}

LL BFS(int s) {
	std::queue<int> Q;
	for (D[s] = 0, Q.push(s); !Q.empty(); ) {
		int u = Q.front(); subT[s].pb(u), Q.pop();
		for (int v, e = last[u]; e; e = E[e].next)
			if (!on_lp[v = E[e].to]) {
				if (D[v] > D[u] + E[e].cost) {
					D[v] = D[u] + E[e].cost;
					Q.push(v);
				}
			}
	}
	LL res = 0;
	for (int i : subT[s]) res = std::max(res, D[i]);
	return res;
}

LL BFS_again(int s) {
	std::queue<int> Q;
	int ns = -1;
	LL mxd = 0;
	for (int i : subT[s]) {
		if (D[i] > mxd) ns = i, mxd = D[i];
		D[i] = INF_64;
	}
	if (ns == -1) return 0;
	on_lp[s] = 0;
	for (D[ns] = 0, Q.push(ns); !Q.empty(); ) {
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
	for (int i : subT[s]) res = std::max(res, D[i]);
	return res;
}

// AC!!!
