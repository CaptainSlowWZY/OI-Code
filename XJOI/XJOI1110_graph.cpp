#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <cassert>

#define rg register
#define gch getchar
#define pb push_back
#define fir first
#define sec second
#ifdef DEBUG
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

const int MAXN = 1e6 + 10;

typedef std::pair<int, int> Pii;
typedef int IntAr[MAXN];

int N, M, dfs_clock, totscc, top, T;
IntAr dfn, low, odgr, idgr, col, S, repr, vis, match;
std::vector<int> OG[MAXN], G[MAXN], noni, nono;
std::vector<int>::iterator cur[MAXN];
std::unordered_set<long long> E;
std::vector<Pii> mch;

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; !isdigit(ch); ch = gch());
			for (x = 0; isdigit(ch); ch = gch())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
void tarjan(int u);
void dfs(int u);

int main() {
	using FastIO::read;

	read(N), read(M);
	for (int u, v; M--; ) {
		read(u), read(v);
		OG[u].pb(v);
	}

	for (int i = 1; i <= N; i++) {
		if (!dfn[i]) tarjan(i);
	}
	if (totscc == 1) {
		puts("0");
		return 0;
	}
	for (int i = 1; i <= N; i++) {
		for (int v : OG[i]) {
			long long e = i * 10000000LL + v;
			if (col[i] == col[v] || E.count(e)) continue;
			G[col[i]].pb(col[v]), E.insert(e);
			++odgr[col[i]], ++idgr[col[v]];
		}
	}
	for (int i = 1; i <= totscc; i++) cur[i] = G[i].begin();
	int totni = 0, totno = 0;
	for (int i = 1; i <= totscc; i++) {
		if (!idgr[i]) {
			T = -1;
			dfs(i);
			if (~T) {
				mch.pb(Pii(i, T));
				match[i] = match[T] = 1;
			}
			++totni;
		}
		if (!odgr[i]) ++totno;
	}
	debug(" mch.size = %d\n", (int)mch.size());
	for (int i = 1; i <= totscc; i++) {
		if (match[i]) continue;
		if (!idgr[i]) noni.pb(i);
		if (!odgr[i]) nono.pb(i);
	}
	
	printf("%d\n", std::max(totni, totno));
	debug(" totscc = %d, totni = %d, totno = %d\n", totscc, totni, totno);
	debug(" noni.size = %d, nono.size = %d\n", (int)noni.size(), (int)nono.size());
	int ocnt = 0;
	for (int i = 0; i + 1 < (int)mch.size(); i++) {
		printf("%d %d\n", repr[mch[i].sec], repr[mch[i + 1].fir]);
		++ocnt;
	}
	std::vector<int> V;
	int f = 1;
	for (int i = 0; i < (int)noni.size() && i < (int)nono.size(); i++) {
		if (noni[i] == nono[i]) V.pb(i);
		else if (f) V.pb(i), f = 0;
	}
	for (int i = 0; i + 1 < (int)V.size(); i++) {
		std::swap(nono[V[i]], nono[V[i + 1]]);
	}
	for (int i = 0; i < (int)noni.size() && i < (int)nono.size(); i++) {
		printf("%d %d\n", repr[nono[i]], repr[noni[i]]);
		++ocnt;
	}
	debug(" ocnt = %d\n", ocnt);
	if (noni.size() == nono.size()) {
		debug("Case %d\n", 1);
		if (mch.size()) {
			printf("%d %d\n", repr[mch.back().sec], repr[mch.front().fir]);
			++ocnt;
		}
	}
	else if (noni.size() < nono.size()) {
		debug("Case %d\n", 2);
		debug(" mch.size = %d\n", (int)mch.size());
		printf("%d %d\n", repr[mch.back().sec], repr[nono[noni.size()]]);
		++ocnt;
		for (int i = noni.size(); i + 1 < (int)nono.size(); i++) {
			printf("%d %d\n", repr[nono[i]], repr[nono[i + 1]]);
			++ocnt;
		}
		printf("%d %d\n", repr[nono[(int)nono.size() - 1]], repr[mch[0].fir]);
		++ocnt;
	}
	else {
		debug("Case %d\n", 3);
		printf("%d %d\n", repr[mch.back().sec], repr[noni[nono.size()]]);
		++ocnt;
		for (int i = nono.size(); i + 1 < (int)noni.size(); i++) {
			printf("%d %d\n", repr[noni[i]], repr[noni[i + 1]]);
			++ocnt;
		}
		printf("%d %d\n", repr[noni[(int)noni.size() - 1]], repr[mch[0].fir]);
		++ocnt;
	}
	debug(" ocnt = %d\n", ocnt);
	assert(ocnt == std::max(totni, totno));
	return 0;
}

void tarjan(int u) {
	dfn[u] = low[u] = ++dfs_clock;
	S[top++] = u;
	for (int v : OG[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
		}
		else if (!col[v]) low[u] = std::min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		repr[col[u] = ++totscc] = u;
		for (; top && S[top - 1] != u; --top) col[S[top - 1]] = totscc;
		--top;
	}
}

void dfs(int u) {
	if (match[u]) return;
	vis[u] = 1;
	if (!odgr[u]) return (void)(T = u);
	for (std::vector<int>::iterator & it = cur[u]; it != G[u].end(); ++it) {
		if (!vis[*it]) dfs(*it);
		if (~T) return;
	}
}
