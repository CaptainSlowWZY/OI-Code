// CTSC 2017
#include <cstdio>
#include <cctype>

const int MOD = 1e9 + 7;

int n, A[212000], dat[(1 << 9) + 5][(1 << 9) + 5];

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar(); x = 0;
			for (; !isdigit(ch); ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
template <typename T>
void Add(T & x, long long del) {
	x = (x + del) % MOD;
}
void Modify(int p, int v) {
	int fr = p >> 9 ^ 511, bk = p & 511;
	Add(dat[fr][bk], v);
	for (int t = fr - 1 & fr; t != fr; t = t - 1 & fr) Add(dat[t][bk], v);
}
int Query(int p) {
	int fr = p >> 9 ^ 511, bk = p & 511, ret = dat[fr][bk];
	for (int t = bk - 1 & bk; t != bk; t = t - 1 & bk) Add(ret, dat[fr][t]);
	return ret;
}

int main() {
	using fast_io::Read;

	Read(n);
	for (int i = 0; i < n; i++) Read(A[i]);

	int ans = 0;
	for (int i = n - 1, dpi; i >= 0; i--) {
		Add(ans, dpi = (Query(A[i]) + 1) % MOD);
		Modify(A[i], dpi);
	}
	
	ans = (ans - n + MOD) % MOD;
	printf("%d\n", ans);
	return 0;
}
