#include <cstdio>

typedef long long LL;

const int kSqrt = 3163000;

LL phi[kSqrt + 10];
int P[kSqrt + 10], np[kSqrt + 10];
int totp;
LL n;

int main() {
	phi[1] = 1;
	for (int i = 2; i <= kSqrt; i++) {
		if (!np[i]) { P[totp++] = i, phi[i] = i - 1; }
		for (LL j = 0, d; j < totp && (d = i * P[j]) <= kSqrt; j++) {
			np[d] = 1;
			if (i % P[j] == 0) { phi[d] = phi[i] * P[j]; break; }
			phi[d] = phi[i] * (P[j] - 1);
		} // phi[i] += phi[i - 1];
	} int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%lld", &n);
		LL ans = 0;
		for (LL i = 1; i * i <= n; i ++) {
			ans += n / (i * i) * phi[i];
		} printf("%lld\n", ans);
	} return 0;
}
