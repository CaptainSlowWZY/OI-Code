// ZJOI 2013
#include <cstdio>
#include <cctype>

typedef long long LL;

const int kMaxn = 5e4 + 10;

struct Oper {
	int tp, l, r, id;
	LL val;
} O[kMaxn];

int n, m, totq, ans[kMaxn];

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
void Solve(int ql, int qr, int vl, int vr);

int main() {
	using fast_io::Read;

	Read(n), Read(m);
	int totq = 0;
	for (int i = 0; i < m; i++) {
		Read(O[i].tp), Read(O[i].l), Read(O[i].r), Read(O[i].val);
		if (--O[i].tp) {
			O[i].id = totq++;
		}
	}

	Solve(0, m, -kMaxn, kMaxn);

	for (int i = 0; i < totq; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

int VER = 0;

namespace bit {
	struct Bit {
		LL T[kMaxn];
		int ver[kMaxn];
		
		void add(int p, LL del) {
			for (; p <= n; p += p & -p) {
				if (ver[p] == VER) {
					T[p] += del;
				}
				else {
					T[p] = del;
					ver[p] = VER;
				}
			}
		}
		LL sum(int p) {
			LL ret = 0;
			for (; p; p &= p - 1) {
				if (ver[p] == VER) {
					ret += T[p];
				}
			}
			return ret;
		}
	} dn, di;

	inline void Add(int l, int r) {
		dn.add(l, 1), dn.add(r + 1, -1);
		di.add(l, l), di.add(r + 1, -r - 1);
	}
	inline LL Sum(int l, int r) {
		return LL(r + 1) * dn.sum(r) - di.sum(r) - 1ll * l * dn.sum(l - 1) + di.sum(l - 1);
	}
}

void Solve(int ql, int qr, int vl, int vr) {
//	fprintf(stderr, " [%d, %d), val : [%d, %d]\n", ql, qr, vl, vr);
	if (ql >= qr) return;
	if (vl == vr) {
		for (int i = ql; i < qr; i++) {
			if (O[i].tp) {
				ans[O[i].id] = vl;
			}
		}
		return;
	}
	int mid = vl + vr >> 1, b1 = 0, b2 = 0;
	static Oper fr[kMaxn], sc[kMaxn];
	++VER;
	for (int i = ql; i < qr; i++) {
		using namespace bit;
		if (O[i].tp) {
			LL cnt = Sum(O[i].l, O[i].r);
			if (cnt < O[i].val) {
				O[i].val -= cnt;
				fr[b1++] = O[i];
			}
			else {
				sc[b2++] = O[i];
			}
		}
		else {
			if (O[i].val <= mid) {
				fr[b1++] = O[i];
			}
			else {
				Add(O[i].l, O[i].r);
				sc[b2++] = O[i];
			}
		}
	}

	for (int i = 0; i < b1; i++) {
		O[ql + i] = fr[i];
	}
	for (int i = 0; i < b2; i++) {
		O[ql + b1 + i] = sc[i];
	}

	Solve(ql, ql + b1, vl, mid);
	Solve(ql + b1, qr, mid + 1, vr);
}
