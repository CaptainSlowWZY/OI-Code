#include <cstdio>
#include <algorithm>

typedef long long LL;

const int kMaxn = (1 << 18) + 10, MOD = 998244353;

int n, A0[kMaxn];
LL DP[kMaxn], G[kMaxn];

void Solve(int l, int r);

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d", A0 + i);
		A0[i] %= MOD;
	}

	Solve(1, n - 1);

	DP[0] = 1;
	for (int i = 0; i < n; i++) printf("%lld ", (DP[i] + MOD) % MOD);
	putchar('\n');
	return 0;
}

LL FastPow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}

void BitReverse(LL a[], int n) {
	for (int i = 0, j = 0; i < n; i++) {
		if (i > j) std::swap(a[i], a[j]);
		for (int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
}

void DFT(LL a[], int n) {
	BitReverse(a, n);
	for (int i = 2, m; i <= n; i <<= 1) {
		m = i >> 1;
		for (int j = 0; j < n; j += i) {
			for (int k = 0; k < m; k++) {
				LL tmp = a[j + m + k] * G[n / i * k] % MOD;
				a[j + m + k] = (a[j + k] - tmp) % MOD;
				(a[j + k] += tmp) %= MOD;
			}
		}
	}
}

void NTT(LL A_[], int lena, int B_[], int lenb, LL ret[]) {
	int n = 1;
	for (; n <= lena + lenb + 1; n <<= 1);
	static LL A[kMaxn], B[kMaxn];
	for (int i = 0; i < lena; i++) A[i] = A_[i];
	for (int i = lena; i < n; i++) A[i] = 0;
	for (int i = 0; i < lenb; i++) B[i] = B_[i];
	for (int i = lenb; i < n; i++) B[i] = 0;
	G[0] = 1, G[1] = FastPow(3, (MOD - 1) / n);
	for (int i = 2; i < n; i++) G[i] = G[i - 1] * G[1] % MOD;
	DFT(A, n);
	DFT(B, n);
	for (int i = 0; i < n; i++) (A[i] *= B[i]) %= MOD;
	G[1] = FastPow(G[1]);
	for (int i = 2; i < n; i++) G[i] = G[i - 1] * G[1] % MOD;
	DFT(A, n);
	LL in = FastPow(n);
	for (int i = lena - 1; i < lenb; i++) (ret[i] += A[i] * in % MOD) %= MOD;
}

void Solve(int l, int r) {
	if (l == r) return (void)((DP[l] += A0[l]) %= MOD);
	int mid = l + r >> 1;
	Solve(l, mid);
	NTT(DP + l, mid - l + 1, A0 + 1, r - l, DP + l + 1);
	Solve(mid + 1, r);
}
