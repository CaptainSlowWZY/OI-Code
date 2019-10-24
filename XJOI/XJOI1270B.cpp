#pragma GCC optimize(2)
#include <algorithm>
#include <cstdio>

typedef long long LL;

const int kMaxn = 5e5 + 5;

int n, q, o;

namespace smt {
	struct Node {
		LL sl, sr, s1, s2, s3;
		void operator+=(const Node & n) {
			sl += n.sl, sr += n.sr, s1 += n.s1;
			s2 += n.s2, s3 += n.s3;
		}
		void debug() const {
			printf("  (sl %lld, sr %lld, s1 %lld, s2 %lld, s3 %lld\n",
					sl, sr, s1, s2 ,s3);
		}
	} T[kMaxn << 1];
	Node Build(int l, int r);
	LL Query(int l, int r, int ql, int qr);
}

int main() {
	scanf("%d%d%d", &n, &q, &o);
	LL la = 0;
	smt::Build(1, n);
	for (LL l, r; q--; ) {
		scanf("%lld%lld", &l, &r);
		l = (l ^ (la * o)) % n + 1, r = (r ^ (la * o)) % n + 1;
		if (l > r) std::swap(l, r);
//		printf(" query [%lld, %lld]\n", l, r);
		printf("%lld\n", la = smt::Query(1, n, l, r));
	} return 0;
}

inline LL SumEd(LL l, LL r) {
	return (l + r) * (r - l + 1) >> 1;
}
inline LL Sum2(LL x) { return x * (x + 1) * (2 * x + 1) / 6; }
inline LL Sum2(LL l, LL r) { return Sum2(r) - Sum2(l - 1); }

namespace smt {
	inline int Id(int l, int r) { return l + r | l != r; }
	Node Build(int l, int r) {
		int u = Id(l, r);
		T[u].sl = l, T[u].sr = r;
		T[u].s1 = LL(r - l) * r;
		T[u].s2 = LL(l + r - 1) * (r - l) >> 1;
		T[u].s3 = l * LL(1 - r);
		if (l == r) return T[u];
		int mid = l + r >> 1;
		T[u] += Build(l, mid);
		T[u] += Build(mid + 1, r);
		return T[u];
	}
	LL Query(int l, int r, int ql, int qr) {
		int u = Id(l, r);
		LL res = 0;
		if (ql <= l && r <= qr) {
			res = (T[u].sr - T[u].sl) * (qr - ql + 2);
			res += T[u].s2 - T[u].s1;
			LL tmp = 0;
			tmp += SumEd(l, r) * (ql + qr) + qr + 1;
			tmp -= Sum2(l, r) + LL(ql) * qr + ql;
			res += tmp * 2, tmp = 0;
//			printf("  gong22 %lld\n", res);
			tmp += T[u].sl * qr + LL(ql - 1) * T[u].sr + qr + T[u].s3 + 1;
			tmp -= LL(ql) * qr + ql;
			res -= tmp;
//			printf("   include [%d, %d] res %lld\n", l, r, res);
//			T[u].debug();
			return res;
		} int mid = l + r >> 1;
		int l3 = std::max(l, ql), r3 = std::min(r - 1, qr),
			l4 = std::max(l + 1, ql), r4 = std::min(r, qr);
		if (l3 <= r3)
			res += SumEd(l3, r3) + LL(r3 - l3 + 1) * (1 - ql);
		res += LL(r4 - l4 + 1) * std::max(qr - r + 1, 0);
		if (ql <= mid) res += Query(l, mid, ql, qr);
		if (qr > mid) res += Query(mid + 1, r, ql, qr);
		return res;
	}
}
