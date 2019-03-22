#include <cstdio>
#include <cctype>
#include <algorithm>

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
	template <typename T>
		void Print(T x) {
			if (!x) return (void)(putchar('0'));
			if (x < 0) x = -x, putchar('-');
			register int arr[20], len = 0;
			for (; x; arr[len++] = x % 10, x /= 10);
			while (len) putchar(arr[--len] ^ '0');
		}
	template <>
		void Print(const char * buff) {
			for (register int i = 0; buff[i]; ++i) putchar(buff[i]);
		}
	template <typename T>
		inline void Println(T x) {
			Print(x), putchar('\n');
		}
}

#ifdef DEBUG
	#define db(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define db(format, ...) 0
#endif

const int kLen = 1 << 17, MOD = 998244353, kMaxn = 1e5;

typedef long long LL;
typedef int IAr[kLen + 10];

int q, sum;
IAr A, B, G, fac, ifac;

void Init();

int main() {
	Init();
	using fast_io::Read;

	Read(q);
	for (int n, ans; q--; ) {
		Read(n);
		ans = (LL)B[n] * ifac[n - 1] % MOD;
		ans = (ans + MOD) % MOD;
		fast_io::Println(ans);
	}
	return 0;
}

template <typename T> inline
void Add(T & x, LL y) {
	x = (x + y) % MOD;
}

template <typename T> inline
void Mult(T & x, LL y) {
	x = x * y % MOD;
}

void DNT(IAr a, int n) {
	for (int i = 0, j = 0; i < n; i++) {
		if (i > j) std::swap(a[i], a[j]);
		for (int l = n >> 1; (j ^= l) < l; l >>= 1);
	}
	for (int i = 2, h, d = kLen >> 1;
			i <= n; i <<= 1, d >>= 1) {
		h = i >> 1;
		for (int j = 0; j < n; j += i) {
			for (int k = 0, tmp, o = 0;
				k < h; k++, o += d) {
				tmp = (LL)a[j + h + k] * G[o] % MOD;
				a[j + h + k] = (a[j + k] - tmp) % MOD;
				Add(a[j + k], tmp);
			}
		}
	}
}

LL FPow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; Mult(bs, bs), ex >>= 1)
		if (ex & 1) Mult(ret, bs);
	return ret;
}

void NTT(IAr a, int lena, IAr b, int lenb) {
	int n = 1;
	for (; n < lena + lenb; n <<= 1);
	for (int i = lena; i < n; i += 4) {
		a[i] = 0, a[i + 1] = 0, a[i + 2] = 0, a[i + 3] = 0;
	}
	for (int i = lenb; i < n; i += 4) {
		b[i] = 0, b[i + 1] = 0, b[i + 2] = 0, b[i + 3] = 0;
	}
	DNT(a, n), DNT(b, n);
	for (int i = 0; i < n; i++) Mult(a[i], b[i]);
	std::reverse(a + 1, a + n);
	DNT(a, n);
	LL invn = FPow(n);
	for (int i = 0; i < n; i++) Mult(a[i], invn);
}

void Solve(int l, int r) {
	if (l == r) {
		if (l == 1) return;
		A[l] = (LL)fac[l - 2] * (sum - A[l]) % MOD;
		Add(sum, (LL)A[l] * ifac[l - 1] % MOD);
		B[l] = (fac[l - 1] - A[l]) % MOD;
		return;
	}
	int mid = l + r >> 1;
	Solve(l, mid);
	static IAr a, b;
//	[l, mid] * [l, mid] --+-> [mid + 1, r]
	for (int i = l; i <= mid; i++) {
		b[i - l] = a[i - l] = (LL)A[i] * ifac[i - 1] % MOD;
	}
	NTT(a, mid - l + 1, b, mid - l + 1);
	for (int i = std::max(l << 1, mid + 1); i <= r; i++) {
		Add(A[i], a[i - (l << 1)]);
	}
	//	[1, ?] * [l, mid] --+-> [mid + 1, r]
	if (l > 1) {
		int lmt = std::min(l - 1, r - l + 1);
		for (int i = 1; i <= lmt; i++) {
			a[i - 1] = (LL)A[i] * ifac[i - 1] % MOD;
		}
		for (int i = l; i <= mid; i++) {
			b[i - l] = (LL)A[i] * ifac[i - 1] % MOD;
		}
		NTT(a, lmt, b, mid - l + 1);
		for (int i = std::max(l + 1, mid + 1); i <= r; i++) {
			Add(A[i], 2ll * a[i - l - 1] % MOD);
		}
	}
	Solve(mid + 1, r);
}

void Init() {
	fac[0] = fac[1] = 1;
	for (LL i = 2; i <= kMaxn; i++) {
		fac[i] = i * fac[i - 1] % MOD;
	}
	ifac[kMaxn] = FPow(fac[kMaxn]);
	for (LL i = kMaxn - 1; i >= 0; i--) {
		ifac[i] = ifac[i + 1] * (i + 1) % MOD;
	}
//	A - invalid, B - valid
	A[1] = 1, B[1] = 0;
	sum = 1;
	LL per = FPow(3, (MOD - 1) / kLen);
	for (int i = G[0] = 1; i < kLen; i++) {
		G[i] = G[i - 1] * per % MOD;
	}
	Solve(1, kMaxn);
}
