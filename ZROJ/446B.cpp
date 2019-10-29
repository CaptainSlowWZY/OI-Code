#include <algorithm>
#include <cstdio>

typedef long long LL;

LL ans, n;

bool Check(LL m);

int main() {
	int t; scanf("%d", &t);
	for (LL lb, ub; t--; ) {
		scanf("%lld", &n);
		lb = 0, ub = 1e18, ans = 0;
		for (LL mid; ub - lb > 1; ) {
			mid = lb + ub >> 1;	
			if (Check(mid)) lb = mid;
			else ub = mid;
		} printf("%lld\n", ans);
	} return 0;
}

inline LL Sum(LL x) { return x * (x + 1) >> 1; }

bool Check(LL m) {
	LL s = 0, b = 0;
	for (int i = 0; i < 60; ++i) {
		LL p = 1ll << i;	
		s += p * Sum((m - 1) / p);
		b += (m - 1) / p;
		if (s > n) return false;
	}	
	for (int i = 0; i < 60; ++i) {
		LL p = 1ll << i;
		if (m % p) continue;
		if (s + m <= n) {
			s += m; ++b;
		}
	} ans = std::max(ans, b);
	return true;
}
