#pragma GCC optimize(2)
#include <cstdio>

const int kMaxn = 1e5 + 5, kMaxm = 21, kMod = 1e9 + 7;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }
inline void Ups(int & a, int b) { a = Sub(a, b); }
inline void Upm(int & a, int b) { a = Mul(a, b); }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

struct Node {
	int v, a, m;
	Node() : v(0), a(0), m(1) {}
};
struct Smt {
	Node T[kMaxn << 2];
//	void build(int, int, int, int);
	void modify(int, int, int, int, int, int, int);
	void push_down(int);
	int query(int, int, int, int);
} dp[kMaxm];

int n, m, A[kMaxn], C[kMaxm][kMaxm], buf[kMaxm];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = C[0][0] = 1; i <= m; ++i) for (int j = C[i][0] = 1; j <= i; ++j) C[i][j] = Add(C[i - 1][j - 1], C[i - 1][j]);
	dp[0].modify(1, 0, n, 0, 0, 1, 1);
	for (int i = 0, ai; i < n; ++i) {
		scanf("%d", &ai);
		for (int j = 0, del; j <= m; ++j) {
			dp[j].modify(1, 0, n, ai, n, 0, 2);
		//	printf(" j = %d\n", j);
		//	printf("  del = %d\n", del);
			buf[j] = dp[j].query(1, 0, n, ai - 1);
			for (int k = del = 0; k <= j; ++k) Upa(del, Mul(C[j][k], buf[k]));
			dp[j].modify(1, 0, n, ai, ai, del, 1);
		//	printf("   T[ai - 1] = %d\n", dp[j].query(1, 0, n, ai - 1));
		}
	} printf("%d\n", dp[m].T[1].v); return 0;
}

#define LSON (rt << 1)
#define RSON (rt << 1 | 1)

/* void Smt::build(int rt, int l, int r, int t) {
	if (l == r) return (void)(T[rt] = (Node){(!l && !r) * t, 0, 1});
	int mid = l + r >> 1;
	build(LSON, l, mid, t); build(RSON, mid + 1, r, t); T[rt].v = Add(T[LSON].v, T[RSON].v), T[rt].m = 1;
} */

void Smt::push_down(int rt) {
	if (!T[rt].a && T[rt].m == 1) return;
	Upm(T[LSON].m, T[rt].m); Upm(T[LSON].a, T[rt].m); Upa(T[LSON].a, T[rt].a); Upm(T[LSON].v, T[rt].m); Upa(T[LSON].v, T[rt].a);
	Upm(T[RSON].m, T[rt].m); Upm(T[RSON].a, T[rt].m); Upa(T[RSON].a, T[rt].a); Upm(T[RSON].v, T[rt].m); Upa(T[RSON].v, T[rt].a);
	T[rt].m = 1, T[rt].a = 0;
}

void Smt::modify(int rt, int l, int r, int ql, int qr, int _a, int _m) {
	if (ql <= l && r <= qr) { Upm(T[rt].m, _m); Upm(T[rt].a, _m); Upa(T[rt].a, _a); Upm(T[rt].v, _m); Upa(T[rt].v, _a); return; }
	push_down(rt);
	int mid = l + r >> 1;
	if (ql <= mid) modify(LSON, l, mid, ql, qr, _a, _m);
	if (qr > mid) modify(RSON, mid + 1, r, ql, qr, _a, _m);
	T[rt].v = Add(T[LSON].v, T[RSON].v);
}

int Smt::query(int rt, int l, int r, int p) {
	if (r <= p) return T[rt].v;
	push_down(rt);
	int mid = l + r >> 1;
	if (p <= mid) return query(LSON, l, mid, p);
	return Add(T[LSON].v, query(RSON, mid + 1, r, p));
}
