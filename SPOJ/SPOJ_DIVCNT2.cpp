// SPOJ DIVCNT2
#include <cstdio>
#include <cmath>
#include <algorithm>

typedef long long LL;

const int MAXL = 1e8;
const int MAXT = 1e4;

int T, totp, P[MAXL + 10], flag[MAXL + 10], mu[MAXL + 10], sumh[MAXL + 10], mpa[MAXL + 10];
LL INIT_LIM, mx, A[MAXT + 10], sums[MAXL + 10];

inline LL sqr(LL x) { return x * x; }
void init();
LL solve(LL n);

int main() {
	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		scanf("%lld", A + i);
		mx = std::max(mx, A[i]);
	}

	INIT_LIM = pow(mx, 2.0 / 3.0);
	init();

	for (int i = 0; i < T; i++) printf("%lld\n", solve(A[i]));

	return 0;
}

void init() {
	mu[1] = sumh[1] = sums[1] = 1;
	for (int i = 2; i <= INIT_LIM; i++) {
		if (!flag[i]) P[totp++] = i, mu[i] = -1, sums[i] = mpa[i] = 2;
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= INIT_LIM; j++) {
			flag[pd] = 1;
			if (i % P[j] == 0) {
				mu[pd] = 0;
				mpa[pd] = mpa[i] + 1;
				sums[pd] = sums[i] / mpa[i] * mpa[pd];
				break;
			}
			mu[pd] = -mu[i];
			mpa[pd] = 2;
			sums[pd] = sums[i] * 2;
		}
		sumh[i] = sumh[i - 1] + std::abs((int)mu[i]);
		sums[i] += sums[i - 1];
	}
}

LL Sh(LL n) {
	if (n <= INIT_LIM) return sumh[n];
	LL ret = 0;
	for (LL i = 1; i * i <= n; i++)
		if (mu[i]) ret += mu[i] < 0 ? - (n / sqr(i)) : n / sqr(i);
	return ret;
}

LL Ssgm(LL n) {
	if (n <= INIT_LIM) return sums[n];
	LL ret = 0;
	for (LL i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ret += (j - i + 1) * (n / i);
	}
	return ret;
}

LL solve(LL n) {
	LL pre = 0, nxt, ret = 0;
	for (LL i = 1, j; i <= n; i = j + 1, pre = nxt) {
		j = n / (n / i);
		nxt = Sh(j);
		ret += (nxt - pre) * Ssgm(n / i);
	}
	return ret;
}
