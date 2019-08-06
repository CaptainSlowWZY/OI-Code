#include <algorithm>
#include <cstdio>

const int kMaxn = 5e4 + 10, kMaxx = 2e4 + 10, kInf = 0x3f3f3f3f;

struct Edge {
	int y, lx, rx, t;
	bool operator<(const Edge & e) const { return y < e.y; }
} E[kMaxn << 1];

namespace smt {
	struct Node {
		int fc, cov, cnts, cl, cr;	// fc - full cover ?
		Node operator+(const Node & n) const {
			return {0, cov + n.cov,
				cnts + n.cnts - (cr & n.cl), cl, n.cr};
		}
		void set(bool md, int len = 0) {
			cov = len, cnts = cl = cr = md;
		}
	} T[kMaxx << 2];
	int bd;

#define ls(_) (_ << 1)
#define rs(_) (_ << 1 | 1)

	inline int TotSeg() { return T[1].cnts; }
	inline void SetBound(int x) { bd = x; }
	void Modify(int u, int l, int r, int ql, int qr, int d);
	inline int Modify(const Edge & e) {
		Modify(1, 1, bd, e.lx, e.rx, e.t);
		return T[1].cov;
	}
}

int n;

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}

int main() {
	scanf("%d", &n);
	int minx = kInf, maxx = -kInf;
	for (int i = 0, x1, y1, x2, y2; i < n; i++) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		E[i << 1] = {y1, x1, x2, 1};
		E[i << 1 | 1] = {y2, x1, x2, -1};
		UMin(minx, x1), UMax(maxx, x2);
	} std::sort(E, E + (n <<= 1));
	for (int i = 0, del = -minx + 1; i < n; i++) {
		E[i].lx += del, E[i].rx += del;
	} smt::SetBound(maxx - minx + 1);
	int lastc = smt::Modify(E[0]);
	long long ans = lastc;
	for (int cov, i = 1; i < n; i++) {
		ans += 2ll * smt::TotSeg() * (E[i].y - E[i - 1].y);
		ans += abs((cov = smt::Modify(E[i])) - lastc);
		lastc = cov;
	} printf("%lld\n", ans);
	return 0;
}

namespace smt {
	void Modify(int u, int l, int r, int ql, int qr, int d) {
		if (qr <= l || r <= ql) return;
		int mid = l + r >> 1;
		if (ql <= l && r <= qr) {
			if (!(T[u].fc += d)) {
				if (r - l > 1) T[u] = T[ls(u)] + T[rs(u)];
				else T[u].set(0);
			} else T[u].set(1, r - l);
			return;
		}
		Modify(ls(u), l, mid, ql, qr, d);
		Modify(rs(u), mid, r, ql, qr, d);
		if (!T[u].fc) T[u] = T[ls(u)] + T[rs(u)];
	}
}
