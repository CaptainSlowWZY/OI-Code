#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>

#define pb push_back

typedef long long LL;

const int kMod = 998244353, kPhm = kMod - 1;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
int FPow(int bs, int ex = kMod - 2) {
	int res = 1;
	for (; ex; bs = Mul(bs, bs), ex >>= 1)
		if (ex & 1) res = Mul(res, bs);
	return res;
}

const int kLim = 1e6;

LL n;
int totp, ans;
int P[kLim + 5], np[kLim + 5];
std::vector<int> aph;

void PreWork();
bool Mr(LL);
void Dfs(int, int, int);

int main() {
	srand(time(NULL));
	scanf("%lld", &n);
	PreWork();
	for (int i = 0, a; i < totp; ++i) {
		for (a = 0; n > 1 && !(n % P[i]); ++a, n /= P[i]);
		if (a) aph.pb(a);
	}
//	printf(" Mr(%lld) %d\n", n, Mr(n));
	if (n > 1 && Mr(n)) aph.pb(1);
	else if (n > 1) {
		LL p = sqrt(n + 23);
		while (p * p > n) --p;
		while (p * p < n) ++p;
		if (p * p == n) aph.pb(2);
		else { aph.pb(1); aph.pb(1); }
	}
//	for (auto i : aph) printf("%d ", i); puts("");
	Dfs(0, 1, 1);
	printf("%d\n", ans);
	return 0;
}

void PreWork() {
	for (int i = 2; i <= kLim; ++i) {
		if (!np[i]) { P[totp++] = i; }
		for (int j = 0, d; j < totp &&
				(d = i * P[j]) <= kLim; ++j) {
			np[d] = 1;
			if (i % P[j] == 0) break;
		}
	}
}

inline LL Add(LL a, LL b, LL mod) {
	return (a += b) >= mod ? a - mod : a;
}

LL Mul(LL x, LL y, LL mod) {
	LL res = 0;
	for (; y; x = Add(x, x, mod), y >>= 1)
		if (y & 1) res = Add(res, x, mod);
	return res;
}

LL FPow(LL bs, LL ex, LL mod) {
	LL res = 1; bs %= mod;
	for (; ex; bs = Mul(bs, bs, mod), ex >>= 1)
		if (ex & 1) res = Mul(res, bs, mod);
	return res;
}

bool Witness(LL a, LL p) {
	int k = 0;
	LL q = p - 1;
	for (; q & 1 ^ 1; ++k, q >>= 1);
	LL tmp = FPow(a, q, p);
	if (tmp == 1 || tmp == p - 1) return false;
	while (k--) {
		tmp = Mul(tmp, tmp, p);
		if (tmp == p - 1) return false;
	} return true;
}

bool Mr(LL p) {
	if (p == 2) return true;
	if (p & 1 ^ 1) return false;
	for (int i = 0; i < 50; ++i) {
		LL a = rand() % (p - 1) + 1;
		if (Witness(a, p)) return false;
	} return true;
}

void Dfs(int u, int a, int k) {
	if (u == aph.size()) {
		ans = Add(Add(Mul(Sub(FPow(2, k), 1), a), kMod), ans);
		return;
	} Dfs(u + 1, a, k * LL(aph[u] + 1) % kPhm);
	Dfs(u + 1, Mul(-2, a), k * LL(aph[u]) % kPhm);
	if (aph[u] > 1)
		Dfs(u + 1, a, k * LL(aph[u] - 1) % kPhm);
}
