#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back

const int kMaxn = 1e5 + 10;

int n, c, k;
int A[kMaxn], head[kMaxn];
std::vector<int> pos[kMaxn];

namespace smt {
	void Build(int l, int r);
	void Modify(int l, int r, int ql, int qr, int del);
	int Query(int l, int r);
}

int main() {
	while (~scanf("%d%d%d", &n, &c, &k)) {
		for (int i = 1; i <= c; i++) {
			pos[i].clear(), pos[i].pb(0), head[i] = 1;
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", A + i);
			pos[A[i]].pb(i);
		}

		smt::Build(1, n);
		for (int i = 1; i <= c; i++) {
			const std::vector<int> & ps = pos[i];
			if (ps.size() == 1) {
				smt::Modify(1, n, 1, n, 1);
				continue;
			}
			if (ps[1] > 1) {
				smt::Modify(1, n, 1, ps[1] - 1, 1);
			}
			if (ps.size() > k) {
				smt::Modify(1, n, ps[k], n, 1);
			}
		}
		int ans = 0;
		for (int i = 1, r; i <= n; i++) {
		//	printf(" l move to %d\n", i);
			if (~(r = smt::Query(1, n)))
				ans = std::max(ans, r - i + 1);
		//	printf("  r = %d\n", r);
			const std::vector<int> & ps = pos[A[i]];
			int & hd = head[A[i]];
			if (ps[hd - 1] + 1 <= ps[hd] - 1) {
				smt::Modify(1, n, ps[hd - 1] + 1, ps[hd] - 1, -1);
			}
            if (hd + k <= ps.size()) {
                smt::Modify(1, n, ps[hd + k - 1], n, -1);
			}
			if (++hd < ps.size()) {
				if (ps[hd - 1] + 1 <= ps[hd] - 1) {
					smt::Modify(1, n, ps[hd - 1] + 1, ps[hd] - 1, 1);
				}
				if (hd + k <= ps.size()) {
					smt::Modify(1, n, ps[hd + k - 1], n, 1);
				}
			} else {
				if (ps[hd - 1] + 1 <= n)
					smt::Modify(1, n, ps[hd - 1] + 1, n, 1);
			}	
		}
		printf("%d\n", ans);
	}
	return 0;
}

namespace smt {
	struct Node {
		int max, tag;
	} T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
	void Build(int l, int r) {
		int u = Id(l, r);
		T[u].max = T[u].tag = 0;
		if (l == r) return;
		int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r);
	}
	void PushDown(int l, int m, int r) {
		int u = Id(l, r);
		if (T[u].tag) {
			int ls = Id(l, m), rs = Id(m + 1, r);
			T[ls].max += T[u].tag, T[rs].max += T[u].tag;
			T[ls].tag += T[u].tag, T[rs].tag += T[u].tag;
			T[u].tag = 0;
		}
	}
	void Modify(int l, int r, int ql, int qr, int del) {
	//	if (l == 1 && r == n)
	//		printf(" [%d, %d] += %d\n", ql, qr, del);
		int cur = Id(l, r);
		if (ql <= l && r <= qr) {
			T[cur].max += del, T[cur].tag += del;
		//	printf("  after upd [%d, %d] max is %d\n", l, r, T[cur].max);
			return;
		}
		int mid = l + r >> 1;
		PushDown(l, mid, r);
		if (ql <= mid) Modify(l, mid, ql, qr, del);
		if (qr > mid) Modify(mid + 1, r, ql, qr, del);
		T[cur].max = std::max(T[Id(l, mid)].max,
			T[Id(mid + 1, r)].max);
	//	printf("  after upd [%d, %d] max is %d\n", l, r, T[cur].max);
	}
	int Query(int l, int r) {
		if (l == r) return l;
		if (T[Id(l, r)].max < c) return -1;
		int mid = l + r >> 1, ls = Id(l, mid), rs = Id(mid + 1, r);
		PushDown(l, mid, r);
		int res = -1;
		if (T[rs].max >= c) res = std::max(res, Query(mid + 1, r));
		if (T[ls].max >= c && res == -1) return Query(l, mid);
		return res;
	}
}
