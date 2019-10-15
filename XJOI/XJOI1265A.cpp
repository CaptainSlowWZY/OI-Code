#include <algorithm>
#include <cstdio>

#define fir first
#define sec second

const int kMaxn = 5e4 + 5;

int n, m;
std::pair<int, int> A[kMaxn];

namespace smt {
	void Init();
	bool Check(int m, int l1, int r1, int l2, int r2);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &A[i].fir); A[i].sec = i;
	} std::sort(A, A + n);
	smt::Init(); scanf("%d", &m);
	for (int l1, r1, l2, r2; m--; ) {
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		--l1, --r1, --l2, --r2;
		int l = 0, r = n + 1;
		for (int mid; r - l > 1; ) {
			mid = l + r >> 1;
			if (smt::Check(mid, l1, r1, l2, r2)) l = mid;
			else r = mid;
		} printf("%d\n", A[l].fir);
	} return 0;
}

namespace smt {
	struct Node {
		int s, ls, rs;
		Node operator+(const Node & n) const {
			return {s + n.s, std::max(ls, s + n.ls),
				std::max(n.rs, rs + n.s)};
		}
	//	void debug() const { printf(" (s %d, ls %d, rs %d)\n", s,ls,rs); }
	} T[kMaxn << 5];
	int sz, rot[kMaxn], ch[kMaxn << 5][2];

#define LSON(_) ch[_][0]
#define RSON(_) ch[_][1]

	void Build(int & rt, int l, int r) {
		rt = ++sz;
		if (l == r) return (void)(T[rt] = {1, 1, 1});
		int mid = l + r >> 1;
		Build(LSON(rt), l, mid); Build(RSON(rt), mid + 1, r);
		T[rt] = T[LSON(rt)] + T[RSON(rt)];
	}
	void Modify(int prv, int & cur, int l, int r, int p) {
		T[cur = ++sz] = T[prv];
		LSON(cur) = LSON(prv); RSON(cur) = RSON(prv);
		if (l == r) return (void)(T[cur] = {-1, -1, -1});
		int mid = l + r >> 1;
		if (p <= mid) Modify(LSON(prv), LSON(cur), l, mid, p);
		else Modify(RSON(prv), RSON(cur), mid + 1, r, p);
		T[cur] = T[LSON(cur)] + T[RSON(cur)];
	}
	void Init() {
		Build(rot[0], 0, --n);
		for (int i = 1; i <= n; ++i)
			Modify(rot[i - 1], rot[i], 0, n, A[i - 1].sec);
	}
	Node Query(int rt, int l, int r, int ql, int qr) {
		if (ql > qr) return {0, 0, 0};
		if (ql <= l && r <= qr) { return T[rt]; }
		int mid = l + r >> 1;
		if (ql > mid) return Query(RSON(rt), mid + 1, r, ql, qr);
		if (qr <= mid) return Query(LSON(rt), l, mid, ql, qr);
		return Query(LSON(rt), l, mid, ql, qr) +
			Query(RSON(rt), mid + 1, r, ql, qr);
	}
	bool Check(int m, int l1, int r1, int l2, int r2) {
		return Query(rot[m], 0, n, l1, r1).rs +
			Query(rot[m], 0, n, r1 + 1, l2 - 1).s +
			Query(rot[m], 0, n, l2, r2).ls >= 0;
	}
}
