#include <algorithm>
#include <cstdio>
#include <vector>
#include <cassert>

#define x first
#define y second
#define pb push_back

typedef long long LL;
typedef std::pair<int, LL> PiL;
typedef std::pair<PiL, int> Line;

const int kMaxn = 2e5 + 10, kSqrtn = 3050;

struct CnvxHul {
	int ptr, top;
	LL x0;
	std::vector<Line> stk;

	void clear() {
		x0 = ptr = top = 0;
	}
	void insert(const Line & l);
	LL calc(LL del);
};

struct Block {
	std::vector<Line> lin;
	CnvxHul hul;
	LL tag, res;
	int lb, ub;

	void init(int fir, int lst);
	void build();
	void modify(int l, int r, LL d);
	LL query(int l, int r);
} B[kSqrtn];

int n, q, totb, bsz, dfs_clock;
int SA[kMaxn], SB[kMaxn], idfn[kMaxn], odfn[kMaxn], id[kMaxn];
std::vector<int> G[kMaxn];

void Dfs(int);

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 2, pi; i <= n; i++) {
		scanf("%d", &pi); G[pi].push_back(i);
	}
	for (int i = 1; i <= n; i++) scanf("%d", SA + i);
	for (int i = 1; i <= n; i++) scanf("%d", SB + i);

	Dfs(1);
	bsz = std::max(1, (int)sqrt(n / 6));
	for (int i = 1; i <= n; i += bsz)
		B[totb++].init(i, std::min(i + bsz, n + 1));

	for (int o, v, x; q--; ) {
		scanf("%d%d", &o, &v);
		if (o == 1) {
			scanf("%d", &x);
			for (int i = 0; i < totb; i++)
				B[i].modify(idfn[v], odfn[v], x);
		} else {
			LL ans = 0;
			for (int i = 0; i < totb; i++)
				ans = std::max(ans, B[i].query(idfn[v], odfn[v]));
			printf("%lld\n", ans);
		}
	}

	return 0;
}

void Block::modify(int l, int r, LL d) {
	if (ub < l || r < lb) return;
	if (l <= lb && ub <= r) {
		res = hul.calc(d), tag += d;
	} else {
		for (auto & i : lin) {
			i.x.y += i.x.x * tag;
			if (l <= i.y && i.y <= r)
				i.x.y += i.x.x * d;
		}
		tag = 0; build();
	}
}

inline LL Fun(const PiL & l, LL x0) {
	return x0 * l.x + l.y;
}

LL Block::query(int l, int r) {
	if (ub < l || r < lb) return 0;
	if (l <= lb && ub <= r) return res;
	LL ret = 0;
	for (auto & i : lin) {
		if (i.y < l || i.y > r) continue;	
		ret = std::max(ret, Fun(i.x, tag));
	}
	return ret;
}

inline double Itrsc(const PiL & p1, const PiL & p2) {
	return (double)(p1.y - p2.y) / (double)(p2.x - p1.x);
}

void CnvxHul::insert(const Line & l) {
	if (top && stk[top - 1].x.x == l.x.x &&
			stk[top - 1].x.y > l.x.y) return;
	for (; top && (l.x.y > stk[top - 1].x.y || 
			l.x.y == stk[top - 1].x.y && l.x.x > stk[top - 1].x.x); --top);
	for (; top > 1 && Itrsc(stk[top - 1].x, stk[top - 2].x) >=
			Itrsc(stk[top - 1].x, l.x); --top);
	if (top < stk.size()) stk[top++] = l;
	else { stk.push_back(l); ++top; }
}


LL CnvxHul::calc(LL del) {
	for (x0 += del; ptr + 1 < top && Fun(stk[ptr].x, x0) <
			Fun(stk[ptr + 1].x, x0); ++ptr);
	return Fun(stk[ptr].x, x0);
}

void Block::init(int fir, int lst) {
	lb = fir, ub = lst;
	for (int i = fir, cur; i < lst; i++) {
		cur = id[i];
		lin.pb({{SB[cur], 1ll * SB[cur] * SA[cur]}, i});
		if (SB[cur] < 0 || SA[cur] < 0)
			lin.pb({{-SB[cur], -1ll * SB[cur] * SA[cur]}, i});
	}
	std::sort(lin.begin(), lin.end());
	build();
}

void Block::build() {
	hul.clear();
	for (auto & l : lin) hul.insert(l);
	res = hul.calc(0);
}

void Dfs(int u) {
	id[idfn[u] = ++dfs_clock] = u;
	for (auto v : G[u]) {
		SA[v] += SA[u], SB[v] += SB[u];
		Dfs(v);
	}
	odfn[u] = dfs_clock;
}
