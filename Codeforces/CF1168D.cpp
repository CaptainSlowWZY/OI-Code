#include <algorithm>
#include <cstdio>
#include <cctype>
#include <vector>

const int kMaxn = 150010;

int n, q, imp, totvld;
int H[kMaxn], C[kMaxn], id[kMaxn], max[kMaxn][27], cnt[kMaxn][27];
int invld[kMaxn], fa[kMaxn];
std::vector<int> T[kMaxn], son[kMaxn];

inline int Ind(char ch) { return isalpha(ch) ? ch - 'a' : 26; }
void Dfs(int);
void Init(int);
void Modify(int, int);

int main() {
	scanf("%d%d", &n, &q);
	char IN[10];
	for (int i = 2, fa; i <= n; i++) {
		scanf("%d%s", &fa, IN);
		T[fa].push_back(i);
		C[i] = Ind(IN[0]);
	}

	Dfs(1);
	for (int i = 2; i <= n; i++) {
		++cnt[id[i]][C[i]];
	}
	Init(1);

	for (int v, ch; q--; ) {
		scanf("%d%s", &v, IN);
		ch = Ind(IN[0]);
		Modify(v, ch);
		if (totvld || imp) puts("Fou");
		else {
			int sum = 0;
			for (int i = 0; i < 26; i++) sum += max[1][i];
			int ans = 0;
			for (int i = 0; i < 26; i++) {
				ans += (i + 1) * (H[1] - sum + max[1][i]);
			}
			printf("Shi %d\n", ans);
		}
	}

	return 0;
}

void Dfs(int u) {
	for (auto v : T[u]) {
		Dfs(v);
		if (!H[u]) H[u] = H[v] + 1;
		else if (H[u] != H[v] + 1) imp = 1;
		id[u] = id[v];
	}
	if (u == 1 || T[u].size() != 1) {
		id[u] = u;
		for (auto v : T[u]) {
			fa[id[v]] = u;
			son[u].push_back(id[v]);
		}
	}
}

void Init(int u) {
	for (auto v : son[u]) {
		Init(v);
		for (int i = 0; i < 26; i++) {
			max[u][i] = std::max(max[u][i], max[v][i] + cnt[v][i]);
		}
	}
	int sum = 0;
	for (int i = 0; i < 26; i++) sum += max[u][i];
	if (sum > H[u]) {
		invld[u] = 1;
		++totvld;
	}
}

void Modify(int u, int ch) {
	--cnt[id[u]][C[u]];
	++cnt[id[u]][ch];
	for (int f = fa[id[u]], sum; f; f = fa[f]) {
		totvld -= invld[f];
		max[f][C[u]] = max[f][ch] = invld[f] = 0;
		for (auto v : son[f]) {
			max[f][C[u]] = std::max(max[f][C[u]], 
									max[v][C[u]] + cnt[v][C[u]]);
			max[f][ch] = std::max(max[f][ch], max[v][ch] + cnt[v][ch]);
		}
		for (int i = sum = 0; i < 26; i++) sum += max[f][i];
		if (sum > H[f]) invld[f] = 1;
		totvld += invld[f];
	}
	C[u] = ch;
}
