// Luogu P3345
// ZJOI 2015
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#define pb push_back
#define fir first
#define sec second
#define rg register
#define gch getchar
#define pch putchar
#define forto(GR, U) for (auto & e : GR.G[U])

const int MAXN = 1e5 + 10;
const int LgM = 18;

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef int IntAr[MAXN];
typedef LL LLAr[MAXN];

struct Graph {
	std::vector<Pii> G[MAXN];

	void adde(int u, int v, int c) {
		G[u].pb(Pii(v, c));
	}
} OT, VT;

int N, Q, M, cntr, GrvtCntr, best, totsz, pw[LgM], Log[MAXN << 1], ST[MAXN << 1][LgM];
IntAr sz, vis, dep, dfn, fa, mxsz;
LLAr ds1, ds2, sumd;

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), pch('\n');
		}
}

void initot();
void rebuild(int);
void modify(int, int);
LL query(int);

int main() {
	using FastIO::read;

	read(N), read(Q);
	for (int i = 1, u, v, c; i < N; i++) {
		read(u), read(v), read(c);
		OT.adde(u, v, c);
		OT.adde(v, u, c);
	}

	initot();
	rebuild(GrvtCntr);

	for (int u, e; Q--; ) {
		read(u), read(e);
		modify(u, e);
		FastIO::writeln(query(GrvtCntr));
	}

	return 0;
}

void dfsot(int u, int fa) {
	ST[dfn[u] = ++M][0] = dep[u];
	forto(OT, u) {
		if (e.fir == fa) continue;
		dep[e.fir] = dep[u] + e.sec;
		dfsot(e.fir, u);
		ST[++M][0] = dep[u];
	}
}

void fctr(int u, int fa) {
	sz[u] = 1, mxsz[u] = 0;
	forto(OT, u) {
		if (vis[e.fir] || e.fir == fa) continue;
		fctr(e.fir, u);
		mxsz[u] = std::max(mxsz[u], sz[e.fir]);
		sz[u] += sz[e.fir];
	}
	mxsz[u] = std::max(mxsz[u], totsz - sz[u]);
	if (mxsz[u] < mxsz[cntr] || !cntr) cntr = u;
}

void rebuild(int u) {
	vis[u] = 1;
	forto(OT, u) {
		if (vis[e.fir]) continue;
		totsz = sz[e.fir], cntr = 0;
		fctr(e.fir, u);
		VT.adde(u, cntr, e.fir), fa[cntr] = u;
		rebuild(cntr);
	}
}

void initot() {
	dfsot(1, 0);
	pw[0] = 1, Log[0] = -1;
	for (int i = 1; i < LgM; i++) pw[i] = pw[i - 1] << 1;
	for (int i = 1; i <= M; i++) Log[i] = Log[i >> 1] + 1;	
	for (int j = 1; j <= Log[M]; j++)
		for (int i = 1, lim = M - pw[j] + 1; i <= lim; i++)
			ST[i][j] = std::min(ST[i][j - 1], ST[i + pw[j - 1]][j - 1]);
	totsz = N, cntr = 0;
	fctr(1, 0);
	GrvtCntr = cntr;
	fctr(GrvtCntr, 0);
}

LL dist(int u, int v) {
	if (dfn[u] > dfn[v]) std::swap(u, v);
	int lg = Log[dfn[v] - dfn[u] + 1];
	return (LL)dep[u] + dep[v] - (std::min(ST[dfn[u]][lg], ST[dfn[v] - pw[lg] + 1][lg]) << 1);
}

void modify(int u, int e) {
	sumd[u] += e;
	for (int v = u; fa[v]; v = fa[v]) {
		LL dlt = dist(fa[v], u) * e;
		ds1[fa[v]] += dlt;
		ds2[v] += dlt;
		sumd[fa[v]] += e;
	}
}

LL calc(int u) {
	LL ret = ds1[u];
	for (int v = u; fa[v]; v = fa[v])
		ret += ds1[fa[v]] - ds2[v] + dist(fa[v], u) * (sumd[fa[v]] - sumd[v]);
	return ret;
}

LL query(int u) {
	LL ret = calc(u);
	forto(VT, u) {
		LL tmp = calc(e.sec);
		if (tmp < ret) return query(e.fir);
	}
	return ret;
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0;
			rg char ch = gch();
			rg int f = 0;
			for (; ch < '0' || ch > '9'; ch = gch())
				f |= ch == '-';
			for (; ch >= '0' && ch <= '9'; ch = gch())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
	template <typename T>
		void write(T x) {
			if (!x) return (void)pch('0');
			if (x < 0) pch('-'), x = -x;
			rg int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) pch(arr[--len] ^ '0');
		}
}
