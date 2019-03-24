// Inverse Element of Polynomial
#include <cstdio>
#include <algorithm>

const int kLen = 1 << 18, MOD = 998244353;

typedef long long LL;
typedef LL LAr[kLen + 10];

int n;
LAr A, G, B;

LL FPow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}
namespace poly {
	void Inv(LAr a, int n, LAr b);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lld", A + i);

	LL per = FPow(3, (MOD - 1) / kLen);
	for (int i = G[0] = 1; i < kLen; i++) G[i] = G[i - 1] * per % MOD;
	poly::Inv(A, n, B);
	
	for (int i = 0; i < n; i++) {
		printf("%lld ", (B[i] + MOD) % MOD);
	}
	putchar('\n');
	return 0;
}

namespace poly {
	void DNT(LAr a, int n) {
		for (int i = 0, j = 0; i < n; i++) {
			if (i > j) std::swap(a[i], a[j]);
			for (int l = n >> 1; (j ^= l) < l; l >>= 1);
		}
		for (int i = 2, d = kLen >> 1, h;
			i <= n; i <<= 1, d >>= 1) {
			h = i >> 1;
			for (int j = 0; j < n; j += i) {
				for (int k = 0, o = 0; k < h; k++, o += d) {
					LL tmp = a[j + h + k] * G[o] % MOD;
					a[j + h + k] = (a[j + k] - tmp) % MOD;
					(a[j + k] += tmp) %= MOD;
				}
			}
		}
	}
	void Inv(LAr a, int deg, LAr ia) {
		if (deg == 1) return (void)(ia[0] = FPow(a[0]));
		Inv(a, deg + 1 >> 1, ia);	
		static LAr buf;
		int n = 1;
		for (; n < (deg << 1); n <<= 1);
		for (int i = 0; i < deg; i++) buf[i] = a[i];
		for (int i = deg; i < n; i++) buf[i] = 0;
		DNT(buf, n), DNT(ia, n);
		for (int i = 0; i < n; i++) {
			ia[i] = (2 - buf[i] * ia[i] % MOD) * ia[i] % MOD;
		}
		std::reverse(ia + 1, ia + n);
		DNT(ia, n);
		LL invn = FPow(n);
		for (int i = 0; i < deg; i++) (ia[i] *= invn) %= MOD;
		for (int i = deg; i < n; i++) ia[i] = 0;
	}
}
