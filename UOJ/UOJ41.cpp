#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>

#define fi first
#define se second
#define pb push_back

typedef std::pair<int, int> Pii;

const int kMaxn = 205, kMaxm = 405;

int n, m;
int rk[kMaxn][kMaxn], boy[kMaxn], ans[kMaxn];
std::vector<int>::iterator it[kMaxn];
std::vector<int> row[kMaxn];
std::queue<int> Q;

bool Props(int u);

int main() {
	int t; scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			row[i].clear(); boy[i] = -1;
		}
		for (int i = 1; i <= n; ++i) {
			for (int aij, j = 1; j <= m; ++j) {
				scanf("%d", &aij);
				if (!aij) continue;
				rk[aij][i] = m - j, row[i].pb(aij);
			}
		}	
		for (int i = 1; i <= n; ++i) { it[i] = row[i].begin(), Q.push(i); }
		for (; !Q.empty(); Q.pop()) if (!Props(Q.front())) Q.push(Q.front());
		for (int i = 1; i <= n; ++i) ans[boy[i]] = i;
		for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}

bool Props(int u) {
	int v = *it[u]++;
	if (boy[v] == -1 || rk[v][boy[v]] > rk[v][u]) {
		if (~boy[v]) Q.push(boy[v]);
		boy[v] = u; return true;
	} return false;
}
