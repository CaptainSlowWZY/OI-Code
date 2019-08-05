#include <algorithm>
#include <cstdio>
#include <vector>

const int kMaxn = 1e6 + 10;

typedef int IAr[kMaxn];
typedef long long LL;

int n, m;
IAr F, head;
LL W[kMaxn];
std::vector<int> pos[kMaxn];

namespace smt {
	void Modify(int l, int r, int ql, int qr, LL d);
	LL Query(int l, int r, int ql, int qr);
}

signed main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) pos[i].push_back(0);
	for (int i = 1; i <= n; i++) {
		scanf("%d", F + i);
		pos[F[i]].push_back(i);
	}
	for (int i = 1; i <= m; i++) scanf("%lld", W + i);
	
	LL ans = 0;
	for (int c, i = 1; i <= n; i++) {
		c = F[i];
		if (head[c]) {
			smt::Modify(1, n, pos[c][head[c] - 1] + 1,
					pos[c][head[c]], -W[c]);
		} ++head[c];
		smt::Modify(1, n, pos[c][head[c] - 1] + 1,
				pos[c][head[c]], W[c]);
		ans = std::max(ans, smt::Query(1, n, 1, i));
	} printf("%lld\n", ans);
	return 0;
}

namespace smt {
	struct Node {
		LL max, tag;
		void operator+=(LL d) { max += d, tag += d; }
	} T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
	void PushDown(int l, int m, int r) {
		Node & u = T[Id(l, r)];
		if (!u.tag) return;
		T[Id(l, m)] += u.tag, T[Id(m + 1, r)] += u.tag;
		u.tag = 0;
	}
	void Modify(int l, int r, int ql, int qr, LL d) {
		int cur = Id(l, r);
		if (ql <= l && r <= qr) return T[cur] += d;	
		int mid = l + r >> 1;
		PushDown(l, mid, r);
		if (ql <= mid) Modify(l, mid, ql, qr, d);
		if (qr > mid) Modify(mid + 1, r, ql, qr, d);
		T[cur].max = std::max(T[Id(l, mid)].max,
				T[Id(mid + 1, r)].max);
	}
	LL Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[Id(l, r)].max;
		int mid = l + r >> 1; LL res = 0;
		PushDown(l, mid, r);
		if (ql <= mid) res = Query(l, mid, ql, qr);
		if (qr > mid) res = std::max(res,
				Query(mid + 1, r, ql, qr));
		return res;
	}
}	
