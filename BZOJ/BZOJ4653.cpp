#include <algorithm>
#include <cstdio>

const int kMaxn = 5e5 + 10, kInf = 0x3f3f3f3f;

struct Seg {
	int l, r, len;
	bool operator<(const Seg & s) const {
		return len < s.len;
	}
} S[kMaxn];

int n, m, totn;
int mp[kMaxn << 1];

namespace smt {
	struct Node {
		int max, tag;
		void operator+=(int d) {
			max += d, tag += d;
		}
	} T[kMaxn << 2];
	
	inline int Id(int l, int r) { return l + r | l != r; }
	inline int Query() { return T[Id(1, totn)].max; }
	void Modify(int l, int r, int ql, int qr, int d);
}

int main() {
	scanf("%d%d", &n, &m);
	int maxl = 0, minl = kInf;
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &S[i].l, &S[i].r);
		mp[totn++] = S[i].l, mp[totn++] = S[i].r;
		S[i].len = S[i].r - S[i].l + 1;
		maxl = std::max(maxl, S[i].len);
		minl = std::min(minl, S[i].len);
	}

	std::sort(S, S + n);
	std::sort(mp, mp + totn);
	totn = std::unique(mp, mp + totn) - mp;
	for (int i = 0; i < n; i++) {
		S[i].l = std::lower_bound(mp, mp + totn, S[i].l) - mp + 1;
		S[i].r = std::lower_bound(mp, mp + totn, S[i].r) - mp + 1;
	//	printf(" i%d [%d, %d]\n", i, S[i].l, S[i].r);
	}
	int l = 0, r = 0;
	for (; r < n && smt::Query() < m; ++r)
		smt::Modify(1, totn, S[r].l, S[r].r, 1);
//	printf(" %d\n", smt::Query());
	if (r == n && smt::Query() < m) { puts("-1"); return 0; }
	int ans = S[r - 1].len - S[l].len;
	while (r < n) {
		smt::Modify(1, totn, S[l].l, S[l].r, -1);
		for (++l; r < n && smt::Query() < m; ++r)
			smt::Modify(1, totn, S[r].l, S[r].r, 1);
		ans = std::min(ans, S[r - 1].len - S[l].len);
	} printf("%d\n", ans);
	return 0;
}

namespace smt {
	void PushDown(int l, int m, int r) {
		int u = Id(l, r);
		if (!T[u].tag) return;
		T[Id(l, m)] += T[u].tag, T[Id(m + 1, r)] += T[u].tag;
		T[u].tag = 0;
	}
	void Modify(int l, int r, int ql, int qr, int d) {
		int cur = Id(l, r);
		if (ql <= l && r <= qr) return (void)(T[cur] += d);
		int mid = l + r >> 1;
		PushDown(l, mid, r);
		if (ql <= mid) Modify(l, mid, ql, qr, d);
		if (qr > mid) Modify(mid + 1, r, ql, qr, d);
		T[cur].max = std::max(T[Id(l, mid)].max,
				T[Id(mid + 1, r)].max);
	}
}
