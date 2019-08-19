#include <cstdio>
#include <vector>

const int kMaxm = 55;

int n, m;
int G[kMaxm][kMaxm], match[kMaxm];
int ans[kMaxm], vis[kMaxm], lock[kMaxm];
std::vector<int> ipos[26], opos[26];
char in[kMaxm], out[kMaxm];

bool Dfs(int u);

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			match[i] = -1, lock[i] = 0;
			for (int j = i; j <= m; j++) G[i][j] = G[j][i] = 0;
		} int unmatch = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s%s", in, out);
			for (int j = 0; j < 26; j++)
				ipos[j].clear(), opos[j].clear();
			for (int j = 0; j < m; j++) {
				ipos[in[j] - 'a'].push_back(j + 1);
				opos[out[j] - 'a'].push_back(j + 1);
			}
			for (int j = 0; j < 26; j++) {
				if (ipos[j].size() != opos[j].size()) {
					unmatch = 1; break;
				}
				if ((int)ipos[j].size() == 1) {
					if (match[opos[j][0]] != -1 &&
						match[opos[j][0]] != ipos[j][0]) {
						unmatch = 1; break;
					} int f = 0;
					for (int k = 1; k <= m; k++) {
						if (G[ipos[j][0]][k]) {
							f = 1; break;
						}
					} if (f && !G[ipos[j][0]][opos[j][0]]) {
						unmatch = 1; break;
					} match[opos[j][0]] = ipos[j][0];
				   	ans[ipos[j][0]] = opos[j][0];
					lock[ipos[j][0]] = 1;
					continue;
				}
				for (auto ip : ipos[j]) {
					if (lock[ip]) {
						int f = 0;
						for (auto op : opos[j]) {
							if (op == ans[ip]) { f = 1; break; }
						} if (!f) { unmatch = 1; break; }
						continue;
					} for (auto op : opos[j]) ++G[ip][op];
				}
			}
		} if (unmatch) { puts("-1"); continue; }
		for (int i = m; i; i--) {
			if (lock[i]) continue;
			std::fill(vis, vis + m + 1, 0);
			if (!Dfs(i)) { unmatch = 1; break; }
		} if (unmatch) { puts("-1"); continue; }
		for (int i = 1; i <= m; i++)
			printf("%d%c", ans[i], i == m ? '\n' : ' ');
	} return 0;
}

bool Dfs(int u) {
	if (lock[u]) return false;
	for (int v = 1; v <= m; v++) {
		if (G[u][v] != n || vis[v]) continue;
		vis[v] = 1;
		if (match[v] == -1 || Dfs(match[v])) {
			match[v] = u, ans[u] = v; return true;
		}
	} return false;
}
