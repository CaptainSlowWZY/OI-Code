#include <algorithm>
#include <cstdio>

typedef long long LL;

const int kMaxn = 2e5 + 5, kMod = 1e9 + 7;

int n;
int cnt[kMaxn], fac[kMaxn], ifac[kMaxn];

LL FPow(LL bs, int ex = kMod - 2);
void Solve();

int main() {
	int n = 2e5;
	for (int i = fac[0] = 1; i <= n; i++)
		fac[i] = 1ll * fac[i - 1] * i % kMod;
	ifac[n] = FPow(fac[n]);
	for (int i = n - 1; i >= 0; i--)
		ifac[i] = 1ll * ifac[i + 1] * (i + 1) % kMod;
	int T; scanf("%d", &T);
	while (T--) Solve();
	return 0;
}

LL FPow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= kMod, ex >>= 1)
		if (ex & 1) (res *= bs) %= kMod;
	return res;
}

inline LL C(int n, int r) {
	return 1ll * fac[n] * ifac[r] % kMod * ifac[n - r] % kMod;
}

void Solve() {
	scanf("%d", &n); n <<= 1;
	std::fill(cnt, cnt + n + 1, 0);
	for (int i = 0, Ai; i < n; i++) {
		scanf("%d", &Ai);
		++cnt[Ai];
	}
	for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
	LL ans = 1;
	for (int i = 1, d; i <= n; i++) {
		if (cnt[i] == cnt[i - 1]) {
			continue;
		} d = cnt[i] - cnt[i - 1];
		if (cnt[i - 1] & 1) {
			if (cnt[i] & 1) {
				ans = (C(d, d / 2 - 1) + C(d, d / 2)) % kMod *
					ans % kMod;
			} else {
				ans = ans * C(d, d / 2) % kMod;
			}
		} else {
			if (cnt[i] & 1) {
				ans = ans * C(d, d / 2) % kMod * 2 % kMod;
			} else {
				ans = ans * C(d, d / 2) % kMod;
			}
		}
	}
	printf("%lld\n", ans);
}
