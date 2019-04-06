// FJOI2016
#include <cstdio>
#include <algorithm>

const int kMaxn = 1e5 + 5;

int n, mpsz, m;
int A[kMaxn], mp[kMaxn];

namespace ds {
	int root[kMaxn];
	int Build(int l, int r);
	int Modify(int cur, int l, int r, int val, int pos);
	int Query(int hd, int tl, int l, int r, int ub);
}
inline int Rank(int x) {
	return std::upper_bound(mp + 1, mp + 1 + mpsz, x) - mp - 1;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", A + i);
		mp[i] = A[i];
	}
	
	std::sort(mp + 1, mp + n + 1);
	mpsz = std::unique(mp + 1, mp + n + 1) - mp - 1;
	ds::root[0] = ds::Build(1, mpsz);
	for (int i = 1; i <= n; i++) {
		using namespace ds;
		root[i] = Modify(root[i - 1], 1, mpsz, A[i], Rank(A[i]));
	}

	scanf("%d", &m);
	for (int i = 1, l, r; i <= m; i++) {
		using namespace ds;
		scanf("%d%d", &l, &r);
		int ans = 1;
		for (int sum; ; ) {	
			sum = Query(root[l - 1], root[r], 1, mpsz, Rank(ans));
		//	printf(" ans = %d, sum = %d\n", ans, sum);
			if (ans > sum) break;
			ans = sum + 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}

#define lson(_) T[_].lson
#define rson(_) T[_].rson
#define sum(_) T[_].sum

namespace ds {
	struct Node {
		int sum, lson, rson;
	} T[kMaxn << 18];
	int pit = 1;

	int Build(int l, int r) {
		int rt = pit++;
		if (l != r) {
			int mid = l + r >> 1;
			lson(rt) = Build(l, mid), rson(rt) = Build(mid + 1, r);
		}
		return rt;
	}
	int Modify(int cur, int l, int r, int val, int pos) {
		int rt = pit++, mid = l + r >> 1;
		T[rt].sum = T[cur].sum + val;
		lson(rt) = lson(cur), rson(rt) = rson(cur);
		if (l == r) return rt;
		if (pos <= mid) {
			lson(rt) = Modify(lson(cur), l, mid, val, pos);
		} else {
			rson(rt) = Modify(rson(cur), mid + 1, r, val, pos);
		}
		return rt;
	}
	int Query(int hd, int tl, int l, int r, int ub) {
		if (!ub) return 0;
		if (r <= ub) return sum(tl) - sum(hd);
		int mid = l + r >> 1;
		if (ub > mid) {
			return sum(lson(tl)) - sum(lson(hd)) + 
					Query(rson(hd), rson(tl), mid + 1, r, ub);
		}
		return Query(lson(hd), lson(tl), l, mid, ub);
	}
}
