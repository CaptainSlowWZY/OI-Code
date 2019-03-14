// CTSC 2018
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int kMaxn = 5e4 + 10, kLen = 1 << 18, MOD = 998244353;

int T, n, L[kMaxn], S[kMaxn];
LL F[kLen];

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar();
			register bool f = false; x = 0;
			for (; !isdigit(ch); f |= (ch == '-'), ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
}
template <typename T>
inline LL & Add(T & x, LL y) {
	return x = (x + y) % MOD;
}
template <typename T>
inline LL & Mult(T & x, LL y) {
	return x = x * y % MOD;
}
void Solve(int l, int r);

int main() {
	using fast_io::Read;

	Read(T), Read(n);
	
	F[0] = 1, F[1] = 2;
	if (n > 2) Solve(2, n);

	for (; T--; ) {
		for (int i = 1; i <= n; i++) {
			Read(L[i]);
			L[i] = i - L[i] + 1;
		}
		if (L[1] != 1 || L[n] != 1) {
			puts("0");
			continue;
		}
		int top = 0, fail = 0;
		LL ans = 1;
		for (int i = 1, sz; i <= n; i++) {
			for (sz = 0; top && L[i] <= S[top - 1]; ) {
				if (L[i] > L[S[top - 1]]) {
					fail = 1;
					break;
				}
				++sz, --top;
			}
			if (fail) break;
			S[top++] = i;
			Mult(ans, F[sz]);
		}
		Add(ans, MOD);
		printf("%lld\n", fail ? 0 : ans);
	}

	return 0;
}

LL FPow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; Mult(bs, bs), ex >>= 1)
		if (ex & 1) Mult(ret, bs);
	return ret;
}

LL G[kLen];

void DNT(LL A[], int n) {
	for (int i = 0, j = 0; i < n; i++) {
		if (i > j) std::swap(A[i], A[j]);
		for (int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
	for (int i = 2, m, d = n >> 1; i <= n; i <<= 1, d >>= 1) {
		m = i >> 1;
		for (int j = 0; j < n; j += i) {
			for (int k = 0, o = 0; k < m; k++, o += d) {
				LL tmp = A[j + m + k] * G[o] % MOD;
				A[j + m + k] = (A[j + k] - tmp) % MOD;
				Add(A[j + k], tmp);
			}
		}
	}
}

void NTT(LL A[], int dega, LL B[], int degb) {
	int n = 1;
	for (; n <= dega + degb; n <<= 1);
	assert(n < kLen);
	for (int i = dega; i < n; i++) A[i] = 0;
	for (int i = degb; i < n; i++) B[i] = 0;
	G[0] = 1, G[1] = FPow(3, (MOD - 1) / n);
	for (int i = 2; i < n; i++) G[i] = G[i - 1] * G[1] % MOD;
	DNT(A, n), DNT(B, n);
	for (int i = 0; i < n; i++) Mult(A[i], B[i]);
	G[1] = FPow(G[1]);
	for (int i = 2; i < n; i++) G[i] = G[i - 1] * G[1] % MOD;
	DNT(A, n);
	LL inv = FPow(n);
	for (int i = 0; i < n; i++) Mult(A[i], inv);
}

void Solve(int l, int r) {
	if (l == r) return (void)Add(F[l], F[l - 1] * (l - 1) % MOD);
	int mid = l + r >> 1;
	Solve(l, mid);
	static LL A[kLen], B[kLen];
	for (int i = l; i <= mid; i++) {
		A[i - l] = (i - 1) * F[i] % MOD;
		B[i - l] = F[i];
	}
	NTT(A, mid - l + 1, B, mid - l + 1);
	for (int i = std::max(l << 1, mid + 1); i <= r; i++) {
		Add(F[i], A[i - (l << 1)]);
	}
	if (l != 2) {
		int lmt = std::min(l - 1, r - l);
		for (int i = 2; i <= lmt; i++) {
			A[i - 2] = F[i];
		}
		for (int i = l; i <= mid; i++) {
			B[i - l] = F[i];
		}
		NTT(A, lmt - 1, B, mid - l + 1);
		for (int i = std::max(l + 2, mid + 1); i <= r; i++) {
			Add(F[i], Mult(A[i - l - 2], i - 2));
		}
	}
	Solve(mid + 1, r);
}
