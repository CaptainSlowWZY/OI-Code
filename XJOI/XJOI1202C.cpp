#include <algorithm>
#include <cstdio>
#include <vector>

#define forto(_) for (int e = back[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 505;

typedef int IAr[kMaxn];

struct Edge {
	int to, cost, next;
} E[kMaxn << 1];

int n, D, tote;
IAr back, cnt;

inline void AddEdge(int u, int v, int c) {
	E[++tote] = (Edge){v, c, back[u]}, back[u] = tote;
	E[++tote] = (Edge){u, c, back[v]}, back[v] = tote;
}
int Dfs(int, int);

int main() {
	scanf("%d%d", &n, &D);
	for (int i = 1, x, y, z; i < n; i++) {
		scanf("%d%d%d", &x, &y, &z);
		AddEdge(x, y, z);
	}

	Dfs(1, 0);

	printf("%d\n", cnt[1] + 1);
	return 0;
}

int Dfs(int u, int fa) {
	int len;
	std::vector<int> link;
	forto(u) {
		if (v == fa) continue;
		len = E[e].cost + Dfs(v, u);	
		if (len > D) ++cnt[v];
		else link.push_back(len);
		cnt[u] += cnt[v];
	}
	if (link.empty()) return 0;
	std::sort(link.begin(), link.end());
	int i;
	for (i = link.size() - 1; i > 0; i--) {
		if (link[i] + link[i - 1] > D) ++cnt[u];
		else break;
	}
	return link[i];
}
