// NOI2019 - Accepted live
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>

#define forto(arb, are, _) for (int e = arb[_], v = are[e].to; e; \
		v = are[e = are[e].next].to)

typedef long long LL;

const int kMaxn = 1e5 + 10;
const int kMaxt = 1010, kMaxm = 2e5 + 10;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

struct Edge {
	int to, lev, arr, next;
} Er[kMaxm], E[kMaxm];

int n, m, A, B, C, tote, toter;
int backr[kMaxn], back[kMaxn];

template <typename T>
inline void UMin(T & x, T y) {
	if (x > y) x = y;
}
inline void AddEdge(int u, int v, int l, int a) {
	Er[++toter] = (Edge){u, l, a, backr[v]}, backr[v] = toter;
	E[++tote] = (Edge){v, l, a, back[u]}, back[u] = tote;
}
namespace solver1 {
	void Solve();
}
namespace solver2 {
	void Solve();
}

int main() {
#ifndef LOCAL
	freopen("route.in", "r", stdin);
	freopen("route.out", "w", stdout);
#endif
	scanf("%d%d%d%d%d", &n, &m, &A, &B, &C);
	int f1 = 1;
	for (int i = 0, x, y, p, q; i < m; i++) {
		scanf("%d%d%d%d", &x, &y, &p, &q);
		AddEdge(x, y, p, q);
		f1 &= x < y;
	}

	if (f1 && n <= 2000) solver1::Solve();
	else solver2::Solve();

#ifndef LOCAL
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}

namespace solver1 {
	const int kMaxn = 2010;

	LL DP[kMaxn][kMaxt];

	void Solve() {
		memset(DP, 0x3f, sizeof DP);
		DP[1][0] = C;
		for (int i = 1; i <= 1000; i++) {
			DP[1][i] = DP[1][i - 1] + 2ll * A * i - A + B;
		}
		for (int i = 2; i <= n; i++) {
			forto(backr, Er, i) {
				if (DP[v][E[e].lev] + (i == n ? 0 : C) < DP[i][E[e].arr]) {
					DP[i][E[e].arr] = DP[v][E[e].lev] + (i == n ? 0 : C);
					for (int j = E[e].arr + 1; j <= 1000; j++) {
						UMin(DP[i][j],
							DP[i][j - 1] + 2ll * A * (j - E[e].arr) - A + B);
					}
				}
			//	printf(" %d->%d, leave at %d, arrive at %d, cost %lld -> %lld\n",
			//			v, i, E[e].lev, E[e].arr, DP[v][E[e].lev], DP[i][E[e].arr]);
			}
		}
		LL ans = kInf64;
		forto(backr, Er, n) {
			UMin(ans, DP[n][E[e].arr] + E[e].arr);
		}
		printf("%lld\n", ans);
	}
}

#define fir first
#define sec second

namespace solver2 {
	typedef std::set<int> SKey;
//	typedef std::pair<int, int> Pii;

	SKey key[kMaxn];
	std::map<int, LL> DP[kMaxn];
	std::queue<int> que;
	int inq[kMaxn];

	inline LL Calc(LL x) {
	   return A * x * x + B * x;
	}
	inline LL & Dp(int u, int t) {
		if (DP[u].count(t)) return DP[u][t];
		else {
			return DP[u][t] = kInf64;
		}
	}
	void Solve() {
		for (int i = 1; i <= n; i++) {
			forto(back, E, i) {
			//	printf(" %d insert %d, %d insert %d\n",
			//			v, E[e].arr, i, E[e].lev);
				key[v].insert(E[e].arr), key[i].insert(E[e].lev);
			}
		}
		for (SKey::iterator it = key[1].begin();
			it != key[1].end(); ++it) {
			Dp(1, *it) = Calc(*it) + C;
		}
		que.push(1), inq[1] = 1;
		for (int u; !que.empty(); ) {
			u = que.front(), que.pop();
			LL now;
			forto(back, E, u) {
			//	printf(" u %d, E[e].lev = %d\n", u, E[e].lev);
				if ((now = Dp(u, E[e].lev)) == kInf64) continue;
			//	printf(" DP[%d][%d] = %lld\n", u, E[e].lev, now);
				if (Dp(v, E[e].arr) > now + (v == n ? 0 : C)) {
					LL nxt = Dp(v, E[e].arr) = now + (v == n ? 0 : C);
					if (!inq[v]) {
						que.push(v);
						inq[v] = 1;
					}
					SKey::iterator it = key[v].lower_bound(E[e].arr);
					for (++it; it != key[v].end(); ++it) {
						if (Dp(v, *it) >
							nxt + Calc(*it - E[e].arr)) {
						//	printf(" DP[%d][%d] = %lld\n",
						//			v, *it, nxt + Calc(*it - E[e].arr));
							Dp(v, *it) = nxt + Calc(*it - E[e].arr);
							if (!inq[v]) {
								que.push(v);
								inq[v] = 1;
							}
						}
					}
				}
			}
			inq[u] = 0;
		}
		LL ans = kInf64;
		for (SKey::iterator it = key[n].begin();
			it != key[n].end(); ++it) {
			UMin(ans, Dp(n, *it) + *it);
		}
		printf("%lld\n", ans);
	}
}
