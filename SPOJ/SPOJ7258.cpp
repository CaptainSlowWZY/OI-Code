// SPOJ 7258 - SUBLEX
#include <cstdio>
#include <cstring>
#include <algorithm>

const int LEN = 9e4 + 5;

char S[LEN];

namespace SAM {
	const int ARSZ = LEN << 1;
	int size = 1, last = 1, A[ARSZ][26], max[ARSZ], par[ARSZ], cnt[ARSZ];
	
	void extend(int ch);
	int dfs(int u);
	void query(int k);
	inline void prep() {
		memset(cnt, 0xff, sizeof cnt);
		dfs(1);
	}
}

int main() {
	scanf("%s", S);
	for (int i = 0; S[i]; i++) SAM::extend(S[i] - 'a');
	SAM::prep();
	int Q;
	scanf("%d", &Q);
	for (int k; Q--; ) {
		scanf("%d", &k);
		SAM::query(k);
	}
	return 0;
}

namespace SAM {
	void extend(int ch) {
		int p = last, np = ++size;
		max[last = np] = max[p] + 1;
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
	int dfs(int u) {
		if (~cnt[u]) return cnt[u];
		int & ret = cnt[u];
		ret = 1;
		for (int i = 0; i < 26; i++)
			if (A[u][i]) ret += dfs(A[u][i]);
		return ret;
	}
	void query(int k) {
		int cur = 1;
		for (int f; k > 0; ) {
			f = 0;
			for (int i = 0; i < 26; i++)
				if (A[cur][i]) {
					if (k <= cnt[A[cur][i]]) {
						putchar('a' + i);
						cur = A[cur][i], f = 1, --k;
						break;
					}
					k -= cnt[A[cur][i]];
				}
			if (!f) break;
		}
		putchar('\n');
	}
}
