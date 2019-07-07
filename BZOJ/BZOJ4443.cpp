#include <algorithm>
#include <cstdio>
#include <cstring>

#define forto(_) for (int e = back[_], v = E[e].to; e; v = E[e = E[e].next].to)

const int kMaxn = 255;

int n, m, k, totn;
int A[kMaxn][kMaxn], num[kMaxn * kMaxn];

bool Check(int);

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &A[i][j]);
			num[totn++] = A[i][j];
		}
	}

	std::sort(num, num + totn);
	totn = std::unique(num, num + totn) - num;
	int lb = 0, ub = totn;
	for (int mid; ub - lb > 1; ) {
		mid = lb + ub >> 1;
		if (Check(num[mid - 1])) ub = mid;
		else lb = mid;
	}

	printf("%d\n", num[ub - 1]);
	return 0;
}

struct Edge {
	int to, next;
} E[kMaxn * kMaxn];

int tote, vis[kMaxn], back[kMaxn], match[kMaxn];

bool Dfs(int u) {
	forto(u) {
		if (!vis[v]) {
			vis[v] = 1;
			if (match[v] == -1 || Dfs(match[v])) {
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, back[u]}, back[u] = tote;
}

bool Check(int val) {
	tote = 0;
	memset(back, 0, sizeof back);
	memset(match, 0xff, sizeof match);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (A[i][j] <= val) AddEdge(i, j);
		}
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		memset(vis, 0, sizeof vis);
		if (Dfs(i)) ++cnt;
	}
	return cnt >= n - k + 1;
}
