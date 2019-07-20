#include <cstdio>

typedef long long LL;

const int kMaxn = 1e7 + 5;

int totp;
int P[kMaxn], phi[kMaxn], np[kMaxn];

LL Dfs(int);

int main() {
	phi[1] = 0;
	int N = 1e7;
	for (int i = 2; i <= N; i++) {
		if (!np[i]) P[totp++] = i, phi[i] = i - 1;
		for (int j = 0, d; j < totp &&
				(d = i * P[j]) <= N; j++) {
			np[d] = 1;
			if (i % P[j] == 0) {
				phi[d] = phi[i] * P[j];
				break;
			}
			phi[d] = phi[i] * (P[j] - 1);
		}
	}

	int t, p;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &p);
		printf("%lld\n", Dfs(p));
	}
	return 0;
}

LL FPow(LL bs, int ex, int mod) {
	LL res = 1;
	for (; ex; (bs *= bs) %= mod, ex >>= 1)
		if (ex & 1) (res *= bs) %= mod;
	return res;
}

LL Dfs(int p) {
	if (p <= 1) return 0;
	return FPow(2, Dfs(phi[p]) + phi[p], p);
}
