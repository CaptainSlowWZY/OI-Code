#include <algorithm>
#include <cstdio>

const int kMaxn = 1e7;

typedef int IAr[kMaxn + 10];
typedef long long LL;

int totp;
IAr np, P, mu, F;

int main() {
	F[1] = 0, mu[1] = 1;
	for (int i = 2; i <= kMaxn; i++) {
		if (!np[i]) {
			P[totp++] = i, mu[i] = -1, F[i] = 1;
		}
		for (int j = 0, d; j < totp && (d = i * P[j]) <= kMaxn; j++) {
			np[d] = 1;
			if (i % P[j] == 0) {
				F[d] = mu[i], mu[d] = 0; break;
			} F[d] = -F[i] + mu[i], mu[d] = -mu[i];
		}
	}
	for (int i = 2; i <= kMaxn; i++) F[i] += F[i - 1];
	int t;
	scanf("%d", &t);
	LL ans;
	for (int n, m; t--; ) {
		scanf("%d%d", &n, &m);
		if (n > m) std::swap(n, m);
		ans = 0;
		for (int i = 1, j; i <= n; i = j + 1) {
		   j = std::min(n / (n / i), m / (m / i));
		   ans += (LL)(F[j] - F[i - 1]) * (n / i) * (m / i);
		}
		printf("%lld\n", ans);
	} 
	return 0;
}
