// pow
#include <cstdio>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define rg register
#define gch getchar
#define pch putchar

typedef long long LL;

const int MILN = 1e6;

int P, powa[MILN + 5], powaa[MILN + 5];
LL A, Q, K, B0, L, M, C;

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
LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex; (bs *= bs) %= P, ex >>= 1) if (ex & 1) (res *= bs) %= P;
	return res;
}

int main() {
	using FastIO::read;
	read(A), read(P), read(Q), read(K);
	read(B0), read(L), read(M), read(C);
	
	powa[0] = powaa[0] = 1;
	for (rg int i = 1; i <= MILN; i++) powa[i] = powa[i - 1] * A % P;
	for (rg int i = 1; i <= MILN; i++) powaa[i] = (LL)powaa[i - 1] * powa[MILN] % P;

	int _xor = 0;
	for (rg int cs = 1; cs <= Q; cs++) {
		LL bi = (M * B0 + C) % L;
		_xor ^= (LL)powaa[bi / MILN] * powa[bi % MILN] % P;
		if (cs % K == 0) {
			FastIO::writeln(_xor);
			if (cs + K > Q) break;
		}
		B0 = bi;
	}
	return 0;
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch(); 
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; ch = gch()) x = (x << 3) + (x << 1) + (ch ^ '0');
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
