// POJ 1151
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
typedef double real;
const int MAXN = 105;

struct Edge {
	real lx, rx, y;
	int flag;
	Edge() {}
	Edge(real lx_, real rx_, real y_, int f_) : lx(lx_), rx(rx_), y(y_), flag(f_) {}
	bool operator<(const Edge & e) const {
		return y < e.y;
	}
} E[MAXN << 1];
real X[MAXN << 1];
int N, totx, tote; 

// #define _DEBUG_MD_

namespace Segment_Tree {
	struct Node {
		real len;
		int flag;
	} T[MAXN << 2];
	int limt, QL, QR, delta;

	void _modfy(int rt, int l, int r);
	inline void init(int lim_) {
		limt = lim_;
		memset(T, 0, sizeof T);
	}
	inline void modify(int _ql, int _qr, int tg) {

#ifdef _DEBUG_MD_
		printf("modify: [%d, %d], delta=%d\n", _ql, _qr, tg);
#endif

		QL = _ql, QR = _qr, delta = tg;
		_modfy(1, 1, limt);
	}
	inline real cvr_len() {
		return T[1].len;
	}
}
void solve();

int main() {
	for (int k = 0; scanf("%d", &N) == 1 && N; ) {
		printf("Test case #%d\n", ++k);
		solve();
	}
	return 0;
}

void solve() {
	double x1, y1, x2, y2;
	totx = tote = 0;
	for (int i = 0; i < N; i++) {
		scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
		E[tote++] = Edge(x1, x2, y1, 1);
		E[tote++] = Edge(x1, x2, y2, -1);
		X[++totx] = x1, X[++totx] = x2;
	}
	std::sort(E, E + tote);
	std::sort(X + 1, X + 1 + tote);
	totx = std::unique(X + 1, X + 1 + tote) - X - 1;

#ifdef _DEBUG_MD_
	printf("totx=%d\n", totx);
	for (int i = 1; i <= totx; i++) printf("%4.2f\n", X[i]); putchar('\n');
#endif

	std::map<real, int> Mp;
	for (int i = 1; i <= totx; i++) Mp[X[i]] = i;
	Segment_Tree::init(totx);
	Segment_Tree::modify(Mp[E[0].lx], Mp[E[0].rx], E[0].flag);
	real ans = 0;
	for (int i = 1; i < tote; i++) {

#ifdef _DEBUG_MD_
		printf("last line's y cordn: %.2f, currend line's y codrn: %.2f\n", E[i - 1].y, E[i].y);
		printf("horinal length: %4.2f\n", Segment_Tree::cvr_len());
#endif

		ans += Segment_Tree::cvr_len() * (E[i].y - E[i - 1].y);	
		Segment_Tree::modify(Mp[E[i].lx], Mp[E[i].rx], E[i].flag);
	}
	printf("Total explored area: %.2f\n\n", ans);
}

namespace Segment_Tree {

#define lson rt << 1
#define rson rt << 1 | 1

	void push_up(int rt, int l, int r) {

#ifdef _DEBUG_MD_
		printf("push up: [%d, %d], flag=%d\n", l, r, T[rt].flag);
#endif

		if (T[rt].flag) { T[rt].len = X[r] - X[l]; return; }
		if (r - l <= 1) { T[rt].len = 0; return; }
		T[rt].len = T[lson].len + T[rson].len;

#ifdef _DEBUG_MD_
		printf("--len=%.2f\n", T[rt].len);
#endif

	}	

	void _modfy(int rt, int l, int r) {
		if (r <= QL || l >= QR) return;

#ifdef _DEBUG_MD_
		printf("__modify: [%d, %d]\n", l, r);
#endif

		if (QL <= l && r <= QR) {
			T[rt].flag += delta;
			push_up(rt, l, r);
			return;
		}
		int mid = l + r >> 1;
		_modfy(lson, l, mid);
		_modfy(rson, mid, r);
		push_up(rt, l, r);

#ifdef _DEBUG_MD_
		printf("__modify: length of [%d, %d]: %.2f\n", l, r, T[rt].len);
#endif

	}
}

// AC!!!
