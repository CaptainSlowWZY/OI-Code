#include <cstdio>

const int kMaxn = 1e5 + 10;

int n, m, tots;

struct Bit {
	int ar[kMaxn];
	void add(int p);
	int query(int p);
} ord, rev;

int main() {
	scanf("%d%d", &n, &m);
	for (int t, l, r; m--; ) {
		scanf("%d%d%d", &t, &l, &r);
		if (t == 1) {
			ord.add(r), rev.add(n - l + 1), ++tots;
		} else {
			printf("%d\n", tots -
					ord.query(l - 1) - rev.query(n - r));
		}
	} return 0;
}

void Bit::add(int p) {
	for (; p <= n; p += p & -p) ++ar[p];
}

int Bit::query(int p) {
	int res = 0;
	for (; p; p &= p - 1) res += ar[p];
	return res;
}
