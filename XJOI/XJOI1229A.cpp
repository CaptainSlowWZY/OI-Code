#include <cstdio>

const int kMaxn = 1e5 + 5;

int n, m;

namespace smt {
	struct Node { int sum, tag; } T[kMaxn << 1];
	inline int Id(int l, int r) { return l + r | l != r; }
	void PushDown(int l, int m, int r);
	void Modify(int l, int r, int ql, int qr);
	inline int Query() { return T[Id(1, n)].sum; }
}

int main() {
	scanf("%d%d", &n, &m);
	++n;
	for (int l, r; m--; ) {
		scanf("%d%d", &l, &r);
		++l, ++r;
		smt::Modify(1, n, l, r);
	} printf("%d\n", n - smt::Query());
	return 0;
}

namespace smt {
	void PushDown(int l, int m, int r) {
		int u = Id(l, r);
		if (!T[u].tag) return;		
		int ls = Id(l, m), rs = Id(m + 1, r);
		T[ls].sum = m - l + 1, T[ls].tag = 1;
		T[rs].sum = r - m, T[rs].tag = 1;
	}
	void Modify(int l, int r, int ql, int qr) {
		int cur = Id(l, r);
		if (ql <= l && r <= qr) {
			T[cur].sum = r - l + 1, T[cur].tag = 1;
			return;
		} int mid = l + r >> 1;
		PushDown(l, mid, r);
		if (ql <= mid) Modify(l, mid, ql, qr);
		if (qr > mid) Modify(mid + 1, r, ql, qr);
		T[cur].sum = T[Id(l, mid)].sum + T[Id(mid + 1, r)].sum;
	}
}
