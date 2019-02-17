// SPOJ 1811 LCS
// By Suffix Automaton
#include <cstdio>
#include <cstring>
#include <algorithm>

const int LEN = 250010;

char S[LEN];

namespace SAM {
	void insert(int c);
	int match(const char *str);
}

int main() {
	scanf("%s", S);
	for (int i = 0; S[i]; i++) SAM::insert(S[i] - 'a');
	scanf("%s", S);
	printf("%d\n", SAM::match(S));

	return 0;
}

namespace SAM {
	const int ARSZ = LEN << 1;
	int size = 1, last = 1, A[ARSZ][26], max[ARSZ], par[ARSZ];

	void insert(int c) {
		int p = last, np = ++size;
		max[np] = max[p] + 1, last = np;
		for (; p && !A[p][c]; p = par[p]) A[p][c] = np;
		if (!p) {
			par[np] = 1;
			return;
		}
		int q = A[p][c];
		if (max[q] == max[p] + 1) par[np] = q;
		else {
			int nq = ++size;
			max[nq] = max[p] + 1;
			par[nq] = par[q], par[q] = par[np] = nq;
			memcpy(A[nq], A[q], sizeof(A[q]));
			for (; A[p][c] == q; p = par[p]) A[p][c] = nq;
		}
	}

	int match(const char *str) {
		int ret = 0, len = 0, cur = 1;
		for (int i = 0, ch; str[i]; i++) {
			if (A[cur][ch = str[i] - 'a']) ++len, cur = A[cur][ch];
			else {
				for (; cur && !A[cur][ch]; cur = par[cur]);
				if (!cur) cur = 1, len = 0;
				else len = max[cur] + 1, cur = A[cur][ch];
			}
			ret = std::max(ret, len);
		}
		return ret;
	}
}
