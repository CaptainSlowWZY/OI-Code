#include <bits/stdc++.h>

#define fir first
#define sec second

typedef long long LL;
typedef std::pair<LL, int> P;

const LL INF = 0x7fffffffffffffff;

std::vector<P> V;

LL fast_pow(LL bs, int ex) {
	LL ret = 1;
	for (; ex; bs *= bs, ex >>= 1)
		if (ex & 1) ret *= bs;
	return ret;
}

int main() {
	LL N, B;
	scanf("%lld%lld", &N, &B);
	LL b = B;
	for (LL i = 2; i * i <= B && i <= b; i++)
		if (b % i == 0) {
			P tmp(i, 0);
			for (; b % i == 0; b /= i) ++tmp.sec;
			V.push_back(tmp);
		}
	if (b > 1) V.push_back(P(b, 1));

	LL ans = INF;
	for (auto p : V) {
		LL sum = 0;
		for (LL pw = p.fir, k = 1; pw <= N; pw *= p.fir, ++k) {
			if (pw > N / p.fir) {
				sum += k * (N / pw);
				break;
			}
			sum += k * (N / pw - N / (pw * p.fir));
		}
		ans = std::min(ans, sum / p.sec);
	}
	printf("%lld\n", ans == INF ? 0 : ans);
	return 0;
}
