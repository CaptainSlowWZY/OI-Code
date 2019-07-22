#include <algorithm>
#include <cstdio>
#include <cstring>

const int kLg = 30, kMaxn = 1e6 + 10;

struct Base {
	int bs[kLg], ps[kLg];
	
	void insert(int x, int p);
	int maxor(int lb) const;
} sum[kMaxn];

int n, m;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 1, ai; i <= n; i++) {
			scanf("%d", &ai);
			sum[i] = sum[i - 1];
			sum[i].insert(ai, i);
		}

		for (int o, x, y, lastans = 0; m--; ) {
			scanf("%d", &o);
			if (o) {
				scanf("%d", &x);
				sum[n + 1] = sum[n];
				sum[n + 1].insert(x ^ lastans, n + 1); ++n;
			} else {
				scanf("%d%d", &x, &y);
				x = (x ^ lastans) % n + 1, y = (y ^ lastans) % n + 1;
				if (x > y) std::swap(x, y);
				printf("%d\n", lastans = sum[y].maxor(x));
			}
		}
	}
	return 0;
}

void Base::insert(int x, int p) {
	if (!x) return;
	for (int i = kLg - 1; i >= 0; i--) {
		if (x >> i & 1 ^ 1) continue;
		if (bs[i]) {
			if (p > ps[i]) {
				std::swap(bs[i], x); std::swap(ps[i], p);
			}
			x ^= bs[i];
			continue;
		}
		bs[i] = x, ps[i] = p; break;
	}
}

int Base::maxor(int lb) const {
	int res = 0;
	for (int i = kLg - 1; i >= 0; i--) {
		if (ps[i] >= lb && (res ^ bs[i]) > res) res ^= bs[i];
	}
	return res;
}
