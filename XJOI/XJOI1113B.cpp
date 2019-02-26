#include <cstdio>
#include <cmath>

typedef long long LL;

namespace Min_25 {
	LL solve(LL);
}

int main() {
	LL a, b;
	scanf("%lld%lld", &a, &b);
	
	using Min_25::solve;
	printf("%lld\n", solve(b) - solve(a - 1));
	return 0;
}

namespace Min_25 {
	const int ARSZ = 1e6 + 5;
	typedef int IntAr[ARSZ];

	IntAr flag, P, id1, id2;
	int tota, totp;
	LL N, SQRT, A[ARSZ], g[ARSZ];

	inline LL id(LL n_) {
		return n_ <= SQRT ? id1[n_] : id2[N / n_];
	}
	void init() {
		for (LL i = 2; i <= SQRT; i++) {
			if (!flag[i]) P[totp++] = i;
			for (int j = 0; j < totp && i * P[j] <= SQRT; j++) {
				flag[i * P[j]] = 1;
				if (i % P[j] == 0) break;
			}
		}
		for (LL i = 1, j; i <= N; i = j + 1) {
			j = N / (N / i);
			A[tota] = N / i;
			if (A[tota] <= SQRT) id1[A[tota]] = tota;
			else id2[N / A[tota]] = tota;
			g[tota] = A[tota] - 1;
			++tota;
		}
		for (int i = 0; i < totp; i++)
			for (int j = 0; j < tota && (LL)P[i] * P[i] <= A[j]; j++)
				g[j] -= g[id(A[j] / P[i])] - i;
	}
	LL S(LL n, int k) {
		if (n <= 1 || P[k] > n) return 0;
		LL ret = 3LL * (g[id(n)] - k);
		for (int i = k; i < totp && (LL)P[i] * P[i] <= n; i++) {
			LL p1 = P[i], p2 = 1LL * P[i] * P[i];
			for (int j = 1; p2 <= n; ++j, p1 = p2, p2 *= P[i])
				ret += S(n / p1, i + 1) * (2 * j + 1) + (2 * j + 3);
		}
		return ret;
	}
	LL solve(LL n_) {
		totp = tota = 0, N = n_, SQRT = floor(sqrt(n_ + 0.5));
		init();
		return S(n_, 0) + 1LL + n_ >> 1;
	}
}
