#include <algorithm>
#include <cstdio>
#include <cmath>

typedef long long LL;

const LL kInf64 = 0x7f7f7f7f7f7f7f7f, kUbnd = 1e17;
const int kLcm = 60;

int m, k;
int A[55];
LL DP[2][kLcm + 2], *prv = DP[0], *nxt = DP[1];

void Solve();

int main() {
	int q; scanf("%d", &q);
	while (q--) Solve();
	return 0;
}

LL FPow(LL bs, int ex) {
	if (!bs) return 0;
	LL res = 1;
	for (; ex; bs *= bs, ex >>= 1)
		if (ex & 1) res *= bs;
	return res;
}

LL Count(LL x) {
	LL res = 0;
	for (int i = 2; i <= kLcm; ++i) {
		if (!prv[i]) continue;
		LL y = pow((long double)x + 233.0, (long double)1.0 / i);
		while (FPow(y, i) > x) --y;
		res += y * prv[i];
	}
	return res;
}

void Solve() {
	scanf("%d%d", &m, &k);
	std::fill(prv, prv + kLcm + 1, 0);
	prv[1] = -1;
	int f1 = 0;
	for (int i = 0; i < k; ++i) {
		scanf("%d", A + i);
		f1 |= A[i] == 1;
		for (int j = 1; j <= kLcm; ++j)
			nxt[j] = prv[j];
		for (int j = 1, l; j < kLcm; ++j) {
			if (!prv[j]) continue;
			l = j / std::__gcd(j, A[i]) * A[i];
			if (l >= kLcm) {
				nxt[kLcm] -= prv[j]; continue;
			}
			nxt[l] -= prv[j];
		}
		if (prv[kLcm]) nxt[kLcm] -= prv[kLcm];
		std::swap(prv, nxt);
	}
	if (f1) { printf("%d\n", m); return; }
	LL lb = 0, ub = kUbnd;
	for (LL mid; ub - lb > 1; ) {
		mid = lb + ub >> 1;
		if (Count(mid) >= m) ub = mid;
		else lb = mid;
	} printf("%lld\n", ub);
}
