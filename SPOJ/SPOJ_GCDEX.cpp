// SPOJ GCDEX 
#include <cstdio>

typedef long long LL;

const int ILIM = (int)1e6 + 1;

int totp, P[ILIM + 5], flag[ILIM + 5], ex[ILIM + 5];
LL f[ILIM + 5];

void init();

int main() {
	init();
	int N;
	while (~scanf("%d", &N) && N) printf("%lld\n", f[N] - LL(N + 1) * N / 2);

	return 0;
}

LL fast_pow(LL bs, int ex_) {
	LL ret = 1;
	for (; ex_; bs *= bs, ex_ >>= 1)
		if (ex_ & 1) ret *= bs;
	return ret;
}

inline LL calc_f(LL p, int ex_) {
	return fast_pow(p, ex_ - 1) * ((p - 1) * ex_ + p);
}

void init() {
	f[1] = 1;
	for (int i = 2; i <= ILIM; i++) {
		if (!flag[i]) P[totp++] = i, f[i] = 2LL * i - 1, ex[i] = 1;
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= ILIM; j++) {
			flag[pd] = 1;
			if (i % P[j] == 0) {
				ex[pd] = ex[i] + 1, f[pd] = calc_f(P[j], ex[pd]) * f[pd / fast_pow(P[j], ex[pd])];
				break;
			}
			ex[pd] = 1, f[pd] = f[i] * f[P[j]];
		}
	}
	for (int i = 2; i <= ILIM; i++) f[i] += f[i - 1];
}
