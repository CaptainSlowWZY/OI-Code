#include <cstdio>

#define rg register
#define gch getchar
#define pch putchar

typedef long long LL;

LL N, M;

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = gch());
		}
}

int main() {
	using FastIO::read;

	read(N), read(M);
	LL tmp = N * (N - 1) >> 1;

	printf("%lld", tmp / M);
	pch('.');
	tmp -= tmp / M * M;
	int fcnt = 0;
	for (; fcnt < 5; ++fcnt) {
		pch('0' ^ ((tmp *= 10) / M));
		tmp -= tmp / M * M;
	}
	int t = (tmp *= 10) / M;
	tmp -= tmp / M * M;
	if ((tmp *= 10) / M >= 5) ++t;
	pch('0' ^ t);
	pch('\n');

	return 0;
}

// AC!!!
