#include <algorithm>
#include <cstdio>
#include <map>

typedef long long LL;

const int kMaxi = 1e6, kInf = 0x3f3f3f3f, kMod = 1e9 + 7;

int N, K, L, H, totp;
int P[kMaxi + 10], smu[kMaxi + 10], np[kMaxi + 10];
std::map<int, int> mp;

LL FPow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= kMod, ex >>= 1) {
		if (ex & 1) (res *= bs) %= kMod;
	} return res;
}
int Smu(int);

int main() {
	scanf("%d%d%d%d", &N, &K, &L, &H);

	smu[1] = 1;
	for (int i = 2; i <= kMaxi; i++) {
		if (!np[i]) { P[totp++] = i, smu[i] = -1; }
		for (int j = 0, d; j < totp && (d = i * P[j]) <= kMaxi; j++) {
			np[d] = 1;
			if (i % P[j] == 0) { smu[d] = 0; break; }
			smu[d] = -smu[i];
		} smu[i] += smu[i - 1];
	}
	int ans = 0;
	L = (L - 1) / K, H /= K;
	for (int i = 1, j, tmp, lst = 0; i <= H; i = j + 1) {
		j = std::min(L / i ? L / (L / i) : kInf, H / (H / i));
		(ans += 1ll * ((tmp = Smu(j)) - lst) *
		 FPow(H / i - L / i, N) % kMod) %= kMod;
	//	printf(" Smu(%d) = %d, Smu(%d) = %d, gap = %d\n",
	//			j, tmp, i - 1, lst, H / i - L / i);
		lst = tmp;
	}
	(ans += kMod) %= kMod;
	printf("%d\n", ans);
	return 0;
}

int Smu(int n) {
	if (n <= kMaxi) return smu[n];
	if (mp.count(n)) return mp[n];
	int & res = mp[n]; res = 1;
	for (int i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i);
		res -= (j - i + 1) * Smu(n / i);
	} return res;
}
