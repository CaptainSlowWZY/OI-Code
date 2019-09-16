#include <cstdio>

int n;
int a[200005];

int main() {
	scanf("%d", &n);
	a[0] = 1;
	int ps = 0, ne = 0;
	long long ans1 = 0, ans2 = 0;
	for (int i = 1, ai; i <= n; i++) {
		scanf("%d", &ai);
		if (ai < 0) ai = -1; else ai = 1;
		a[i] = a[i - 1] * ai;
		if (a[i] < 0) {
			ans1 += ps + 1;
			ans2 += ne++;
		} else {
			ans1 += ne;
			ans2 += ++ps;
		}
	} printf("%lld %lld\n", ans1, ans2);
	return 0;
}
