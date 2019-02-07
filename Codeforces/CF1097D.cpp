#include <bits/stdc++.h>

#define fir first
#define sec second

const int Lg_N = 51;
const int MOD = 1e9 + 7;

typedef long long LL;
typedef std::pair<LL, int> PLi;

LL N, DP[2][Lg_N], inv[Lg_N];
int K;
std::vector<PLi> D;

void extgcd(LL a, LL b, LL & x, LL & y) {
	if (b) {
		extgcd(b, a % b, y, x);
		y -= a / b * x;
	}
	else { x = 1; y = 0; }
}
LL calc(PLi p);

int main() {
	scanf("%lld%d", &N, &K);
	
	LL n = N;
	int mxk = 0;
	for (LL i = 2; i * i <= n; i++)
		if (n % i == 0) {
			int cnt = 0;
			for (; n % i == 0; n /= i, ++cnt);
			D.push_back(PLi(i, cnt));
			mxk = std::max(mxk, cnt);
		}
	if (n > 1) D.push_back(PLi(n, 1));
	mxk = std::max(mxk, 1);

	for (int i = 0; i <= mxk; i++) {
		LL x, y;
		extgcd(i + 1, MOD, x, y);
		inv[i] = (x % MOD + MOD) % MOD;
	}
	LL ret = 1;
	for (const auto & p : D) (ret *= calc(p)) %= MOD;
	printf("%lld\n", ret);

	return 0;
}

LL calc(PLi p) {
	memset(DP, 0, sizeof DP);
	LL *pre = DP[0], *nxt = DP[1];
	pre[p.sec] = 1;
	for (int i = 1; i <= K; i++) {
		nxt[p.sec] = pre[p.sec] * inv[p.sec] % MOD;
		for (int j = p.sec - 1; j >= 0; j--) nxt[j] = (nxt[j + 1] + pre[j] * inv[j] % MOD) % MOD;
		std::swap(pre, nxt);
	}
	LL ret = 0, pw = 1;
	for (int i = 0; i <= p.sec; i++, (pw *= p.fir) %= MOD)
		(ret += pw * pre[i] % MOD) %= MOD;
	return ret;
}
