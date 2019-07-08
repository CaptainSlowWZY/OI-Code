#include <algorithm>
#include <cstdio>
#include <cstring>

const int MOD = 1e9 + 7;
typedef long long LL;

int _xor[100];

void Calc(LL);

int main() {
	LL A, B;
	scanf("%lld%lld", &A, &B);

	Calc(B);
	Calc(A - 1);
	LL pow2 = 1, ans = 0;
	for (int i = 0; i < 100; i++) {
		if (_xor[i]) (ans += pow2) %= MOD;
		(pow2 <<= 1) %= MOD;
	}

	printf("%lld\n", ans);
	return 0;
}

int cnt[3][100], sum[100];

void Calc(LL n) {
	if (n == 0) return;
	if (n == 1) {
		_xor[0] ^= 1;
		return;
	}
	if (n == 2) {
		_xor[0] ^= 1, _xor[1] ^= 1;
		return;
	}
	LL f1 = 1, f2 = 1, f3, m = 2;
	memset(cnt, 0, sizeof cnt);
	memset(sum, 0, sizeof sum);
	cnt[0][0] = cnt[1][1] = 1;
	sum[0] = sum[1] = 1;
	int d;
	for (d = 2; ; d++) {
		f3 = f1 + f2;
		if (m + f3 > n) break;
		m += f3;
		cnt[2][d] = f3 & 1;	
		cnt[2][d - 1] = 0;
		for (int i = d - 2; i >= 0; i--) {
			cnt[2][i] = cnt[0][i] ^ cnt[1][i];
		}
		for (int i = 0; i <= d; i++) {
			sum[i] ^= cnt[2][i];
			cnt[0][i] = cnt[1][i];
			cnt[1][i] = cnt[2][i];
		}
		f1 = f2, f2 = f3;
	}
	if (n - m & 1) sum[d] = 1;
	for (int i = 0; i <= d; i++) _xor[i] ^= sum[i];
	if (n > m) Calc(n - m - 1);
}
