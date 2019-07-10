#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

#define forto(_) for (int e = back[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 100, kMaxv = 2e5, kInf = 0x3f3f3f3f;

struct Edge {
	int to, capt, next;
} E[kMaxv << 1];

int n, m, k, tote = 1, moon, src, trg, size;
int fa[kMaxn], H[kMaxn], R[kMaxn], S[kMaxn][kMaxn];
int back[kMaxv], D[kMaxv], cur[kMaxv], id[kMaxn][700];

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, 0, back[v]}, back[v] = tote;
}
int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
void Merge(int x, int y);
int MaxFlow();

int main() {
	scanf("%d%d%d", &n, &m, &k);
	moon = n + 1;
	for (int i = 0; i <= moon; i++) fa[i] = i;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", H + i, R + i);
		for (int j = 0; j < R[i]; j++) {
			scanf("%d", S[i] + j);
			if (S[i][j] == -1) S[i][j] = moon;
			if (j) Merge(S[i][j - 1], S[i][j]);
		}
	}

	if (Find(0) != Find(moon)) {
		puts("0");
		return 0;
	}

	src = 0, trg = size = 1;
	for (int i = 1; i <= n; i++) id[0][i] = ++size;
	id[0][0] = src, id[0][moon] = trg;
	for (int t = 1, tot = 0; ; t++) {
	//	printf(" t = %d\n", t);
		for (int i = 1; i <= n; i++) {
			id[t][i] = ++size;
			AddEdge(id[t - 1][i], id[t][i], kInf);
		}
	//	puts("  CHECK point 1");
		id[t][0] = src, id[t][moon] = trg;
		for (int i = 0, prv, nxt; i < m; i++) {
			prv = (t - 1) % R[i], nxt = t % R[i];
		//	printf("   Add (%d, %d) -> (%d, %d), capt %d\n", S[i][cur], t - 1, S[i][cur + 1], t, H[i]);
			AddEdge(id[t - 1][S[i][prv]], id[t][S[i][nxt]], H[i]);
		}
	//	puts("  CHECK point 2");
		tot += MaxFlow();
	//	puts("  CHECK point 3");
		if (tot >= k) {
			printf("%d\n", t);
			return 0;
		}
	}

	return 0;
}

void Merge(int x, int y) {
	x = Find(x), y = Find(y);
	if (x != y) fa[x] = y;
}

bool Build() {
	std::queue<int> que;
	memset(D, 0, sizeof D);
	que.push(src), D[src] = 1;
	for (int u; !que.empty(); ) {
		u = que.front(), que.pop();
		forto(u) {
			if (E[e].capt <= 0 || D[v]) continue;
			D[v] = D[u] + 1;
			que.push(v);
		}
	}
//	printf("   D[trg] = %d\n", D[trg]);
	return D[trg];
}

int Dinic(int u, int flow) {
	if (u == trg) return flow;
	int rem = flow, delta;
	for (int & e = cur[u], v = E[e].to; e && rem;
		   v = E[e = E[e].next].to)	{
		if (E[e].capt <= 0 || D[v] != D[u] + 1) continue;
		delta = Dinic(v, std::min(rem, E[e].capt));
		E[e].capt -= delta, E[e ^ 1].capt += delta;
		rem -= delta;
	}
	return flow - rem;
}

int MaxFlow() {
	int sum = 0;
	while (Build()) {
		for (int i = 0; i <= size; i++) cur[i] = back[i];
		sum += Dinic(src, kInf);
	}
	return sum;
}
