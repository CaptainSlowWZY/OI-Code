// HDU 1828
// IOI 1998
#include <cstdio>
#include <cstring>
#include <algorithm>
const int MAXN = 5005;
const int MAXX = 20005;
const int INF = 0x3f3f3f3f;
struct Edge {
	int lx, rx, y, f;
	Edge() {}
	Edge(int lx_, int rx_, int y_, int f_) : lx(lx_), rx(rx_), y(y_), f(f_) {}
	bool operator<(const Edge & e) const {
		return y < e.y;
	}
} E[MAXN << 1];

int N, tote;

namespace Segment_Tree {
	struct Node {
		int len, crfg, crseg, lft_cvr, rgh_cvr;
		void set(int md) {
		// mode of node setting: 0 - no seg cover, 1 - all covered
			if (md) { lft_cvr = rgh_cvr = crseg = 1; return; }
			lft_cvr = rgh_cvr = crseg = len = 0;
		}
		Node operator+(const Node & n) const {
		// This addition does NOT satisfy the exchange law.
		// Left son must be the first-operation element.
			Node res;
			res.len = this->len + n.len, res.crfg = 0;
			res.lft_cvr = this->lft_cvr, res.rgh_cvr = n.rgh_cvr;
			res.crseg = this->crseg + n.crseg - (this->rgh_cvr & n.lft_cvr);
			return res;
		}
	} T[MAXX << 2];
	int limt, QL, QR, delta;

	void modify(int rt, int l, int r);
	inline void init(int l_) {
		limt = l_;
		memset(T, sizeof T, 0);
	}
	inline int add_edge(int ql, int qr, int flg) {
		QL = ql, QR = qr, delta = flg;
		modify(1, 1, limt);
		return T[1].len;
	}
	inline int tot_seg() {
		return T[1].crseg;
	}
}
void solve();

int main() {
	while (~scanf("%d", &N)) solve();
	return 0;
}

void solve() {
	int minx = INF, maxx = -INF;
	tote = 0;
	for (int i = 0, x1, x2, y1, y2; i < N; i++) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		E[tote++] = Edge(x1, x2, y1, 1);
		E[tote++] = Edge(x1, x2, y2, -1);
		minx = std::min(minx, x1);
		maxx = std::max(maxx, x2);
	}
	std::sort(E, E + tote);
	Segment_Tree::init(maxx - minx + 1);
	int dltx = -minx + 1, lstcvr = Segment_Tree::add_edge(E[0].lx + dltx, E[0].rx + dltx, E[0].f), ans = lstcvr, tmp;
	for (int i = 1; i < tote; i++) {
		ans += Segment_Tree::tot_seg() * 2 * (E[i].y - E[i - 1].y);
		ans += std::abs((tmp = Segment_Tree::add_edge(E[i].lx + dltx, E[i].rx + dltx, E[i].f)) - lstcvr);
		lstcvr = tmp;
	}
	printf("%d\n", ans);
}

namespace Segment_Tree {
#define lson rt << 1
#define rson rt << 1 | 1
	void pushup(int rt, int l, int r) {
		if (T[rt].crfg) {
			T[rt].len = r - l;
			T[rt].set(1);
			return;
		}
		if (r - l <= 1) { T[rt].set(0); return; }
		T[rt] = T[lson] + T[rson];
	}
	void modify(int rt, int l, int r) {
		if (QR <= l || QL >= r) return;
		if (QL <= l && r <= QR) {
			T[rt].crfg += delta;
			pushup(rt, l, r);
			return;
		}
		int mid = l + r >> 1;
		modify(lson, l, mid);
		modify(rson, mid, r);
		pushup(rt, l, r);
	}
}

// AC!!!