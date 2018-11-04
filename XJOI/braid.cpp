// braid
#include <cstdio>
#include <algorithm>

#define rg register
#define gch getchar
#define pch putchar

typedef long long LL;

const int TOTFAC = 96;
int FACT[] = {1, 17, 7, 119, 2, 34, 14, 238, 4, 68, 28, 476, 8, 136, 56, 952, 16, 272, 112, 1904, 32, 544, 224, 3808, 64, 1088, 448, 7616, 128, 2176, 896, 15232, 256, 4352, 1792, 30464, 512, 8704, 3584, 60928, 1024, 17408, 7168, 121856, 2048, 34816, 14336, 243712, 4096, 69632, 28672, 487424, 8192, 139264, 57344, 974848, 16384, 278528, 114688, 1949696, 32768, 557056, 229376, 3899392, 65536, 1114112, 458752, 7798784, 131072, 2228224, 917504, 15597568, 262144, 4456448, 1835008, 31195136, 524288, 8912896, 3670016, 62390272, 1048576, 17825792, 7340032, 124780544, 2097152, 35651584, 14680064, 249561088, 4194304, 71303168, 29360128, 499122176, 8388608, 142606336, 58720256, 998244352};

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

LL fast_pow(LL bs, int ex, LL MOD) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1) if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}

int main() {
	std::sort(FACT, FACT + TOTFAC);
	using FastIO::read;

	int T;
	read(T);
	for (rg LL N, M, X, K; T--; ) {
		read(N), read(M), read(X), read(K);
		int i;
		for (i = 0; i < TOTFAC; i++) {
			if (fast_pow(K, FACT[i], N) == 1) break;
		}
		if (FACT[i] & 1) {
			if (M >= FACT[i]) FastIO::writeln(N - FACT[i] + 1);
			else FastIO::writeln(N - M);
		}
		else FastIO::writeln(N - std::min(M, (LL)FACT[i] >> 1));
	}

	return 0;
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
