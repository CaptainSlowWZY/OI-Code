// BZOJ 3944
// compile with -std=c++11
#include <cstdio>
#include <utility>
#include <unordered_map>

#define phi first
#define mu second

typedef long long LL;
typedef std::pair<LL, int> PLi;

const int INIT_LIM = 3e6;

int totp, P[216850];
PLi sum[INIT_LIM + 10];
std::unordered_map<int, PLi> ans;

void init();
PLi S(LL n);

int main() {
	init();

	int t;
	LL N;
	for (scanf("%d", &t); t--; ) {
		scanf("%lld", &N);
		PLi res = S(N);
		printf("%lld %d\n", res.phi, res.mu);
	}

	return 0;
}

void init() {
	sum[1] = PLi(1, 1);
	for (int i = 2; i <= INIT_LIM; i++) {
		if (!sum[i].phi) P[totp++] = i, sum[i] = PLi(i - 1, -1);
		for (int j = 0, lmt = INIT_LIM / i; j < totp && P[j] <= lmt; j++) {
			if (i % P[j] == 0) {
				sum[i * P[j]] = PLi(sum[i].phi * P[j], 0);
				break;
			}
			sum[i * P[j]] = PLi(sum[i].phi * (P[j] - 1), -sum[i].mu);
		}
	}
	for (int i = 2; i <= INIT_LIM; i++) {
		sum[i].phi += sum[i - 1].phi;
		sum[i].mu += sum[i - 1].mu;
	}
}

PLi S(LL n) {
	if (n <= INIT_LIM) return sum[n];
	if (ans.count(n)) return ans[n];
	PLi & ret = ans[n];
	ret.phi = LL(n + 1) * n / 2, ret.mu = 1;
	for (LL i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i);
		PLi tmp = S(n / i);
		ret.phi -= LL(j - i + 1) * tmp.phi;
		ret.mu -= (j - i + 1) * tmp.mu;
		if (j >= n) break;
	}
	return ret;
}
