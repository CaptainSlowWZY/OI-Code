#include <cstdio>

const int kMaxk = 1e5 + 5, kMod = 998244353;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

int t, n, k, ans, l, r;
int inv[kMaxk];

int main() {
	inv[1] = 1;
	for (int i = 2; i <= 100000; ++i)
		inv[i] = Sub(kMod, Mul(kMod / i, inv[kMod % i]));
	scanf("%d", &t);
	for (int o; t--; ) {
		scanf("%d", &o);
		if (o == 1) {
			scanf("%d%d", &n, &k);
			if (n <= k) {
				printf("%d\n", FPow(2, n));
				continue;
			}
			for (int i = ans = 0, c = 1; i <= k; ++i) {
				ans = Add(ans, c);
				c = Mul(c, Mul(n - i, inv[i + 1]));
			} 
		} else {
			scanf("%d%d%d", &l, &r, &k);
			ans = 0;
			for (int i = 1, c = Add(r, 1); i <= r + 1 && i <= k + 1; ++i) {
				ans = Add(ans, c);
				c = Mul(c, Mul(r + 1 - i, inv[i + 1]));
			}
			for (int i = 1, c = l; i <= l && i <= k + 1; ++i) {
				ans = Sub(ans, c);
				c = Mul(c, Mul(l - i, inv[i + 1]));
			}
		} printf("%d\n", ans);
	} return 0;
}
