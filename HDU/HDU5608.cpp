// HDU 5608
#include <cstdio>
#include <map>

const int INIT_LIM = 5e6;
const int MOD = 1e9 + 7;
const int INV_2 = 500000004;
const int INV_6 = 166666668;

typedef long long LL;
typedef int IntArr[INIT_LIM + 10];

int totp;
IntArr P, flag, sum, mu;
std::map<int, int> ans;

inline void sub(int & x, int d) { (x -= d) %= MOD; }
inline void add(int & x, int d) { (x += d) %= MOD; }
inline LL sqr(LL x) { return x * x % MOD; }
inline LL g(int n) { return (sqr(n) - 3LL * n + 2) % MOD; }
int Sumf(int n);
void init();

int main() {
	init();

	int N, t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &N);
		printf("%d\n", (Sumf(N) + MOD) % MOD);
	}

	return 0;
}

void init() {
	mu[1] = 1;
	for (int i = 2; i <= INIT_LIM; i++) {
		if (!flag[i]) P[totp++] = i, mu[i] = -1;
		for (int j = 0, d; j < totp && (d = i * P[j]) <= INIT_LIM; j++) {
			flag[d] = 1;
			if (i % P[j] == 0) {
				mu[d] = 0;
				break;
			}
			mu[d] = -mu[i];
		}
	}
	for (int i = 1; i <= INIT_LIM; i++)
		for (int j = i, t = 1; j <= INIT_LIM; j += i, ++t)
			add(sum[j], g(t) * mu[i] % MOD);
	for (int i = 2; i <= INIT_LIM; i++) add(sum[i], sum[i - 1]);
}

int Sumf(int n) {
	if (n <= INIT_LIM) return sum[n];
	if (ans.count(n)) return ans[n];
	int & ret = ans[n];
	ret = (LL(n + 1) * n % MOD * (2LL * n + 1) % MOD * INV_6 % MOD - 3LL * n % MOD * (n + 1) % MOD * INV_2 % MOD + 2LL * n % MOD) % MOD;
	for (int i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i);
		sub(ret, LL(j - i + 1) * Sumf(n / i) % MOD);
	}
	return ret;
}
