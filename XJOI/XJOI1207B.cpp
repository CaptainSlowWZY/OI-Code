#include <cstdio>
#include <algorithm>
#include <map>

typedef long long LL;

const int kMod = 1e9 + 7;

int n, P, C;
int A[40];
std::map<int, int> way;

LL FPow(LL bs, int ex = P - 2) {
	LL res = 1;
	for (; ex; (bs *= bs) %= P, ex >>= 1)
		if (ex & 1) (res *= bs) %= P;
	return res;
}

int main() {
	scanf("%d%d%d", &n, &P, &C);
	if (C >= P) {
		puts("0");
		return 0;
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", A + i);
		A[i] %= P;
	}

	int hn = n >> 1;
	for (int mask = (1 << hn) - 1; mask >= 0; --mask) {
		LL mul = 1;
		for (int i = 0; i < hn; i++) {
			if (mask >> i & 1) (mul *= A[i]) %= P;
		}
		++way[mul];
	}
	LL ans = C == 1 ? way[1] - 1 : way[C];
	for (int mask = (1 << n - hn) - 1; mask > 0; --mask) {
		LL mul = 1;
		for (int i = 0; i < n - hn; i++) {
			if (mask >> i & 1) (mul *= A[hn + i]) %= P;
		}
		(ans += way[C * FPow(mul) % P]) %= kMod;
	}
	printf("%lld\n", ans);
	return 0;
}
