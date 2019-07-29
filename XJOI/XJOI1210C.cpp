#pragma GCC optimize(2)
#include <algorithm>
#include <cstdio>

const int kMaxn = 1e6 + 10, kInf = 0x3f3f3f3f;

struct Node {
	int min, tag;

	Node() {}
	Node(int mn, int tg = kInf) :
		min(mn), tag(tg) {}
	void value(int val) {
		min = std::min(min, val);
		tag = std::min(tag, val);
	}
	Node operator+(const Node & n) const {
		return Node(std::min(min, n.min));
	}
};
struct SegTree {
	Node T[kMaxn << 1];

	int id(int l, int r) const { return l + r | l != r; }
	const Node & build(int l, int r, int buf[]);
	void pushdown(int l, int m, int r);
	int query(int l, int r, int ql, int qr);
	void update(int l, int r, int ql, int qr, int val);
} seg[3];

int n, m, q;
int K[3], H[kMaxn];

int main() {
	for (int i = 0; i < 3; i++) scanf("%d", K + i);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) H[i] = kInf;
	for (int i = 0; i < 3; i++) seg[i].build(1, n, H);
	for (int i = 1; i <= n; i++) {
		scanf("%d", H + i);
	}
	scanf("%d", &m);
	for (int l, r, p, b; m--; ) {
		scanf("%d%d%d%d", &l, &r, &p, &b);
		seg[--p].update(1, n, l, r, b);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			H[i] = std::min(H[i], (int)
			std::max(0ll, 1ll * K[j] * i + seg[j].query(1, n, i, i)));
		}
	}
	seg[0].build(1, n, H);
	scanf("%d", &q);
	for (int l, r; q--; ) {
		scanf("%d%d", &l, &r);
		printf("%d\n", seg[0].query(1, n, l, r));
	}
	return 0;
}

const Node & SegTree::build(int l, int r, int buf[]) {
	int cur = id(l, r);
	if (l == r) {
		T[cur].min = buf[l], T[cur].tag = kInf;
		return T[cur];
	}
	int mid = l + r >> 1;
	return T[cur] = build(l, mid, buf) + build(mid + 1, r, buf);
}

void SegTree::pushdown(int l, int m, int r) {
	int cur = id(l, r);
	if (T[cur].tag != kInf) {
		T[id(l, m)].value(T[cur].tag);
		T[id(m + 1, r)].value(T[cur].tag);
		T[cur].tag = kInf;
	}
}

void SegTree::update(int l, int r, int ql, int qr, int val) {
	int cur = id(l, r);
	if (ql <= l && r <= qr) {
		T[cur].value(val);
		return;
	}
	int mid = l + r >> 1;
	pushdown(l, mid, r);
	if (ql <= mid) update(l, mid, ql, qr, val);
	if (qr > mid) update(mid + 1, r, ql, qr, val);
	T[cur] = T[id(l, mid)] + T[id(mid + 1, r)];
}

int SegTree::query(int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return T[id(l, r)].min;
	int mid = l + r >> 1, res = kInf;
	pushdown(l, mid, r);
	if (ql <= mid) res = std::min(res, query(l, mid, ql, qr));
	if (mid < qr) res = std::min(res, query(mid + 1, r, ql, qr));
	return res;
}
