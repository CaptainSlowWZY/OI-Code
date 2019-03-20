#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>

#define pb push_back
#define fir first
#define sec second
#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)
#define forback(_) for (int _ = T; _ ^ S; _ = pre[_])

typedef long long LL;

const int kMaxn = 85, kMaxe = 2e4;
const LL kInf64 = 1e15 + 5;

typedef std::pair<int, int> Pii;
typedef int IArn[kMaxn];
typedef int IArv[kMaxn << 2];

struct Edge {
	int to, capt;
	LL cost;
	int next;
} E[kMaxe << 1];

int n, m, tote, S, T;
IArn X, Y, L, R, U, D;
IArv last, pre, pree;
LL V[kMaxn], dist[kMaxn << 2];
std::vector<Pii> con[4];
char IN[5];

inline void AddEdge(int u, int v, int cap, LL cst) {
	E[++tote] = (Edge){v, cap, cst, last[u]}, last[u] = tote;
	assert(E[tote].cost == cst);
	E[++tote] = (Edge){u, 0, -cst, last[v]}, last[v] = tote;
}
template <typename T>
void Umin(T & x, T y) {
	x > y ? x = y : 0;
}
template <typename T>
void Umax(T & x, T y) {
	x < y ? x = y : 0;
}
LL Mcf(int);

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%lld", X + i, Y + i, V + i);
	}
	scanf("%d", &m);
	for (int i = 0, ai, bi; i < m; i++) {
		scanf("%s%d%d", IN, &ai, &bi);
		switch (IN[0]) {
			case 'L' :
				con[0].pb(Pii(ai, bi));
				break;
			case 'R' :
				con[1].pb(Pii(ai, bi));
				break;
			case 'D' :
				con[2].pb(Pii(ai, bi));
				break;
			case 'U' :
				con[3].pb(Pii(ai, bi));
				break;
		}
	}

	for (int i = 0; i <= n; i++) {
		L[i] = D[i] = 1;
	}
	for (auto & p : con[0]) {
		Umax(L[p.sec + 1], p.fir + 1);
	}
	for (auto & p : con[2]) {
		Umax(D[p.sec + 1], p.fir + 1);
	}
	for (int i = 1; i <= n; i++) {
		Umax(L[i], L[i - 1]);
		Umax(D[i], D[i - 1]);
	}

	LL ans = 0;
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= k; i++) {
			R[i] = U[i] = 100;
		}
		for (auto & p : con[1]) {
			if (k <= p.sec) continue;
			Umin(R[k - p.sec], p.fir - 1);
		}
		for (auto & p : con[3]) {
			if (k <= p.sec) continue;
			Umin(U[k - p.sec], p.fir - 1);
		}
		for (int i = k - 1; i > 0; i--) {
			Umin(R[i], R[i + 1]);
			Umin(U[i], U[i + 1]);
		}


		tote = 1;
		memset(last, 0, sizeof last);
		T = (S = k + n + n + k + 1) + 1;
		for (int i = 1; i <= k; i++) {
			AddEdge(S, i, 1, 0);
			AddEdge(k + n + n + i, T, 1, 0);
			for (int j = 1; j <= n; j++) {
				if (L[i] <= X[j] && X[j] <= R[i]) {
					AddEdge(i, k + j, 1, 0);
				}
				if (D[i] <= Y[j] && Y[j] <= U[i]) {
					AddEdge(k + n + j, k + n + n + i, 1, 0);
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			AddEdge(k + i, k + n + i, 1, kInf64 - V[i]);
		}

		ans = std::max(ans, Mcf(k));
	}

	printf("%lld\n", ans);
	return 0;
}

bool Spfa() {
	static std::queue<int> que;
	static int inque[kMaxn << 2];

	memset(pre, 0xff, sizeof pre);
	memset(dist, 0x7f, sizeof dist);

	for (dist[S] = 0, que.push(S), inque[S] = 1; !que.empty(); ) {
		int u = que.front(); que.pop();
		forto(u) {
			if (E[e].capt > 0 && dist[v] > dist[u] + E[e].cost) {
				dist[v] = dist[u] + E[e].cost;
				pre[v] = u, pree[v] = e;
				if (!inque[v]) {
					que.push(v), inque[v] = 1;
				}
			}
		}
		inque[u] = 0;
	}
	return ~pre[T];
}

LL Mcf(int maxf) {
	LL tot = 0, sumf = 0;
	while (Spfa()) {
		int flow = 100000;
		forback(u) {
			flow = std::min(flow, E[pree[u]].capt);
		}
		tot += 1ll * flow * dist[T], sumf += flow;
		forback(u) {
			E[pree[u]].capt -= flow;
			E[pree[u] ^ 1].capt += flow;
		}
	}
	return sumf >= maxf ? maxf * kInf64 - tot : 0;
}
