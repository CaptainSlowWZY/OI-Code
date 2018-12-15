// BZOJ 2844
#include <cstdio>
#include <vector>

typedef long long LL;

const int MOD = 10086;

struct Linear_Basis {
	static const int LgInt = 30;
	int bs[LgInt + 5];
	std::vector<int> bit;

	int size() const { return (int)bit.size(); }
	void insert(int x);
	void init();
	int rank(int x) const;
} B;

int N, Q;

LL fast_pow(LL bs, int ex) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}

int main() {
	scanf("%d", &N);
	for (int i = 0, Ai; i < N; i++) {
		scanf("%d", &Ai);
		B.insert(Ai);
	}
	scanf("%d", &Q);

	B.init();
	int rk = B.rank(Q);
	printf("%d", ((LL)rk % MOD * fast_pow(2, N - B.size()) + 1) % MOD);

	return 0;
}

void Linear_Basis::insert(int x) {
	for (int i = LgInt; i >= 0; i--)
		if (x >> i & 1) {
			if (bs[i]) x ^= bs[i];
			else {
				for (int j = i - 1; j >= 0; j--)
					if (bs[j] && x >> j & 1) x ^= bs[j];
				bs[i] = x;
				for (int j = i + 1; j <= LgInt; j++)
					if (bs[j] >> i & 1) bs[j] ^= x;
				break;
			}
		}
}

void Linear_Basis::init() {
	for (int i = 0; i <= LgInt; i++)
		if (bs[i]) bit.push_back(i);
}

int Linear_Basis::rank(int x) const {
	int rk = 0;
	for (int i = 0, sz = bit.size(); i < sz; i++)
		if (x >> bit[i] & 1) rk |= 1 << i;
	return rk;
}