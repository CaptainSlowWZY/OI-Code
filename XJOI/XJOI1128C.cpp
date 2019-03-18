#pragma GCC optimize(2, "Ofast")
#include <cstdio>
#include <cassert>
#include <algorithm>

#define rg register

const int MOD = 998244353, kLen = 1 << 20;

typedef long long LL;
typedef LL LAr[kLen + 10];

int n;
LL p, q;
LAr A, G;

namespace fast_io {
	template <typename T>
		void Print(T x) {
			if (!x) return (void)(putchar('0'));
			if (x < 0) x = -x, putchar('-');
			rg int arr[20], len = 0;
			for (; x; arr[len++] = x % 10, x /= 10);
			while (len) putchar(arr[--len] ^ '0');
		}
}
LL FPow(LL bs, LL ex_ = MOD - 2) {
	// assert(ex >= 0);
	LL ret = 1;
	for (rg int ex = ex_ % (MOD - 1); ex;
		(bs *= bs) %= MOD, ex >>= 1) {
		if (ex & 1) (ret *= bs) %= MOD;
	}
	return ret;
}
void Solve(int r);

int main() {
	scanf("%d%lld", &n, &p);

	q = (1 - p) * FPow(p) % MOD;
	LL per = FPow(3, (MOD - 1) / kLen);
	for (rg int i = G[0] = 1; i < kLen; ++i) {
		G[i] = G[i - 1] * per % MOD;
	}
	Solve(n);
	// return 0;
	
	LL invq = FPow(q);
	for (rg int i = 1; i < n; ++i) {
		fast_io::Print((FPow(p, 1ll * (n - i) * i) *
					FPow(invq, 1ll * i * (i + 1) >> 1) % MOD *
					A[n - i] % MOD + MOD) % MOD);
		putchar(' ');
	}
	putchar('\n');
	return 0;
}

void DNT(LL a[], int n) {
	for (rg int i = 0, j = 0; i < n; ++i) {
		if (i > j) std::swap(a[i], a[j]);
		for (int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
	static LAr g;
	for (rg int i = 2, m, d = 1;
		i <= n; i <<= 1, ++d) {
		m = i >> 1;
		for (rg int j = 0, k = 0; j < m; ++j, k += 1 << 20 - d) {
			g[j] = G[k];
		}
		for (rg int j = 0; j < n; j += i) {
			for (rg int k = 0, o = 0; k < m; ++k) {
				LL tmp = a[j + m + k] * g[o++] % MOD;
				a[j + m + k] = (a[j + k] - tmp) % MOD;
				(a[j + k] += tmp) %= MOD;
			}
		}
	}
}

void NTT(LL a[], LL b[], int l_) {
	int n = 1;
	for (; n <= (l_ << 1); n <<= 1);
	for (rg int i = l_ + 1; i < n; ++i) {
		a[i] = b[i] = 0;
	}
	DNT(a, n), DNT(b, n);
	for (rg int i = 0; i < n; ++i) (a[i] *= b[i]) %= MOD;
	std::reverse(a + 1, a + n);
	DNT(a, n);
	LL invn = FPow(n);
	for (rg int i = (l_ << 1); i >= 0; --i) {
		(a[i] *= invn) %= MOD;
	}
}

void Solve(int r) {
	if (r == 1) {
		A[0] = q, A[1] = 1;
		return;
	}
	if (r & 1) {
		Solve(r - 1);
		LL t = FPow(q, r);
		for (rg int i = r; i > 0; --i) {
			A[i] = (A[i] * t % MOD + A[i - 1]) % MOD;
		}
		(A[0] *= t) %= MOD;
		return;
	}
	int mid = r >> 1;
	Solve(mid);
	static LAr buf;
	LL t = FPow(q, mid), cur = 1;
	for (rg int i = mid; i >= 0; --i) {
		buf[i] = A[i] * cur % MOD;
		(cur *= t) %= MOD;
	}
	NTT(A, buf, mid);
}
