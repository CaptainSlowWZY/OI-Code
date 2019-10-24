#include <algorithm>
#include <cstdio>

#define fi first
#define se second
#define ALL(_) _.begin(), _.end()

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef std::pair<LL, int> Pli;

const int kV = 1e6 + 5, kMaxn = 2e5 + 5, kInf = 0x3f3f3f3f;

struct Info {
	int m, lem, rim;
	Info(int m_ = -1, int l = 0, int r = 0) :
		m(m_), lem(l), rim(r){}
};

int n, H[kMaxn];
std::vector<int> pos[kV];
LL ans1, ans2;

namespace smt { int Build(int l, int r); }
Info Solve(int l, int r);

int main() {
	scanf("%d", &n);
	int mxh = 0, mnh = kInf, T;
	for (int i = 1; i <= n; ++i) {
	 	scanf("%d", H + i);
		pos[H[i]].push_back(i);
		mxh = std::max(mxh, H[i]);
		mnh = std::min(mnh, H[i]);
	} scanf("%d", &T);
	H[0] = H[n + 1] = kInf;
	for (int i = 1; i < n; ++i)
		ans1 += 1ll * i * (n - i);
	smt::Build(1, n);
	Solve(1, n);
	if (T == 1) printf("%lld\n", ans1);
	else printf("%lld %lld\n", ans1, ans2);
	return 0;
}

namespace smt {
	int T[kMaxn << 1];
	inline int Id(int l, int r) { return l + r | l != r; }
	int Build(int l, int r) {
		int u = Id(l, r);
		if (l == r) return T[u] = H[l];
		int mid = l + r >> 1;
		return T[u] = std::min(Build(l, mid), Build(mid + 1, r));
	}
	int Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[Id(l, r)];
		int mid = l + r >> 1;
		if (qr <= mid) return Query(l, mid, ql, qr);
		if (ql > mid) return Query(mid + 1, r, ql, qr);
		return std::min(Query(l, mid, ql, qr),
				Query(mid + 1, r, ql, qr));
	}
}

namespace bit {
	Pli T[kMaxn];

	inline void operator+=(Pli & a, const Pli & b) {
		a.fi += b.fi, a.se += b.se;
	}
	inline Pli operator-(const Pli & a, const Pli & b) {
		return {a.fi - b.fi, a.se - b.se};
	}
	void Add(int p, int v) {
		for (; p <= n; p += p & -p) T[p] += {v, 1};
	}
	Pli Sum(int p) {
		Pli res = {0, 0};
		for (; p; p &= p - 1) res += T[p];
		return res;
	}
	inline Pli Sum(int l, int r) {
		return l <= r ? Sum(r) - Sum(l - 1) : Pli(0, 0);
	}
}

Info Solve(int l, int r) {
	if (l >= r) {
		if (l == r) bit::Add(l, H[l]);
		return {l == r ? H[l] : -1, l, l};
	}
//	{leftmost, rightmost}
	int m = smt::Query(1, n, l, r);
	auto be = std::lower_bound(ALL(pos[m]), l),
		 en = std::upper_bound(ALL(pos[m]), r),
		 la = en, be0 = be; --la;
	Info res = {m, *be, *la},
		 lp = *be > l ? Solve(l, *be - 1) : Info(),
		 rp = *la < r ? Solve(*la + 1, r) : Info();
/*	printf(" solve [%d, %d], min %d, be %d, la %d\n   lp(%d, %d), rp(%d, %d)\n",
			l, r, m, *be, *la, lp.m, lp.rim, rp.m, rp.lem);
	printf("    left part  %d\n", *be - lp.rim - (H[*be - 1] > lp.m));
	printf("    right part %d\n", rp.lem - *la - (H[*la + 1] > rp.m)); */
	if (~lp.m) { ans2 += *be - lp.rim; res.lem = lp.rim; }
	if (~rp.m) { ans2 += rp.lem - *la; res.rim = rp.lem; }
	using namespace bit;
//	printf("    self part %d\n", *la - *be);
	ans2 += *la - *be, Add(*be, m);
	for (la = be, ++be; be != en; ++la, Add(*be++, m))
		Solve(*la + 1, *be - 1);
	be = la = be0;
	Pli lt = Sum(l, *be - 1), rt = Sum(*be + 1, r);
	ans1 += (rt.fi - (LL)m * rt.se) * (lt.se + 1) +
		(lt.fi - (LL)m * lt.se) * (rt.se + 1);
	for (++be; be != en; ++be, ++la) {
		lt = Sum(*la + 1, *be - 1), rt = Sum(*be + 1, r);
		ans1 += (rt.fi - (LL)m * rt.se) * (lt.se + 1) +
			(lt.fi - (LL)m * lt.se) * (rt.se + 1);
	}
	return res;
}
