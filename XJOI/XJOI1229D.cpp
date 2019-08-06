#include <cstdio>

const int kMaxn = 20000;

char IN[10];

namespace bit {
	void Modify(int x);
	int Query(int p);
}

int main() {
	for (int x, y; ~scanf("%s", IN); ) {
		if (IN[0] == 'A') {
			scanf("%d", &x); bit::Modify(x);
		} else if (IN[0] == 'R') {
			scanf("%d", &x); bit::Modify(x);
		} else {
			scanf("%*s%d%*s%d", &x, &y);
			if (x > y) { puts("0"); continue; }
			printf("%d\n", bit::Query(y) ^ bit::Query(x - 1));
		}
	} return 0;
}

namespace bit {
	int T[kMaxn + 10];
	void Modify(int x) {
		for (int p = x; p <= kMaxn; p += p & -p) T[p] ^= x;
	}
	int Query(int p) {
		if (p <= 0) return 0;
		int res = 0;
		for (; p; p &= p - 1) res ^= T[p];
		return res;
	}
}
