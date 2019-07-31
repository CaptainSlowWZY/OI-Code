#include <algorithm>
#include <cstdio>
#include <cassert>

const int kMaxn = 1e5 + 10;
const int kBd = 1e6;

namespace smt {
	struct Node {
		int cnt;
		int lson, rson;
	} T[kBd * 40];
#define lson(_) (T[_].lson)
#define rson(_) (T[_].rson)
	int root[kMaxn];
	int size;

	int Build(int l, int r);
	int U(int prv, int l, int r, int val);
	int Q(int prv, int suc, int l, int r, int ql, int qr);
	inline void Insert(int pos, int val) {
		root[pos] = U(root[pos - 1], 1, kBd, val);
	}
	inline int Query(int l, int r, int lb, int ub) {
		return Q(root[l - 1], root[r], 1, kBd, lb, ub);
	}
}

int n, m;

int main() {
	int t, osz;
	smt::size = 0;
	smt::root[0] = smt::Build(1, kBd);
	osz = smt::size;
	for (scanf("%d", &t); t--; ) {
		smt::size = osz;
		scanf("%d%d", &n, &m);
		for (int i = 1, Ai; i <= n; i++) {
			scanf("%d", &Ai);
		//	revmp[i] = A[i];
			smt::Insert(i, Ai);
		}

	//	std::sort(revmp + 1, revmp + 1 + n);
	//	rank = std::unique(revmp + 1, revmp + 1 + n) - revmp - 1;
	/*	for (int i = 1; i <= n; i++) {
			smt::Insert(i, 
				std::lower_bound(revmp + 1, revmp + 1 + rank, A[i]) - revmp);
		}*/
		for (int l, r, p, k, lans = 0; m--; ) {
			scanf("%d%d%d%d", &l, &r, &p, &k);
			l ^= lans, r ^= lans, p ^= lans, k ^= lans;
			assert(l <= r);
			int lb = -1, ub = kBd;
			for (int mid; ub - lb > 1; ) {
				mid = lb + ub >> 1;
				int cnt = smt::Query(l, r, std::max(p - mid, 1),
					std::min(p + mid, kBd));
				if (cnt >= k) ub = mid;
				else lb = mid;
			}
			printf("%d\n", lans = ub);
		}
				
	}
	return 0;
}

namespace smt {
	int Build(int l, int r) {
		int rt = ++size;
		assert(size < kBd * 40);
		T[rt].cnt = 0;
		if (l == r) return rt;
		int mid = l + r >> 1;
		lson(rt) = Build(l, mid);
		rson(rt) = Build(mid + 1, r);
		return rt;
	}
	int U(int prv, int l, int r, int val) {
		int rt = ++size;
		assert(size < kBd * 40);
		lson(rt) = lson(prv), rson(rt) = rson(prv);
		T[rt].cnt = T[prv].cnt + 1;
		if (l == r) return rt;
		int mid = l + r >> 1;
		if (val <= mid) lson(rt) = U(lson(prv), l, mid, val);
		else rson(rt) = U(rson(prv), mid + 1, r, val);
		return rt;
	}
	int Q(int prv, int suc, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[suc].cnt - T[prv].cnt;
		int mid = l + r >> 1, res = 0;
		if (ql <= mid) res = Q(lson(prv), lson(suc), l, mid, ql, qr);
		if (qr > mid) res += Q(rson(prv), rson(suc), mid + 1, r, ql, qr);
		return res;
	}
}
