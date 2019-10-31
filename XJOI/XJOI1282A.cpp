#include <algorithm>
#include <cstdio>
typedef long long LL;
const int kMaxn = 3e5 + 5;
int n, m, sa[kMaxn], id[kMaxn], G[kMaxn];
struct Smt {
	LL T[kMaxn << 1], tag[kMaxn << 1], (*meg)(LL, LL);
	int id(int l, int r) { return l + r | l != r; }
	void set_mode(LL (*ptr)(LL, LL)) { meg = ptr; }
	void modify(int l, int r, int ql, int qr, int d);
	LL query(int l, int r, int ql, int qr);
} C, D;
inline LL Max(LL a, LL b) { return std::max(a, b); }
inline LL Min(LL a, LL b) { return std::min(a, b); }
inline bool CmpG(int a, int b) { return G[a] > G[b]; }
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", sa + i); sa[i] += sa[i - 1];
	} C.set_mode(Max); D.set_mode(Min);
	for (int i = 1, l, r; i <= m; ++i) {
		scanf("%d%d%d", &l, &r, G + i);
		id[i] = i, C.modify(1, m, i, i, -sa[r]);
		D.modify(1, m, i, i, -sa[l - 1]);
	} std::sort(id + 1, id + m + 1, CmpG);
	LL ans = 0;
	for (int i = 1; i <= m; ++i) {
		if (C.query(1, m, id[i], m) >= D.query(1, m, 1, id[i]))
			continue;
		ans += G[id[i]];
		C.modify(1, m, id[i], m, 1);
		if (id[i] < m) D.modify(1, m, id[i] + 1, m, 1);
	} printf("%lld\n", ans);
	return 0;
}
#define LSON id(l, mid)
#define RSON id(mid + 1, r)
#define PUSH_DOWN if (tag[u]) { \
	T[LSON] += tag[u], tag[LSON] += tag[u]; \
	T[RSON] += tag[u], tag[RSON] += tag[u]; tag[u] = 0; }
void Smt::modify(int l, int r, int ql, int qr, int d) {
	int u = id(l, r), mid = l + r >> 1;
	if (ql <= l && r <= qr) { T[u] += d, tag[u] += d; return; }
	if (ql <= mid) modify(l, mid, ql, qr, d);
	if (qr > mid) modify(mid + 1, r, ql, qr, d);
	PUSH_DOWN T[u] = meg(T[LSON], T[RSON]);
}
LL Smt::query(int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return T[id(l, r)];
	int mid = l + r >> 1, u = id(l, r); PUSH_DOWN
	if (qr <= mid) return query(l, mid, ql, qr);
	if (ql > mid) return query(mid + 1, r, ql, qr);
	return meg(query(l, mid, ql, qr), query(mid + 1, r, ql, qr));
}
