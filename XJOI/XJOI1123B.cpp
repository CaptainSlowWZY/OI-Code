#include <cstdio>
#include <cctype>
#include <algorithm>

typedef long long LL;

const int kMaxn = 2e6 + 10, kLgN = 21, MOD = 998244353;

int n, q, prv[kMaxn], nxt[kMaxn];
int S[kMaxn], st[kMaxn][kLgN], log[kMaxn], pow[kMaxn];
LL f[kMaxn], g[kMaxn], sumf[kMaxn], sumg[kMaxn];
LL sum[kMaxn], sum2[kMaxn], sumi[kMaxn];

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
namespace online {
	int S, A, B, P, tp;
	LL lastans;

	void init() {
		using fast_io::Read;
		Read(S), Read(A), Read(B), Read(P), Read(tp);
		lastans = 0;
	//	printf("\nS = %d, A = %d, B = %d, P = %d, tp = %d\n", S, A, B, P, tp);
	}
	int Rand() {
		S = (S * A % P + (B ^ (tp * lastans))) % P;
		S = S < 0 ? -S : S;
		return S;
	}
}

inline int Max(int a, int b) {
	return sum[a] > sum[b] ? a : b;
}

int main() {
	using fast_io::Read;

	Read(n), Read(q);
	for (int i = 1; i <= n; i++) {
		Read(sum[i]);
		sum[i] += sum[i - 1];
		sum2[i] = sum2[i - 1] + sum[i - 1];
		sumi[i] = sumi[i - 1] + 1ll * i * sum[i - 1];
	}
	online::init();

	int top = 0;
	for (int i = 1; i <= n; i++) {
		while (top && sum[S[top - 1]] <= sum[i]) --top;
		if (top) prv[i] = S[top - 1];
		S[top++] = i;
		f[i] = f[prv[i]] + LL(i - prv[i]) * sum[i];
		sumf[i] = sumf[i - 1] + f[i];
		st[i][0] = i;
	}
	top = 0;
	for (int i = n; i > 0; i--) {
		while (top && sum[S[top - 1]] <= sum[i]) --top;
		nxt[i] = top ? S[top - 1] : n + 1;
		S[top++] = i;
		g[i] = g[nxt[i]] + LL(nxt[i] - i) * sum[i];
		sumg[i] = sumg[i + 1] + g[i];
	}
	pow[0] = 1, log[0] = -1;
	for (int i = 1; i < kLgN; i++) pow[i] = pow[i - 1] << 1;
	for (int i = 1; i <= n; i++) log[i] = log[i >> 1] + 1;
	for (int i = 1; i < kLgN; i++) {
		for (int j = 1; j + pow[i] - 1 <= n; j++) {
			st[j][i] = Max(st[j][i - 1], st[j + pow[i - 1]][i - 1]);
		}
	}

	LL ret, ans = 0;
	for (int l, r, lg, p; q--; ) {
		using namespace online;
		l = Rand() % n + 1, r = Rand() % n + 1;
		if (l > r) std::swap(l, r);
		lg = log[r - l + 1];
		p = Max(st[l][lg], st[r - pow[lg] + 1][lg]);
		ret = 1ll * sum[p] * (p - l + 1) * (r - p + 1);
		ret += sumf[r] - sumf[p] - f[p] * (r - p);
		ret += sumg[l] - sumg[p] - g[p] * (p - l);
		ret -= LL(r + 1) * (sum2[r] - sum2[l - 1]) - sumi[r] + sumi[l - 1];
		lastans = ret;
		(ans += ret) %= MOD;
	}
	(ans += MOD) %= MOD;

	printf("%lld\n", ans);
	return 0;
}
