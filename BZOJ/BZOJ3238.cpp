// BZOJ 3238
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int LEN = 5e5 + 5;

char S[LEN];
long long ans, lens;

namespace SAM {
	void extend(int ch);
	void solve();
}

int main() {
	scanf("%s", S);
	lens = strlen(S);
	for (int i = lens - 1; i >= 0; i--) SAM::extend(S[i] - 'a');
	SAM::solve();
	printf("%lld\n", ans);
	return 0;
}

namespace SAM {
	const int ARSZ = LEN << 1;
	int size = 1, last = 1, A[ARSZ][26], max[ARSZ], par[ARSZ], sz[ARSZ];
	std::vector<int> G[ARSZ];

	void extend(int ch) {
		int p = last, np = ++size;
		max[last = np] = max[p] + 1, sz[np] = 1;
		for (; p && !A[p][ch]; p = par[p]) A[p][ch] = np;
		if (!p) return (void)(par[np] = 1);
		int q = A[p][ch];
		if (max[q] == max[p] + 1) par[np] = q;
		else {
			int nq = ++size;
			max[nq] = max[p] + 1;
			par[nq] = par[q], par[np] = par[q] = nq;
			memcpy(A[nq], A[q], sizeof(A[q]));
			for (; A[p][ch] == q; p = par[p]) A[p][ch] = nq;
		}
	}
	void dfs(int u) {
		for (std::vector<int>::iterator v = G[u].begin(); v != G[u].end(); ++v) {
			dfs(*v);
			sz[u] += sz[*v];
			ans += (lens - sz[*v]) * sz[*v] * (max[*v] - max[u]);
		}
	}
	void solve() {
		for (int i = 2; i <= size; i++) G[par[i]].push_back(i);
		dfs(1);
	}
}
