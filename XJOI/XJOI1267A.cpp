#include <algorithm>
#include <cstdio>

typedef long long LL;

inline LL Abs(LL x) { return x < 0 ? -x : x; }

int main() {
	int n;
	scanf("%d", &n);
	LL f0 = 0, g0 = 0, f1, g1, l0, r0, l1, r1;
	scanf("%lld%lld", &l0, &r0);
	for (int i = 1; i < n; ++i) {
		scanf("%lld%lld", &l1, &r1);
		f1 = std::max(f0 + Abs(l1 - l0), g0 + Abs(l1 - r0));
		g1 = std::max(f0 + Abs(r1 - l0), g0 + Abs(r1 - r0));
		f0 = f1, g0 = g1, l0 = l1, r0 = r1;
	} printf("%lld\n", std::max(f0, g0));
	return 0;
}
