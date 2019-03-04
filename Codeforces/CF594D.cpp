#include <cstdio>
#include <cctype>
#include <algorithm>

const int kMaxn = 2e5 + 10, kMaxa = 1e6 + 10, MOD = 1e9 + 7;

typedef long long LL;
typedef int IntArr[kMaxn];

struct Query {
	int l, r, id;
	bool operator<(const Query & q) const {
		return r < q.r;
	}
} qry[kMaxn];

int n, q, totp, A[kMaxn], ans[kMaxn], prod[kMaxn], P[kMaxa], flag[kMaxa], minp[kMaxa], last[kMaxa];

namespace bit {
	LL T[kMaxn];

	void init() {
		for (int i = 1; i <= n; i++) T[i] = 1;
	}
	void Mult(int p, LL v) {
		for (; p <= n; p += p & -p) (T[p] *= v) %= MOD;
	}
	LL Query(int p) {
		LL ret = 1;
		for (; p > 0; p &= p - 1) (ret *= T[p]) %= MOD;
		return ret;
	}
}
namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar(); x = 0;
			for (; !isdigit(ch); ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
LL FastPow(LL bs, int ex = MOD - 2) {
	LL ret = 1;
	for (; ex; (bs *= bs) %= MOD, ex >>= 1)
		if (ex & 1) (ret *= bs) %= MOD;
	return ret;
}

int main() {
	using fast_io::Read;

	Read(n);
	int mxai = 0;
	for (int i = 1; i <= n; i++) {
		Read(A[i]);
		mxai = std::max(mxai, A[i]);
	}
	Read(q);
	for (int i = 0; i < q; i++) {
		Read(qry[i].l), Read(qry[i].r);
		qry[i].id = i;
	}

	for (int i = 2; i <= mxai; i++) {
		if (!flag[i]) P[totp++] = i, minp[i] = i;
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= mxai; j++) {
			flag[pd] = 1, minp[pd] = P[j];
			if (i % P[j] == 0) break;
		}
	}
	prod[0] = 1;
	for (int i = 1; i <= n; i++) prod[i] = (LL)prod[i - 1] * A[i] % MOD;
	bit::init();

	std::sort(qry, qry + q);
	int cur = 0;
	for (int i = 0; i < q; i++) {
		for (; cur < qry[i].r; ) {
			for (int t = A[++cur], p; t > 1; ) {
				if (last[p = minp[t]]) {
					bit::Mult(last[p], FastPow(p - 1));
					bit::Mult(last[p], p);
				}
				bit::Mult(cur, p - 1);
				bit::Mult(cur, FastPow(p));
				last[p] = cur, t /= p;
			}
		}	
		ans[qry[i].id] = bit::Query(qry[i].r) * prod[qry[i].r] % MOD * FastPow(bit::Query(qry[i].l - 1) * prod[qry[i].l - 1] % MOD) % MOD;
	}	

	for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
	return 0;
}