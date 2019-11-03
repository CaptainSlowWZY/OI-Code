#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>

namespace fast_io {
	const int MAX_SIZE = 1 << 15;
	char *l, *r, buf[ MAX_SIZE ];
	inline int gc() {
		if( l == r ) {
			l = buf, r = l + fread(buf, 1, MAX_SIZE, stdin);
			if( l == r) return -1;
		}
		return *l++; 
	}
	inline void Read( int &x ) {
		char c = gc();
		for(; c < 48 || c > 57; c = gc() );
		for( x = 0; c > 47 && c < 58; c = gc() )
			x = ( x << 3 ) + ( x << 1 ) + ( c ^ 48 );
		return;
	}
}
const int kMaxn = 1e5 + 5, kLg = 18;

typedef int Arr[kMaxn << 1];

struct Edge {
	int u, v, c;
	bool operator<(const Edge & e) const { return c < e.c; }
} E[kMaxn * 5];

int n, m, q, dfsc, cntv;
Arr A, H, fa, idfn, odfn;
int F[kMaxn << 1][kLg], ch[kMaxn << 1][2];

namespace ds {
	int tot, rt[kMaxn];

	void Build();
	int _Q(int, int, int, int, int);
	inline int Qry(int l, int r, int k) {
		return _Q(rt[l - 1], rt[r], 1, tot, k);
	}
}
inline int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
void Dfs(int);

int main() {
//	scanf("%d%d%d", &n, &m, &q);
	using fast_io::Read;
	Read(n); Read(m); Read(q);
	int mxh = 0;
	for (int i = 1; i <= n; ++i) {
		Read(H[i]); mxh = std::max(mxh, H[i]);
	}
	for (int i = 0; i < m; ++i) {
		Read(E[i].u); Read(E[i].v); Read(E[i].c);
//		scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].c);
	}
	std::sort(E, E + m); cntv = n;
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int i = 0, cnt = 0, x, y; i < m; ++i) {
		if ((x = Find(E[i].u)) == (y = Find(E[i].v))) continue;
		H[++cntv] = E[i].c;
		fa[cntv] = fa[x] = fa[y] = cntv;
		ch[cntv][0] = x, ch[cntv][1] = y;
		if (++cnt == n - 1) break;
	}
	for (int i = cntv; i; --i) if (!idfn[i]) Dfs(Find(i));
	ds::Build();
	for (int x, v, k, la = 0; q--; ) {
	//	scanf("%d%d%d", &v, &x, &k);
		Read(v); Read(x); Read(k);
		if (~la) { v ^= la, x ^= la, k ^= la; }
		if (!k) { printf("%d\n", la = mxh); continue; }
		for (int i = kLg - 1; ~i; --i)
			if (F[v][i] && H[F[v][i]] <= x) v = F[v][i];
		//	printf(" jump to %d, [%d, %d]\n", v, idfn[v], odfn[v]);
		printf("%d\n", la = ds::Qry(idfn[v], odfn[v], k));
	} return 0;
}

namespace ds {
	const int kMaxv = kMaxn * 20;
	int cntn;
	int ls[kMaxv], rs[kMaxv], C[kMaxv], mp[kMaxn];

	inline int New(int u = 0) {
		ls[++cntn] = ls[u], rs[cntn] = rs[u];
		C[cntn] = C[u]; return cntn;
	}
	int Grow(int l, int r) {
		int u = New(), md = l + r >> 1;
		if (l == r) return u;
		ls[u] = Grow(l, md); rs[u] = Grow(md + 1, r);
		return u;
	}
	int Ins(int pr, int l, int r, int v) {
		int u = New(pr), md = l + r >> 1; ++C[u];
		if (l == r) return u;
		if (v <= md) ls[u] = Ins(ls[pr], l, md, v);
		else rs[u] = Ins(rs[pr], md + 1, r, v);
		return u;
	}
	void Build() {
		memcpy(mp + 1, A + 1, sizeof(int) * n);
		std::sort(mp + 1, mp + (tot = n) + 1);
		tot = std::unique(mp + 1, mp + tot + 1) - mp - 1;
		rt[0] = Grow(1, tot);
		for (int i = 1; i <= n; ++i) rt[i] = Ins(rt[i - 1], 1, tot,
				std::lower_bound(mp + 1, mp + tot + 1, A[i]) - mp);
	}
	int _Q(int pr, int nx, int l, int r, int k) {
		if (k > C[nx] - C[pr]) return -1;
		if (l == r) return mp[l];
		int cr = C[rs[nx]] - C[rs[pr]], md = l + r >> 1;
		if (cr >= k) return _Q(rs[pr], rs[nx], md + 1, r, k);
		return _Q(ls[pr], ls[nx], l, md, k - cr);
	}
}

#define LS ch[u][0]
#define RS ch[u][1]

void Dfs(int u) {
	for (int i = 1; i < kLg && F[u][i - 1]; ++i)
		F[u][i] = F[F[u][i - 1]][i - 1];
	if (!LS) {
		assert(u <= n);
		return (void)(A[idfn[u] = odfn[u] = ++dfsc] = H[u]);
	}
	F[LS][0] = u; Dfs(LS); F[RS][0] = u; Dfs(RS);
	idfn[u] = idfn[LS], odfn[u] = odfn[RS];
}
