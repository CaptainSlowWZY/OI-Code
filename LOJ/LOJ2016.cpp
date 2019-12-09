#include <algorithm>
#include <cstdio>

const int kMaxn = 2e5 + 5, kLen = 1 << 18, kLg = 17;

namespace smt {
	const int kMaxv = 6e6;
	int size, rt[kMaxn], val[kMaxv], ls[kMaxv], rs[kMaxv];
	int Build(int l, int r);
	int Mdf(int pr, int L, int R, int v);
	inline void Insert(int p, int v) { rt[p] = Mdf(rt[p - 1], 0, kLen, v); }
	int Flavor(int fir, int lst, int x, int d);
}

int n, m;

int main() {
	scanf("%d%d", &n, &m);
	smt::rt[0] = smt::Build(0, kLen);
	for (int i = 1, ai; i <= n; ++i) { scanf("%d", &ai); smt::Insert(i, ai); }
	for (int b, x, l, r; m--; ) {
		scanf("%d%d%d%d", &b, &x, &l, &r);
		printf("%d\n", smt::Flavor(l, r, b, x));
	} return 0;
}

namespace smt {
	int Build(int l, int r) {
		int rt = ++size;
		if (r - l == 1) return rt;
		int mid = l + r >> 1;
		ls[rt] = Build(l, mid); rs[rt] = Build(mid, r); return rt;
	}
	int Mdf(int pr, int L, int R, int v) {
		int rt = ++size;
		val[rt] = val[pr] + 1, ls[rt] = ls[pr], rs[rt] = rs[pr];
		if (R - L == 1) return rt;
		int mid = L + R >> 1;
		if (v < mid) ls[rt] = Mdf(ls[pr], L, mid, v);
		if (v >= mid) rs[rt] = Mdf(rs[pr], mid, R, v);
		return rt;
	}
	int Cnt(int rl, int rr, int L, int R, int ql, int qr) {
		if (qr <= 0) return 0;
		ql = std::max(ql, 0), qr = std::max(qr, 1);
		if (ql <= L && R <= qr) return val[rr] - val[rl];
		int mid = L + R >> 1, res = 0;
		if (ql < mid) res += Cnt(ls[rl], ls[rr], L, mid, ql, qr);
		if (qr > mid) res += Cnt(rs[rl], rs[rr], mid, R, ql, qr);
		return res;
	}
	int Flavor(int fir, int lst, int x, int d) {
		fir = rt[fir - 1], lst = rt[lst];
		int res = 0;
		for (int c, i = kLg, l = 0, gap = kLen >> 1; i >= 0; --i, gap >>= 1) {
			c = x >> i & 1 ^ 1;
//			printf(" bit %d, c%d, gap %d, l %d\n", i, c, gap, l);
//			printf("   Q[%d, %d)\n",l + c * gap - d, l + c * gap + gap - d);
			if (smt::Cnt(fir, lst, 0, kLen, l + c * gap - d, l + c * gap + gap - d)) {
//				puts("  Found xor=1");
				res |= gap, l += c * gap;
			} else l += (c ^ 1) * gap;
		} return res;
	}
}
