#include <cstdio>
#include <cctype>
#include <algorithm>

typedef long long LL;

const int kMaxn = 1e5 + 10, kLgN = 18;

int bl[kMaxn];

struct Query {
	int l, r, id;
	bool operator<(const Query & q) const {
	//	return bl[l] == bl[q.l] ? r < q.r : l < q.l;
		return bl[l] == bl[q.l] ? (bl[l] & 1 ? r < q.r : r > q.r) : l < q.l;
	}
} Q[kMaxn];

int n, q, A[kMaxn], prv[kMaxn], nxt[kMaxn];
int S[kMaxn], st[kMaxn][kLgN], log[kMaxn], pow[kMaxn];
LL f[kMaxn], g[kMaxn], ans[kMaxn];

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
LL CalcBack(int l, int r);
LL CalcFront(int l, int r);

int main() {
	using fast_io::Read;

	Read(n), Read(q);
	int Unsz = 0;
	while (Unsz * Unsz < n) ++Unsz;
	for (int i = 1; i <= n; i++) {
		Read(A[i]);
		bl[i] = (i - 1) / Unsz + 1;
	}
	for (int i = 0; i < q; i++) {
		Read(Q[i].l), Read(Q[i].r);
		Q[i].id = i;
	}

	int top = 0;
	for (int i = 1; i <= n; i++) {
		while (top && A[S[top - 1]] >= A[i]) --top;
		if (top) prv[i] = S[top - 1];
		S[top++] = i;
		f[i] = f[prv[i]] + LL(i - prv[i]) * A[i];
		st[i][0] = i;
	}
	top = 0;
	for (int i = n; i > 0; i--) {
		while (top && A[S[top - 1]] >= A[i]) --top;
		nxt[i] = top ? S[top - 1] : n + 1;
		S[top++] = i;
		g[i] = g[nxt[i]] + LL(nxt[i] - i) * A[i];
	}
	pow[0] = 1, log[0] = -1;
	for (int i = 1; i < kLgN; i++) pow[i] = pow[i - 1] << 1;
	for (int i = 1; i <= n; i++) log[i] = log[i >> 1] + 1;
	for (int i = 1; i < kLgN; i++) {
		for (int j = 1; j + pow[i] - 1 <= n; j++) {
			st[j][i] = Min(st[j][i - 1], st[j + pow[i - 1]][i - 1]);
		}
	}

	std::sort(Q, Q + q);
	int hd = 0, tl = 0;
	LL sum = 0;
	for (int i = 0; i < q; i++) {
		while (tl < Q[i].r) {
			sum += CalcBack(hd, ++tl);
		}
		while (tl > Q[i].r) {
			sum -= CalcBack(hd, tl--);
		}
		while (hd < Q[i].l) {
			sum -= CalcFront(hd++, tl);
		}
		while (hd > Q[i].l) {
			sum += CalcFront(--hd, tl);
		}
		ans[Q[i].id] = sum;
	}

	for (int i = 0; i < q; i++) printf("%lld\n", ans[i]);
	return 0;
}

LL CalcBack(int l, int r) {
	if (!r || l > r) return 0;
	l = std::max(1, l), r = std::min(r, n);
	int lg = log[r - l + 1];
	int p = Min(st[l][lg], st[r - pow[lg] + 1][lg]);
	return LL(p - l + 1) * A[p] + f[r] - f[p];
}

LL CalcFront(int l, int r) {
	if (!l || l > r) return 0;
	l = std::max(1, l), r = std::min(r, n);
	int lg = log[r - l + 1];
	int p = Min(st[l][lg], st[r - pow[lg] + 1][lg]);
	return LL(r - p + 1) * A[p] + g[l] - g[p];
}
