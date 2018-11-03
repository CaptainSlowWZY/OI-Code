// gwent
#include <cstdio>

#define rg register
#define gch getchar
#define pch putchar

typedef long long LL;

const int MOD = 998244353;
const int INIT = 1e6 + 10;

int N, A[1010], rq[1010], fac[INIT + 5], inv[INIT + 5];

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), pch('\n');
		}
}
template <typename T1, typename T2>
inline void mult(T1 & x, T2 y) { x = (LL)x * y % MOD; }

LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex; mult(bs, bs), ex >>= 1) if (ex & 1) mult(res, bs);
	return res;
}
inline LL get_inv(LL x) { return fast_pow(x, MOD - 2); }
inline int C(int n, int r) { return (LL)fac[n] * inv[r] % MOD * inv[n - r] % MOD; }
void init();
void solve();

int main() {
	init();

	int t;
	for (FastIO::read(t); t--; ) solve();

	return 0;
}

void init() {
	fac[0] = 1;
	for (LL i = 1; i <= INIT; i++) fac[i] = i * fac[i - 1] % MOD;
	inv[INIT] = get_inv(fac[INIT]);
	for (LL i = INIT - 1; i >= 0; i--) inv[i] = (i + 1) * inv[i + 1] % MOD; 
}

void solve() {
	using FastIO::read;

	read(N);
	int avg = 0;
	for (int i = 0; i < N; i++) {
		read(A[i]);
		avg += A[i];
	}

	avg /= N;
	for (int i = 0; i < N; i++) rq[i] = avg;
	int ans = 1;
	for (int i = 0; i + 1 < N; i++)
		if (A[i] <= rq[i]) {
			rq[i + 1] += rq[i] - A[i];
			mult(ans, C(rq[i + 1], rq[i] - A[i]));
		}
		else {
			A[i + 1] += A[i] - rq[i]; 
			mult(ans, C(A[i], rq[i]));
		}
	
	FastIO::writeln(ans);
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = gch());
		}
	template <typename T>
		void write(T x) {
			if (!x) return (void)pch('0');
			if (x < 0) x = -x, pch('-');
			rg int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) pch(arr[--len] ^ '0');
		}
}

// AC!!!