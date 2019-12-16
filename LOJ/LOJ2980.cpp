// what a fuck thu!
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <initializer_list>

const int kMaxn = 2.5e5 + 5, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }

struct Matrix {
	int r, c, A[4][4];
	Matrix() {}
	Matrix(int _r, int _c) : r(_r), c(_c) {}
	void set(int _r, int _c) { r = _r, c = _c; memset(A, 0, sizeof A); }
	int *operator[](int x) { return A[x]; }
	Matrix operator+(const Matrix & m) const;
	Matrix operator*(const Matrix & m) const;
	void operator*=(const Matrix & m) { *this = m * *this; }
} idmat, op[3], tr;

namespace smt {
	struct Node {
		Matrix val, tag;
		Node() {}
		Node(std::initializer_list<int> arg);
	} T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
	void Build(int l, int r);
	void Modify(int l, int r, int ql, int qr, const Matrix & m);
	Matrix Query(int l, int r, int ql, int qr);
}

int n, m;

int main() {
	idmat.set(4, 4);
	for (int i = 0; i < 4; ++i) idmat[i][i] = 1;
	for (int i = 0; i < 2; ++i) { op[i] = idmat, op[i][i][i + 1] = 1; }
	op[2] = idmat, op[2][2][0] = 1;
	scanf("%d", &n);
	for (int a, b, c, i = 1; i <= n; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		using namespace smt;
		T[Id(i, i)] = Node({a, b, c});
	} scanf("%d", &m); smt::Build(1, n);
	for (int o, l, r, v; m--; ) {	
		scanf("%d%d%d", &o, &l, &r);
		using namespace smt;
		if (o <= 3) Modify(1, n, l, r, op[o - 1]);
		else if (o == 7) {
			tr = Query(1, n, l, r);
			printf("%d %d %d\n", tr[0][0], tr[1][0], tr[2][0]);
		} else {
			scanf("%d", &v);
			tr = idmat;
			if (o == 4) tr[0][3] = v;
			else if (o == 5) tr[1][1] = v;
			else if (o == 6) { tr[2][2] = 0, tr[2][3] = v; }
			Modify(1, n, l, r, tr);
		}
	}
	return 0;
}

Matrix Matrix::operator+(const Matrix & m) const {
	assert(r == m.r && c == m.c);
	Matrix res(r, c);
	for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) res[i][j] = Add(A[i][j], m.A[i][j]);
	return res;
}

Matrix Matrix::operator*(const Matrix & m) const {
//	if (c != m.r) printf(" %dx%d * %dx%d\n", r, c, m.r, m.c);
	assert(c == m.r);
	Matrix res(r, m.c);
	for (int i = 0; i < r; ++i) for (int j = 0; j < m.c; ++j) {
		for (int k = res[i][j] = 0; k < c; ++k) Upa(res[i][j], Mul(A[i][k], m.A[k][j]));
	} return res;
}

namespace smt {
	Node::Node(std::initializer_list<int> arg) {
		val.set(0, 1), tag = idmat;
		for (auto x : arg) val[val.r++][0] = x;
		val[val.r++][0] = 1;
	}
#define LS Id(l, mid)
#define RS Id(mid + 1, r)
	void Build(int l, int r) {
		if (l == r) return;
		int rt = Id(l, r), mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r); T[rt].val = T[LS].val + T[RS].val, T[rt].tag = idmat;
	}
	void PushDw(int l, int mid, int r) {
		int rt = Id(l, r);
		T[LS].val = T[rt].tag * T[LS].val, T[LS].tag *= T[rt].tag;
		T[RS].val = T[rt].tag * T[RS].val, T[RS].tag *= T[rt].tag;
		T[rt].tag = idmat;
	}
	void Modify(int l, int r, int ql, int qr, const Matrix & m) {
		int rt = Id(l, r), mid = l + r >> 1;
		if (ql <= l && r <= qr) {
			T[rt].val = m * T[rt].val, T[rt].tag *= m; return;
		} PushDw(l, mid, r);
		if (ql <= mid) Modify(l, mid, ql, qr, m);
		if (qr > mid) Modify(mid + 1, r, ql, qr, m);
		T[rt].val = T[LS].val + T[RS].val;
	}
	Matrix Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[Id(l, r)].val;
		int mid = l + r >> 1;
		PushDw(l, mid, r);
		if (qr <= mid) return Query(l, mid, ql, qr);
		if (ql > mid) return Query(mid + 1, r, ql, qr);
		return Query(l, mid, ql, qr) + Query(mid + 1, r, ql, qr);
	}
}
