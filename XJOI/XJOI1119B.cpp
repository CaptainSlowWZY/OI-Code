#include <cstdio>
#include <cstring>
#include <vector>

const int kLen = 1e6 + 10;

char S[kLen];

namespace sam {
	void extend(int ch);
	double solve();
}

int main() {
	scanf("%s", S);

	int len = strlen(S);
	for (int i = len - 1; i >= 0; i--) sam::extend(S[i] - 'a');

	printf("%.6lf\n", sam::solve());
	return 0;
}

namespace sam {
	int last = 1, size = 1, tag[kLen], max[kLen], A[kLen][26], par[kLen];
	std::vector<int> G[kLen];

	void extend(int ch) {
		int p = last, np = ++size;
		max[last = np] = max[p] + 1, tag[np] = 1;
		for (; p && !A[p][ch]; p = par[p]) A[p][ch] = np;
		if (!p) return (void)(par[np] = 1);
		int q = A[p][ch];
		if (max[p] == max[q] + 1) par[np] = q;
		else {
			int nq = ++size;
			max[nq] = max[p] + 1;
			par[nq] = par[q], par[q] = par[np] = nq;
			memcpy(A[nq], A[q], sizeof(A[q]));
			for (; A[p][ch] == q; p = par[p]) A[p][ch] = nq;
		}
	}
	double dfs(int u, int d) {
		if (tag[u]) return d;
		double ret = 0;
		for (auto v : G[u]) ret += 1.0 / dfs(v, max[v] - max[u]);
		return 1.0 / ret + d;
	}
	double solve() {
		for (int i = 1; i <= size; i++) G[par[i]].push_back(i);
		return dfs(1, 0);
	}
}
