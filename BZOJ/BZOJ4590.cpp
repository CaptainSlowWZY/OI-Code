#include <algorithm>
#include <cstdio>

typedef long long LL;

const int kMaxn = 1e5 + 10;

int n, k;
int X[kMaxn];

int Check(LL l);

int main() {
	scanf("%d%d", &n, &k);
	LL ub0 = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", X + i);
		if (X[i] > 0) ub0 += X[i];
	}
//	ub0 = 0x7f7f7f7f7f7f7f7f;

	LL lb = 1, ub = ub0, ans = -1;
	for (LL mid; lb <= ub; ) {
		mid = lb + ub >> 1;
		int r = Check(mid);
		if (!r) {
			ans = mid;
			ub = mid - 1;
		} else if (r > 0) {
			ub = mid - 1;
		} else lb = mid + 1;
	}
	if (ans == -1) {
		puts("-1");
		return 0;
	}
	printf("%lld ", ans);
	lb = 1, ub = ub0, ans = -1;
	for (LL mid; lb <= ub; ) {
		mid = lb + ub >> 1;
		int r = Check(mid);
		if (!r) {
			ans = mid;
			lb = mid + 1;
		} else if (r > 0) {
			ub = mid - 1;
		} else lb = mid + 1;
	}
	printf("%lld\n", ans);
	return 0;
}

int Check(LL l) {
	LL sum = 0;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		sum = std::max(0ll, sum + X[i]);
		if (sum >= l) {
			sum = 0, ++cnt;
		}
	}
	return cnt == k ? 0 : (cnt > k ? -1 : 1);
}
