#include <algorithm>
#include <cstdio>

const int kMaxn = 1e5 + 5, kMod = 1e9 + 7;

typedef long long LL;
typedef int Arr[kMaxn];

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline int Sub(int a, int b) { return (a -= b) < 0 ? a + kMod : a; }
inline int Mul(int a, int b) { return 1ll * a * b % kMod; }
inline void Upa(int & a, int b) { a = Add(a, b); }

int t;

namespace solver2 { void Solve(); }

int main() { scanf("%d", &t); solver2::Solve(); return 0; }

/* namespace solver1 {
	inline int Calc(int x) { return 1ll * x * (x + 1) / 2 % kMod; }
	int Sum(int n, int m) {
		if (n > m) std::swap(n, m);
		int res = 0;
		for (int i = 1, j; i <= n; i = j + 1) {
			j = std::min(n / (n / i), m / (m / i));
//			printf(" n %d, [%d, %d], mu2: %d - %d\n", n, i, j, mu2[j], mu2[i]);
			Upa(res, Mul(Sub(mu2[j], mu2[i - 1]), Mul(Calc(n / i), Calc(m / i))));
		} return res;
	}
	void Solve() {
		int ans = 0;
		for (int i = 1, j; i <= a && i <= n; i = j + 1) {
			j = std::min(n / (n / i), m / (m / i));
//			printf(" a %d, [%d, %d], S(%d, %d) = %d\n", a, i, j, n / i, m / j, Sum(n / i, m / i));
			Upa(ans, Mul(LL(j - i + 1) * (i + j) / 2 % kMod, Sum(n / i, m / i)));
		} printf("%d\n", ans);
	}
} */

namespace solver2 {
	struct Qry {
		int n, m, a, id;
		bool operator<(const Qry & q) const { return a < q.a; }
	} Q[kMaxn];
	Arr ans, np, P, mu;
	int cntp, mxn;

	namespace bit {
		int T[kMaxn];
		void Add(int p, int v) {
			for (; p <= mxn; p += p & -p) Upa(T[p], v);
		}
		int Q(int p) {
			int r = 0;
			for (; p; p &= p - 1) Upa(r, T[p]);
			return r;
		}
		inline int Query(int l, int r) { return Sub(Q(r), Q(l - 1)); }
	}
	inline int Sum(int x) { return 1ll * x * (x + 1) / 2 % kMod; }

	void Solve() {
		for (int i = 0; i < t; ++i) {
			scanf("%d%d%d", &Q[i].n, &Q[i].m, &Q[i].a);
			if (Q[i].n > Q[i].m) std::swap(Q[i].n, Q[i].m);
			Q[i].id = i, mxn = std::max(mxn, Q[i].n);
		} std::sort(Q, Q + t), mu[1] = 1;
		for (int i = 2, neg1 = Sub(0, 1); i <= mxn; ++i) {
			if (!np[i]) { P[cntp++] = i, mu[i] = neg1; }
			for (int j = 0, d; j < cntp && (d = i * P[j]) <= mxn; ++j) {
				np[d] = 1, mu[d] = Sub(0, mu[i]);
				if (!(i % P[j])) { mu[d] = 0; break; }
			}
		}
		for (int ca = 1, i = 0; ca <= Q[t - 1].a; ++ca) {
			for (int j = ca; j <= mxn; j += ca) bit::Add(j, Mul(mu[j / ca], Mul(j / ca, j)));
			for (int n, m; i < t && Q[i].a == ca; ++i) {
				n = Q[i].n, m = Q[i].m;
				int & res = ans[Q[i].id];
				for (int j = 1, k; j <= n; j = k + 1) {
					k = std::min(n / (n / j), m / (m / j));
					Upa(res, Mul(bit::Query(j, k), Mul(Sum(n / j), Sum(m / j))));
				}
			}
		}
		for (int i = 0; i < t; ++i) printf("%d\n", ans[i]);
	}
}
