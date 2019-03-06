#include <cstdio>
#include <cctype>
#include <vector>

typedef long long LL;

const int kMaxn = 2e5 + 10, kMaxm = 205, MOD = 998244353;

struct Ask {
	int c, d, id;
};

int n, m, q, S[kMaxn];
LL M[kMaxm][kMaxm], H[kMaxm][kMaxm], dec[kMaxm], sum[kMaxm], ans[kMaxn];
std::vector<Ask> A[kMaxn];

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar(); x = 0;
			for (; !isdigit(ch); ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}
void Mult(int ch);
void Inv(int ch);
LL Solve(int c, int d) {
	return ((M[d][0] - dec[d] + M[d][c] - dec[d]) % MOD + MOD) % MOD;
}

int main() {
	using fast_io::Read;

	Read(n), Read(m), Read(q);
	for (int i = 1; i <= n; i++) Read(S[i]);
	for (int i = 0, bi, ci, di; i < q; i++) {
		Read(bi), Read(ci), Read(di);
		A[bi].push_back((Ask){ci, di, i});
	}

	for (int i = 0; i <= m; i++) M[i][i] = 1, sum[i] = 1;
	for (int i = 1; i <= n; i++) Mult(S[i]);
	for (int i = 1; i <= n; i++) {
		Inv(S[i]);
		for (auto & qry : A[i]) ans[qry.id] = Solve(qry.c, qry.d);
		Mult(S[i]);
	}

	for (int i = 0; i < q; i++) printf("%lld\n", ans[i]);
	return 0;
}

void Mult(int ch) {
	for (int i = 0; i <= m; i++) {
		LL tmp = (M[ch][i] - dec[ch]) % MOD;
		M[ch][i] = sum[i];
		sum[i] = (sum[i] - tmp + M[ch][i]) % MOD;
	}
	dec[ch] = 0;
}

void Inv(int ch) {
	for (int i = 0; i <= m; i++) {
		LL tmp = (M[i][ch] - dec[i]) % MOD;
		(dec[i] += tmp) %= MOD;
		(M[i][ch] += tmp) %= MOD;
	}
	for (int i = 0; i <= m; i++)
		if (i ^ ch) (sum[i] -= sum[ch]) %= MOD;
}
