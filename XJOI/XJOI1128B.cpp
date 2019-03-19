#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int kMaxn = 5e5 + 5;

int n, X[kMaxn], max[kMaxn];

namespace smt {
	LL min[kMaxn << 2];
	void Init();
	void Extend(int, LL);
}

int main() {	
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", X + i);
		max[i] = std::max(max[i - 1], X[i]);
	}

	smt::Init();

	for (int i = n; i > 0; i--) {
		smt::Extend(X[i], max[i] - X[i]);
	}
	printf("%lld\n", smt::min[1]);
	return 0;
}

#define lson (rt << 1)
#define rson (rt << 1 | 1)

namespace smt {
	struct Tag {
		LL cov, k, b;

		Tag(LL cov_ = -1, LL k_ = 0, LL b_ = 0) :
			cov(cov_), k(k_), b(b_) {}
		void operator+=(const Tag & t) {
			~t.cov ? *this = t : (k += t.k, b += t.b);
		}
	} T[kMaxn << 2];
	int tot, ql, qr, dis[kMaxn];

	void Init() {
		memcpy(dis + 1, X + 1, sizeof(int) * (tot = n));
		std::sort(dis, dis + ++tot);
		tot = std::unique(dis, dis + tot) - dis;
	}
	void Add(int rt, int l, const Tag & t) {
		T[rt] += t;
		min[rt] = (~t.cov ? t.cov : min[rt]) +
			1ll * dis[l] * t.k + t.b;
	}
	void PushDown(int rt, int l, int mid) {
		Add(lson, l, T[rt]);
		Add(rson, mid, T[rt]);
		T[rt] = Tag();
	}
	void Modify(int rt, int l, int r, const Tag & t) {
		if (l >= qr || ql >= r) return;
		if (ql <= l && r <= qr) return Add(rt, l, t);
		int mid = l + r >> 1;
		PushDown(rt, l, mid);
		Modify(lson, l, mid, t);
		Modify(rson, mid, r, t);
		min[rt] = min[lson];
	}
	LL Q(int rt, int l, int r) {
		if (r - l == 1) return min[rt];
		int mid = l + r >> 1;
		PushDown(rt, l, mid);
		return ql < mid ? Q(lson, l, mid) : Q(rson, mid, r);
	}
	int Find(int rt, int l, int r, LL bd) {
		if (min[rt] >= bd) return -1;
		if (r - l == 1) return l;
		int mid = l + r >> 1;
		PushDown(rt, l, mid);
		int ret = Find(rson, mid, r, bd);
		if (~ret) return ret;
		return Find(lson, l, mid, bd);
	}
	void Extend(int xi, LL del) {
		xi = std::lower_bound(dis, dis + tot, xi) - dis;
		ql = xi;
		LL fxi = Q(1, 0, tot);
		ql = xi, qr = tot;
		Modify(1, 0, tot, Tag(-1, 1, -dis[xi]));
		int mid = Find(1, 0, tot, fxi - del) + 1;
		if (mid) {
			ql = 0, qr = mid;
			Modify(1, 0, tot, Tag(-1, 0, del));
		}
		if (mid < xi) {
			ql = mid, qr = xi;
			Modify(1, 0, tot, Tag(fxi));
		}
	}
}
