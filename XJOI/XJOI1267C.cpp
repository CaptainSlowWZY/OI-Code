#include <algorithm>
#include <cassert>
#include <cstdio>

const int kMaxn = 2e5 + 5;

int n, q;
int sum[kMaxn];
char S[kMaxn];

namespace smt {
	struct Node {
		int mn, mx, gap, tag;
		Node(int v = 0) : mn(v), mx(v) {
			gap = tag = 0;
		}
		Node(int m1, int m2, int g, int t) :
			mn(m1), mx(m2), gap(g), tag(t) {}
		void operator+=(int d) {
			mn += d, mx += d, tag += d;
		}
		Node operator+(const Node & n) const {
			return {std::min(mn, n.mn), std::max(mx, n.mx),
				std::max(std::max(gap, n.gap), n.mx - mn), 0};
		}
	} T[kMaxn << 1];

	void Build(int l, int r);
	void Modify(int l, int r, int ql, int qr, int d);
	Node Query(int l, int r, int ql, int qr);
}
namespace solver1 {
	int flag[1005];

	void Solve() {
		for (int o, x, y, ans; q--; ) {
			scanf("%d%d", &o, &x);
			if (o == 1) {
				if (S[x - 1] == '(') {
					y = -2; S[x - 1] = ')';
				} else {
					y = 2; S[x - 1] = '(';
				}
				for (; x <= n; ++x) sum[x] += y;
			} else {
				scanf("%d", &y); ans = 0;
				if (o == 2) {
					for (int i = x, min = 0; i <= y; ++i) {
						if (sum[i] - sum[x - 1] < min) {
							++ans; min = sum[i] - sum[x - 1];
						}
					} printf("%d\n", ans);
				} else {
					for (int i = x, min = 0; i <= y; ++i) {
						if (sum[i] - sum[x - 1] < min) {
							//  printf(" 11del = %d, i = %d\n", sum[y] - sum[i - 1], i);
							flag[i] = 1; min = sum[i] - sum[x - 1];
						}
					}
					for (int i = y, min = 0, d = 0; i >= x; --i) {
						d += flag[i];
						if (sum[y] - sum[i - 1] + d < min) {
							//  printf(" 22del = %d, i = %d\n", sum[y] - sum[i - 1] + d, i);
							flag[i] = 1; min = sum[y] - sum[i - 1] + d;
						}
					}
					for (int i = x; i <= y; ++i) {
						if (!flag[i]) continue;
						++ans; flag[i] = 0;
					} printf("%d\n", ans);
				}
			}
		}
	}
}

int main() {
	scanf("%d%s%d", &n, S, &q);
	for (int i = 0; i < n; ++i)
		sum[i + 1] = sum[i] + (S[i] == '(' ? 1 : -1);
	if (n <= 1000 && q <= 2000) {
		solver1::Solve(); return 0;
	}
	smt::Build(1, n);
	for (int o, x, y; q--; ) {
		scanf("%d%d", &o, &x);
		using namespace smt;
		if (o == 1) {
			if (S[x - 1] == '(') {
				Modify(1, n, x, n, -2);
				S[x - 1] = ')';
			} else {
				Modify(1, n, x, n, 2);
				S[x - 1] = '(';
			}
		} else {
			scanf("%d", &y);
			if (o == 2)
				printf("%d\n", std::max(0,
							Query(1, n, x - 1, x - 1).mn -
							Query(1, n, x, y).mn));
			else
				printf("%d\n", Query(1, n, x - 1, y).gap -
						Query(1, n, y, y).mn +
						Query(1, n, x - 1, x - 1).mn);
		}
	}
	return 0;
}

namespace smt {
	inline int Id(int l, int r) {
		return l + r | l != r;
	}
#define LSON Id(l, mid)
#define RSON Id(mid + 1, r)
	void Build(int l, int r) {
		int cur = Id(l, r);
		if (l == r)
			return (void)(T[cur] = Node(sum[l]));
		int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r);
		T[cur] = T[LSON] + T[RSON];
	}
	inline void PushDown(int l, int mid, int r) {
		int cur = Id(l, r);
		if (!T[cur].tag) return;
		T[LSON] += T[cur].tag; T[RSON] += T[cur].tag;
		T[cur].tag = 0;
	}
	void Modify(int l, int r, int ql, int qr, int d) {
		int cur = Id(l, r);
		if (ql <= l && r <= qr)
			return (void)(T[cur] += d);
		int mid = l + r >> 1;
		PushDown(l, mid, r);
		if (ql <= mid) Modify(l, mid, ql, qr, d);
		if (qr > mid) Modify(mid + 1, r, ql, qr, d);
		T[cur] = T[LSON] + T[RSON];
	}
	Node Query(int l, int r, int ql, int qr) {
		if (ql < 1) {
			if (!qr) return Node();
			return Query(l, r, 1, qr);
		}
		if (ql <= l && r <= qr) return T[Id(l, r)];
		int mid = l + r >> 1;
		PushDown(l, mid, r);
		if (ql > mid)
			return Query(mid + 1, r, ql, qr);
		if (qr <= mid)
			return Query(l, mid, ql, qr);
		return Query(l, mid, ql, qr) + Query(mid + 1, r, ql, qr);
	}
}
