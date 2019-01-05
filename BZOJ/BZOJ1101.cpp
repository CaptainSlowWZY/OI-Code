// BZOJ 1101
// POI 2007
#include <cstdio>
#include <algorithm>

const int MAXA = 5e4;

typedef int IntAr[MAXA + 10];

int A, B, D, totp;
IntAr P, mu, flag;

void init();
void solve();

int main() {
	init();

	int n;
	for (scanf("%d", &n); n--; ) {
		scanf("%d%d%d", &A, &B, &D);
		solve();
	}

	return 0;
}

void init() {
	mu[1] = 1;
	for (int i = 2; i <= MAXA; i++) {
		if (!flag[i]) P[totp++] = i, mu[i] = -1;
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= MAXA; j++) {
			flag[pd] = 1;
			if (i % P[j] == 0) {
				mu[pd] = 0;
				break;
			}
			mu[pd] = -mu[i];
		}
		mu[i] += mu[i - 1];
	}
}

void solve() {
	A /= D, B /= D;
	if (A < B) std::swap(A, B);
	long long ans = 0;
	for (int i = 1, j; i <= A; i = j + 1) {
		if (B / i == 0) break;
		j = std::min(A / (A / i), B / (B / i));	
		ans += (long long)(mu[j] - mu[i - 1]) * (A / i) * (B / i);
	}
	printf("%lld\n", ans);
}
