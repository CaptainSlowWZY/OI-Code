#include <algorithm>
#include <cstdio>

typedef long long LL;

int n;

int main() {
	scanf("%d", &n);
	LL rem = 0, ai, t, ans = 0;
	for (int i = 0; i < n; i++) {
		scanf("%lld", &ai);
		if (rem) {
			t = std::min(ai / 2, rem);
			ai -= t * 2, ans += t, rem -= t;
		}
		if (ai >= 3) {
			ans += ai / 3;
			ai = ai % 3;
		} rem += ai;
	} printf("%lld\n", ans);
	return 0;
}
