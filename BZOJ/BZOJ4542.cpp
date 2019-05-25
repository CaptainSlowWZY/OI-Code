// HNOI2016
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <map>

typedef long long LL;

const int kMaxm = 1e5 + 10;

int P, n, m;
char S[kMaxm];

namespace moa {
	void Solve();
}
namespace spc {
	void Solve();
}

int main() {
	scanf("%d%s%d", &P, S + 1, &m);
	if (P == 2 || P == 5) spc::Solve();
	else moa::Solve();
	return 0;
}

namespace spc {
	int tot[kMaxm];
	LL sum[kMaxm];
	void Solve() {
		n = 1;
		for (int f; S[n]; n++) {
			f = (S[n] ^ '0') % P == 0;
			tot[n] = tot[n - 1] + f;
			sum[n] = sum[n - 1] + 1ll * f * n;
		}
		for (int i = 0, l, r; i < m; i++) {
			scanf("%d%d", &l, &r);
			printf("%lld\n", 
				sum[r] - sum[l - 1] - LL(tot[r] - tot[l - 1]) * (l - 1));
		}
	}
}

namespace moa {
	int bl[kMaxm], cnt[kMaxm];

	struct Query {
		int l, r, id;
		bool operator<(const Query & q) const {
			return bl[l] == bl[q.l] ? 
				(bl[l] & 1 ? r < q.r : r > q.r) : l < q.l;
		}
	} Q[kMaxm];

	LL curans;
	LL R[kMaxm], R1[kMaxm], ans[kMaxm];

	inline void Invalid(int p) { curans -= --cnt[p]; }
	inline void Valid(int p) { curans += cnt[p]++; }
	LL FastPow(int mod, LL bs) {
		int ex = mod - 2;
		LL res = 1;
		for (; ex; (bs *= bs) %= mod, ex >>= 1) {
			if (ex & 1) (res *= bs) %= mod;
		}
		return res;
	}
	void Solve() {
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &Q[i].l, &Q[i].r);
			--Q[i].l, Q[i].id = i;
		}

		n = 1;
		for (; S[n]; n++) {
			R[n] = (R[n - 1] * 10 + (S[n] ^ '0')) % P;
		}
		LL pw = 1, per = FastPow(P, 10);
		for (int i = 1; S[i]; i++) {
			(pw *= per) %= P;
			(R[i] *= pw) %= P;
			R1[i] = R[i];
		}
		std::sort(R1, R1 + n);
		int sz = std::unique(R1, R1 + n) - R1;
		for (int i = 0; i < n; i++) {
			R[i] = std::lower_bound(R1, R1 + sz, R[i]) - R1;
		}
		int Unsz = sqrt(n + 0.5);
		bl[0] = 1;
		for (int i = 1; i < n; i++) {
			bl[i] = (i - 1) / Unsz + 1;
		}

		std::sort(Q, Q + m);
		int l = -1, r = -1;
		for (int i = 0; i < m; i++) {
			for (; l < Q[i].l; ++l) {
				if (~l) Invalid(R[l]);
			}
			for (; l > Q[i].l; --l) {
				if (l) Valid(R[l - 1]);
			}
			for (; r > Q[i].r; ) Invalid(R[r--]);
			for (; r < Q[i].r; ) Valid(R[++r]);
			ans[Q[i].id] = curans;
		}

		for (int i = 0; i < m; i++) printf("%lld\n", ans[i]);
	}
}
