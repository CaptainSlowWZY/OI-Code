#include <algorithm>
#include <cstdio>

typedef long long LL;

const int kMaxn = 5e4;

int totp;
int P[kMaxn + 5], smu[kMaxn + 5], np[kMaxn + 5];
LL S[kMaxn + 5];

int main() {
	S[1] = smu[1] = 1;
	for (int i = 2; i <= kMaxn; i++) {
		if (!np[i]) { P[totp++] = i, smu[i] = -1; }
		for (int j = 0, d; j < totp && (d = i * P[j]) <= kMaxn; j++) {
			np[d] = 1, smu[d] = -smu[i];
			if (i % P[j] == 0) { smu[d] = 0; break; }
		} smu[i] += smu[i - 1];
		for (int j = 1, k; j <= i; j = k + 1) {
			k = i / (i / j);
			S[i] += 1ll * (k - j + 1) * (i / j);
		}
	}
	int t, n, m;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d", &n, &m);
		if (n > m) std::swap(n, m);
		LL ans = 0;
		for (int i = 1, j; i <= n; i = j + 1) {
			j = std::min(n / (n / i), m / (m / i));
			ans += 1ll * (smu[j] - smu[i - 1]) * S[n / i] * S[m / i];
		} printf("%lld\n", ans);
	} return 0;
}
