#include <cstdio>
#include <cctype>
#include <algorithm>

const int kMaxn = 5e5 + 10, MOD = 1e9 + 7;

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar();
			register bool f = false; x = 0;
			for (; !isdigit(ch); f |= (ch == '-'), ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
}
namespace smt {
	void Modify(int rt, int l, int r, int pos, int del);
	int Query(int rt, int l, int r, int ql, int qr);
}

struct Line {
	int k, b, l, r, id;
	bool operator<(const Line & l) const {
		return k == l.k ? b < l.b : k < l.k;
	}
} L[kMaxn];

int n;

inline bool Cmpb(const Line & l1, const Line & l2) {
	return l1.b < l2.b;
}
inline bool Cmpd(const Line & l1, const Line & l2) {
	return l1.r == l2.r ? l1.l < l2.l : l1.r < l2.r;
}

int main() {
	using fast_io::Read;

	Read(n);
	for (int i = 0; i < n; i++) {
		Read(L[i].b), Read(L[i].k);
	}

	std::sort(L, L + n);
	for (int i = 0; i < n; i++) L[i].id = i + 1;
	std::sort(L, L + n, Cmpb);
	L[0].r = L[0].id;
	for (int i = 1; i < n; i++) {
		L[i].r = std::max(L[i].id, L[i - 1].r);
	}
	L[n - 1].l = L[n - 1].id;
	for (int i = n - 2; i >= 0; i--) {
		L[i].l = std::min(L[i].id, L[i + 1].l);
	}

	std::sort(L, L + n, Cmpd);
	smt::Modify(1, 0, n, 0, 1);
	for (int i = 0; i < n; i++) {
		smt::Modify(1, 0, n, L[i].r, 
					smt::Query(1, 0, n, L[i].l - 1, L[i].r));
	}

	printf("%d\n", smt::Query(1, 0, n, n, n));
	return 0;
}

#define lson (rt << 1)
#define rson (rt << 1 | 1)

namespace smt {
	int T[kMaxn << 2];

	void Modify(int rt, int l, int r, int pos, int del) {
		if (l == r) {
			(T[rt] += del) %= MOD;
			return;
		}
		int mid = l + r >> 1;
		if (pos <= mid) Modify(lson, l, mid, pos, del);
		else Modify(rson, mid + 1, r, pos, del);
		T[rt] = (T[lson] + T[rson]) % MOD;
	}
	int Query(int rt, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return T[rt];
		int mid = l + r >> 1, ret = 0;
		if (ql <= mid) ret = Query(lson, l, mid, ql, qr);
		if (qr > mid) (ret += Query(rson, mid + 1, r, ql, qr)) %= MOD;
		return ret;
	}
}
