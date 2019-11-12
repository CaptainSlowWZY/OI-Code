#include <cstdio>
#include <cstring>

const int kMaxn = 5e4 + 5, kMod = 1e9 + 7;

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
	int tag, dp[5][3][3];
	void set(int k, int l = 1);
	Node operator+(const Node & n) const;
};

namespace smt {
	void Build(int, int);
	void Modify(int, int, int, int, int);
	Node Query(int, int, int, int);
}

int n, q, H[kMaxn], C[6][6];

int main() {
#ifndef LOCAL
	freopen("sendpoints.in", "r", stdin);
	freopen("sendpoints.out", "w", stdout);
#endif
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) { scanf("%d", H + i); --H[i]; }
	smt::Build(1, n);
	for (int i = C[0][0] = 1; i <= 5; ++i) for (int j = C[i][0] = 1; j <= i; ++j) C[i][j] = Add(C[i - 1][j], C[i - 1][j - 1]); 
	for (int ans, o, l, r, k; q--; ) {
		scanf("%d%d%d%d", &o, &l, &r, &k);
		if (o == 1) smt::Modify(1, n, l, r, --k);
		else {
			Node res = smt::Query(1, n, l, r);
			for (int i = ans = 0, sum; i < k; ++i) {
				for (int j = sum = 0; j < 3; ++j) for (int t = j; t < 3; ++t) Upa(sum, res.dp[k - i - 1][j][t]);
				Upm(sum, C[k][i]);
				if (i & 1) Ups(ans, sum); else Upa(ans, sum);
			} printf("%d\n", ans);
		}
	}
#ifndef LOCAL
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

void Node::set(int k, int l) {
	memset(dp, 0, sizeof dp); tag = k;
	for (int i = 0; i < 5; ++i) dp[i][k][k] = Sub(FPow(i + 2, l), 1);
}

Node Node::operator+(const Node & n) const {
	Node res; memset(res.dp, 0, sizeof res.dp);
	for (int t = 0; t < 5; ++t) for (int i0 = 0; i0 < 3; ++i0) for (int i1 = i0; i1 < 3; ++i1) {
		for (int i2 = i1; i2 < 3; ++i2) for (int i3 = i2; i3 < 3; ++i3) Upa(res.dp[t][i0][i3], Mul(dp[t][i0][i1], n.dp[t][i2][i3]));
		Upa(res.dp[t][i0][i1], Add(dp[t][i0][i1], n.dp[t][i0][i1]));
	} res.tag = -1; return res;
}

namespace smt {
	Node T[kMaxn << 1];

	inline int Id(int l, int r) { return l + r | l != r; }
#define LSON Id(l, mid)
#define RSON Id(mid + 1, r)
	void Build(int l, int r) {
		int cur = Id(l, r);
		if (l == r) return T[cur].set(H[l]);
		int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r); T[cur] = T[LSON] + T[RSON];
	}
#define PUSH_DOWN if (~T[cur].tag) { T[LSON].set(T[cur].tag, mid - l + 1); T[RSON].set(T[cur].tag, r - mid); T[cur].tag = -1; }
	void Modify(int l, int r, int ql, int qr, int k) {
		int cur = Id(l, r);
		if (ql <= l && r <= qr) return T[cur].set(k, r - l + 1);
		int mid = l + r >> 1;
		PUSH_DOWN;
		if (ql <= mid) Modify(l, mid, ql, qr, k);
		if (qr > mid) Modify(mid + 1, r, ql, qr, k);
		T[cur] = T[LSON] + T[RSON];
	}
	Node Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[Id(l, r)];
		int mid = l + r >> 1, cur = Id(l, r); PUSH_DOWN;
		if (qr <= mid) return Query(l, mid, ql, qr);
		if (ql > mid) return Query(mid + 1, r, ql, qr);
		return Query(l, mid, ql, qr) + Query(mid + 1, r, ql, qr);
	}
}
