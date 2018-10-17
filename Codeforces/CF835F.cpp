// Codeforces 835 F
// Round #427 (Div. 2)
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include <set>

#define fir first
#define sec second
#define pb push_back
// #define _DEBUG_MD_

typedef long long LL;
typedef std::pair<LL, int> Pli;
typedef std::pair<int, int> Pii;
typedef std::multiset<Pli> Mymset;

const int MAXN = 2e5 + 10;
const LL INF_64 = 0x3f3f3f3f3f3f3f3f;

int N, gotlp, vis[MAXN], on_lp[MAXN];
LL mxdep[MAXN << 1], D[MAXN], sumD[MAXN << 1];
std::vector<Pii> G[MAXN], loop;
std::vector<int> subt[MAXN];
Mymset mn, mx;
std::stack<Pii> Stk;

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}
LL calc1() {
	Mymset::reverse_iterator mxi = mx.rbegin();
	Mymset::iterator mni = mn.begin();
	if (mxi->sec != mni->sec) return mxi->fir - mni->fir;
	if (++mni != mn.end()) return mxi->fir - mni->fir;
	return 0;
}
LL calc2() {
	Mymset::iterator mni = mn.begin();
	Mymset::reverse_iterator mxi = mx.rbegin();
	if (mxi->sec != mni->sec) return mxi->fir - mni->fir;
	if (++mxi != mx.rend()) return mxi->fir - mni->fir;
	return 0;
}
inline LL calc() { return std::max(calc1(), calc2()); }
void dfs(int u, int fa);
LL BFS(int s);
LL BFS_again(int s);

int main() {
	using FastIO::read;
	read(N);
	for (int i = 0, ui, vi, li; i < N; i++) {
		read(ui), read(vi), read(li);
		G[ui].pb(Pii(vi, li));
		G[vi].pb(Pii(ui, li));
	}
	dfs(1, 0);
	int now = 0, sz = loop.size();
	memset(D, 0x3f, sizeof D);
	LL ans = 0;
	for (auto pi : loop) {
		mxdep[++now + sz] = mxdep[now] = BFS(pi.fir);
		ans = std::max(ans, BFS_again(pi.fir));
		sumD[now + 1] = sumD[now + 1 + sz] = pi.sec;
	}
	for (int i = 1; i <= sz * 2; i++) sumD[i] += sumD[i - 1];
	for (int i = 1; i <= sz; i++) {
		if (i > 1) mx.insert(Pli(sumD[i] + mxdep[i], i));
		if (i < sz) mn.insert(Pli(sumD[i] - mxdep[i], i));
	}
	LL tmp = calc();
	for (int i = sz + 1; i < sz * 2; i++) {
		mn.erase(mn.find(Pli(sumD[i - sz] - mxdep[i - sz], i - sz)));
		mx.erase(mx.find(Pli(sumD[i - sz + 1] + mxdep[i - sz + 1], i - sz + 1)));
		mn.insert(Pli(sumD[i - 1] - mxdep[i - 1], i - 1));
		mx.insert(Pli(sumD[i] + mxdep[i], i));
		tmp = std::min(tmp, calc());
	}
	printf("%I64d\n", std::max(tmp, ans));
	return 0;
}

void dfs(int u, int fa) {
	vis[u] = 1;
	for (auto pe : G[u]) {
		int v = pe.fir;
		if (v == fa) continue;
		if (vis[v]) {
			gotlp = 1;
			for (; !Stk.empty() && Stk.top().fir != v; Stk.pop()) on_lp[Stk.top().fir] = 1, loop.pb(Stk.top());
			if (!Stk.empty() && Stk.top().fir == v) Stk.pop();
			on_lp[v] = 1, loop.pb(Pii(v, pe.sec));
			return;
		}
		Stk.push(Pii(v, pe.sec));
		dfs(v, u);
		if (gotlp) return;
		if (!Stk.empty() && Stk.top().fir == v) Stk.pop();
	}
}

LL BFS(int s) {
	std::queue<int> Q;
	for (Q.push(s), D[s] = 0; !Q.empty(); ) {
		int u = Q.front(), v;
		subt[s].pb(u), Q.pop();
		for (auto pe : G[u]) {
			if (on_lp[v = pe.fir]) continue;
			if (D[v] > D[u] + pe.sec) {
				D[v] = D[u] + pe.sec;
				Q.push(v);
			}
		}
	}
	LL res = 0;
	for (int i : subt[s]) res = std::max(res, D[i]);
	return res;
}

LL BFS_again(int s) {
	LL mxd = 0;
	int k = -1;
	for (int i : subt[s]) {
		if (D[i] > mxd) k = i, mxd = D[i];
		D[i] = INF_64;
	}
	if (k == -1) return 0;
	std::queue<int> Q;
	for (Q.push(k), D[k] = on_lp[s] = 0; !Q.empty(); ) {
		int u = Q.front(), v; Q.pop();
		for (auto pe : G[u]) {
			if (on_lp[v = pe.fir]) continue;
			if (D[v] > D[u] + pe.sec) {
				D[v] = D[u] + pe.sec;
				Q.push(v);
			}
		}
	}
	on_lp[s] = 1;
	LL res = 0;
	for (int i : subt[s]) res = std::max(res, D[i]);
	return res;
}

// AC!!!