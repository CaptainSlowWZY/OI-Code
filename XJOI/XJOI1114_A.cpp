#include <cstdio>
#include <algorithm>
#include <vector>

typedef long long LL;

const int kMaxp = 1e6 + 10;
const LL kINF64 = 0x3f3f3f3f3f3f3f3f;

LL L, R, P, maxk[kMaxp];
std::vector<int> SR[kMaxp];

inline LL Sqr(LL x) { return x * x; }
LL Calc(LL n);
void PreWork(LL p0, int k0);

int main() {
	scanf("%lld%lld%lld", &L, &R, &P);
	
	LL rem = P;
	for (LL i = 2; i <= rem; i++)
		if (rem % i == 0) {
			int cnt;
			for (cnt = 0; rem % i == 0; rem /= i, ++cnt);
			PreWork(i, cnt);
		}
	if (rem > 1) PreWork(rem, 1);

	printf("%lld\n", Calc(R) - Calc(L - 1));
	return 0;
}

LL Calc(LL n) {
	if (!n) return 0;
	LL ret = 0;
	for (int i = 0; i < P; i++) {
		if (maxk[i] == kINF64 || Sqr(maxk[i]) >= n) continue;
		ret += (n - i) / P - (Sqr(maxk[i]) - i) / P;
		if (n >= i) ++ret;
		if (Sqr(maxk[i]) >= i) --ret;
	}
	return ret;
}

void PreWork(LL p0, int k0) {
	for (int i = 0; i < p0; i++) SR[i].clear();
	for (LL i = 0; i < p0; i++) SR[i * i % p0].push_back(i);
	for (int i = 0, j, r; i < P; i++) {
		if (maxk[i] == kINF64) continue;
		if (SR[r = i % p0].empty()) {
			maxk[i] = kINF64;
			continue;
		}
		const std::vector<int> & V = SR[r];
		int ret = 0, k = k0;
		for (j = 0; k > 0; ) {
			if (j == (int)V.size()) {
				ret += p0 - 1 - V[j - 1];
				j = 0;
			}
			LL t = i - (LL)V[j] * V[j];
			for (; t % p0 == 0 && k > 0; t /= p0, --k);
			if (j) ret -= V[j - 1];
			ret += V[j];
		}
		maxk[i] = std::max(maxk[i], (LL)ret);
	}
}
