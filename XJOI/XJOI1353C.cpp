#include <algorithm>
#include <cassert>
#include <cstdio>

typedef long long LL;
typedef double Db;

const int kMaxn = 1e5 + 5, kInf = 0x3f3f3f3f;

int n, q;
int A[kMaxn];
char O[5];

namespace solver1 { void Solve(); }
namespace solver2 { void Solve(); }
inline LL X2(LL x) { return x * x; }

int main() {
//	srand(19260817);
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) scanf("%d", A + i);
	solver2::Solve();
	return 0;
}

namespace solver1 {
	void Solve() {
		for (int l, r; q--; ) {
			scanf("%s%d%d", O, &l, &r);
			if (O[0] == 'q') {
				if (l == r) { puts("0.000000"); continue; }
				LL s = 0, s2 = 0;
				int len = r - l + 1, L = 1e9, R = 0;
				for (int i = l; i <= r; ++i) {
					s += A[i], s2 += X2(A[i]), L = std::min(L, A[i]), R = std::max(R, A[i]);
				}
				LL del = std::max(X2(len * L - s), X2(len * R - s));
				printf("%.6Lf\n", (len * s2 - X2(s) - del / Db(len - 1)) / (Db)X2(len));
			} else std::reverse(A + l, A + r + 1);
		}
	}
}

namespace solver2 {
	struct Node {
		int rkey, val, mn, mx, ch[2], rev, sz;
		LL s, s2;
		Node() {}
		Node(int _v) : rkey(rand()) { s = val = mn = mx = _v, rev = ch[0] = ch[1] = 0, sz = 1, s2 = X2(_v); }
	} T[kMaxn];
	int rt;
#define LSON(_) T[_].ch[0]
#define RSON(_) T[_].ch[1]
	inline void Revrs(int u) { std::swap(LSON(u), RSON(u)), T[u].rev ^= 1; }
	inline void Maintn(int u) {
		T[u].mn = std::min({T[u].val, T[LSON(u)].mn, T[RSON(u)].mn});
		T[u].mx = std::max({T[u].val, T[LSON(u)].mx, T[RSON(u)].mx});
		T[u].sz = 1 + T[LSON(u)].sz + T[RSON(u)].sz;
		T[u].s = T[u].val + T[LSON(u)].s + T[RSON(u)].s;
		T[u].s2 = X2(T[u].val) + T[LSON(u)].s2 + T[RSON(u)].s2;
	}
	void PushDw(int u) {
		if (T[u].rev) {
			if (LSON(u)) Revrs(LSON(u));
			if (RSON(u)) Revrs(RSON(u));
			T[u].rev = 0;
		}
	}
	int Merge(int u, int v) {
		if (!u || !v) return u + v;
		PushDw(u), PushDw(v);
		if (T[u].rkey < T[v].rkey) {
			RSON(u) = Merge(RSON(u), v); Maintn(u);
			return u;
		} else {
			LSON(v) = Merge(u, LSON(v)); Maintn(v);
			return v;
		}
	}
	void Split(int u, int k, int & r1, int & r2) {
		if (!u) return (void)(r1 = r2 = 0);
		PushDw(u);
		if (T[LSON(u)].sz >= k) Split(LSON(u), k, r1, LSON(r2 = u));
		else Split(RSON(u), k - 1 - T[LSON(u)].sz, RSON(r1 = u), r2);
		Maintn(u);
	}
	void Out() {
		for (int i = 1; i <= n; ++i) printf(" node %d, val %d, ls %d, rs %d, s %lld, s2 %lld\n",
				i, T[i].val, LSON(i), RSON(i), T[i].s, T[i].s2);
		puts("===============================");
	}
	void Solve() {
		T[0].mx = -(T[0].mn = kInf);
		for (int i = 1; i <= n; ++i) { T[i] = Node(A[i]), rt = Merge(rt, i); }
		for (int l, r, r1, r2, r3; q--; ) {
			scanf("%s%d%d", O, &l, &r);
			if (O[0] == 'q' && l == r) { puts("0.000000"); continue; }
//			Out();
			Split(rt, r, r1, r3); Split(r1, l - 1, r1, r2);
//			Out(); printf(" r1 %d, r2 %d, r3 %d\n", r1, r2, r3);
			if (O[0] == 'q') {
				int len = T[r2].sz, L = T[r2].mn, R = T[r2].mx;
//				if (len != r - l + 1) printf(" len = %d, l = %d, r = %d\n", len, l, r);
				assert(len == r - l + 1);
				LL s = T[r2].s, s2 = T[r2].s2, del = std::max(X2(len * L - s), X2(len * R - s));
//				printf("%.6Lf\n", Db((len * s2 - X2(s) - del / Db(len - 1)) / (__float128)X2(len)));
				printf("%.6lf\n", Db(std::min((s2 - LL(R) * R) * (r - l) - LL(s - R) * (s - R),
								(s2 - LL(L) * L) * (r - l) - LL(s - L) * (s - L)) / 
							__float128(LL(r - l + 1) * (r - l)))); 
			} else Revrs(r2);
			rt = Merge(r1, Merge(r2, r3));
		}
	}
}
