// Codeforces 1060 D
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int MAXN = 1e5 + 10;

int N, A[MAXN], B[MAXN];

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}

int main() {
	using FastIO::read;
	read(N);
	for (int i = 0; i < N; i++) read(A[i]), read(B[i]);
	std::sort(A, A + N);
	std::sort(B, B + N);
	LL ans = N;
	for (int i = 0; i < N; i++) ans += std::max(A[i], B[i]);
	printf("%I64d\n", ans);
	return 0;
}
