#include <cstdio>
#include <cctype>
#include <vector>

#define rg register
#define gch getchar

const int MAXN = 7010, MOD = 998244353;

typedef std::vector<int> Vi;
typedef long long LL;

int N, M, R[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; !isdigit(ch); ch = gch());
			for (x = 0; isdigit(ch); ch = gch())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
inline void add(int & x, int y) { (x += y) >= MOD ? x -= MOD : 0; }
inline void umax(int & x, int y) { x < y ? x = y : 0; }
Vi dp(int u);

int main() {
	using FastIO::read;

	read(N), read(M);
	for (int a, b; M--; ) {
		read(a), read(b);
		umax(R[a], b);
	}
	
	for (int i = N; i > 0; i--) {
		for (int j = i + 1; j <= R[i]; j++) umax(R[i], R[j]);
		umax(R[i], i);
	}
	R[1] = N;

	Vi DP(dp(1));
	int ans = 0;
	for (int i = 0; i < N; i++) add(ans, DP[i]);

	printf("%d\n", ans);
	return 0;
}

Vi dp(int u) {
	Vi ret(R[u] - u + 1);
	ret[0] = 1;
	for (int v = u + 1, mxh = 0; v <= R[u]; v = R[v] + 1) {
		for (int i = 0; i <= mxh; i++) add(ret[i], ret[i - 1]);
		Vi f(dp(v));
		int fsz = f.size();
		for (int i = mxh; i >= 0; i--) {
			LL reti = ret[i];
			ret[i] = 0;
			for (int j = 0; j < fsz; j++) add(ret[i + j], reti * f[j] % MOD);
		}
		if ((mxh += fsz) < v - u) {
			for (int i = mxh + 1; i + v <= u; i++) ret[i] = ret[i - 1];
			mxh = v - u;
		}
	}
	return ret;
}
