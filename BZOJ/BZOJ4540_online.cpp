#include <cstdio>
#include <cctype>

typedef long long LL;

const int kMaxn = 1e5 + 10, kLgN = 18;

int n, q, A[kMaxn], prv[kMaxn], nxt[kMaxn];
int S[kMaxn], st[kMaxn][kLgN], log[kMaxn], pow[kMaxn];
LL f[kMaxn], g[kMaxn], sumf[kMaxn], sumg[kMaxn];

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
inline int Min(int a, int b) {
	return A[a] < A[b] ? a : b;
}

int main() {
	using fast_io::Read;

	Read(n), Read(q);
	for (int i = 1; i <= n; i++) {
		Read(A[i]);
	}

	int top = 0;
	for (int i = 1; i <= n; i++) {
		while (top && A[S[top - 1]] >= A[i]) --top;
		if (top) prv[i] = S[top - 1];
		S[top++] = i;
		f[i] = f[prv[i]] + LL(i - prv[i]) * A[i];
		sumf[i] = sumf[i - 1] + f[i];
		st[i][0] = i;
	}
	top = 0;
	for (int i = n; i > 0; i--) {
		while (top && A[S[top - 1]] >= A[i]) --top;
		nxt[i] = top ? S[top - 1] : n + 1;
		S[top++] = i;
		g[i] = g[nxt[i]] + LL(nxt[i] - i) * A[i];
		sumg[i] = sumg[i + 1] + g[i];
	}
	pow[0] = 1, log[0] = -1;
	for (int i = 1; i < kLgN; i++) pow[i] = pow[i - 1] << 1;
	for (int i = 1; i <= n; i++) log[i] = log[i >> 1] + 1;
	for (int i = 1; i < kLgN; i++) {
		for (int j = 1; j + pow[i] - 1 <= n; j++) {
			st[j][i] = Min(st[j][i - 1], st[j + pow[i - 1]][i - 1]);
		}
	}

	LL ans;
	for (int l, r, lg, p; q--; ) {
		Read(l), Read(r);
		lg = log[r - l + 1];
		p = Min(st[l][lg], st[r - pow[lg] + 1][lg]);
		ans = 1ll * A[p] * (p - l + 1) * (r - p + 1);
		ans += sumf[r] - sumf[p] - f[p] * (r - p);
		ans += sumg[l] - sumg[p] - g[p] * (p - l);
		printf("%lld\n", ans);
	}
	return 0;
}
