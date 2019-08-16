#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define fir first
#define sec second
#define FORTO(_) for (int e = lst[_], v = B[e]; ~e; \
		v = B[e = nxt[e]])

typedef std::pair<int, int> Pii;

const int kMaxn = 1e5 + 5, kMaxm = 2e5 + 5, kInf = 0x3f3f3f3f;

int n, m, K, P;
int lst[kMaxn], dis1[kMaxn], disn[kMaxn], tprk[kMaxn], ideg[kMaxn];
int DP[kMaxn][55], id[kMaxn];
int A[kMaxm], B[kMaxm], C[kMaxm], nxt[kMaxm];

inline void Add(int & x, int y) {
	if ((x += y) >= P) x -= P;
}
void Solve();

int main() {
	int t;
	for (scanf("%d", &t); t--; ) Solve();
	return 0;
}

void Dijkstra(int s, int dis[]) {
	std::fill(dis, dis + n + 1, kInf);
	std::priority_queue<Pii, std::vector<Pii>,
		std::greater<Pii> > hap;
	dis[s] = 0, hap.push(Pii(0, s));
	while (!hap.empty()) {
		Pii cur = hap.top(); hap.pop();
		if (dis[cur.sec] < cur.fir) continue;
		FORTO(cur.sec) {
			if (cur.fir + C[e] < dis[v]) {
				dis[v] = cur.fir + C[e];
				hap.push(Pii(dis[v], v));
			}
		}
	}
}

void Topo() {
	std::fill(ideg, ideg + n + 1, 0);
	for (int i = 0; i < m; i++)
		if (!C[i]) ++ideg[B[i]];
	std::queue<int> que;
	for (int i = 1; i <= n; i++)
		if (!ideg[i]) que.push(i);
	int rank = 0;
	for (int u; !que.empty(); ) {
		tprk[u = que.front()] = ++rank; que.pop();
		FORTO(u) {
			if (C[e]) continue;
			if (!(--ideg[v])) que.push(v);
		}
	}
}

inline bool CmpId(int a, int b) {
	return dis1[a] == dis1[b] ? tprk[a] < tprk[b] :
		dis1[a] < dis1[b];
}

void Solve() {
	scanf("%d%d%d%d", &n, &m, &K, &P);
	std::fill(lst, lst + n + 1, -1);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", A + i, B + i, C + i);
		nxt[i] = lst[A[i]], lst[A[i]] = i;
	} Dijkstra(1, dis1); Topo();
//	reverse graph
	std::fill(lst, lst + n + 1, -1);
	for (int i = 0; i < m; i++) {
		std::swap(A[i], B[i]);
		nxt[i] = lst[A[i]], lst[A[i]] = i;
	} Dijkstra(n, disn);
//	check for inf solution
	for (int i = 1; i <= n; i++) {
		id[i] = i;
		if (!ideg[i]) continue;
		if (dis1[i] + disn[i] <= dis1[n] + K) {
			puts("-1"); return;
		}
	} std::sort(id + 1, id + n + 1, CmpId);
//	reverse graph back
	std::fill(lst, lst + n + 1, -1);
	for (int i = 0; i < m; i++) {
		std::swap(A[i], B[i]);
		nxt[i] = lst[A[i]], lst[A[i]] = i;
	}
//	calc ans
	memset(DP, 0, sizeof DP);
	DP[1][0] = 1;
	for (int i = 0; i <= K; i++) {
		for (int j = 1, u; j <= n; j++) {
			FORTO(u = id[j]) {
				if (dis1[u] + i + C[e] > dis1[v] + K)
					continue;
				Add(DP[v][dis1[u] + i + C[e] - dis1[v]],
						DP[u][i]);
			}
		}
	} int ans = 0;
	for (int i = 0; i <= K; i++) Add(ans, DP[n][i]);
	(ans += P) %= P;
	printf("%d\n", ans);
}
