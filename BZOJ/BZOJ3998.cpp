// BZOJ 3998
// TJOI 2015
#include <cstdio>
#include <cstring>
#include <algorithm>

const int LEN = 5e5 + 10;

int T, K, lens;
char S[LEN];

namespace SAM {
	void extend(int ch);
	void query(int t, int k);
}

int main() {
	scanf("%s%d%d", S, &T, &K);

	for (int i = 0; S[i]; i++) SAM::extend(S[i] - 'a');
	SAM::query(T, K);

	return 0;
}

namespace SAM {
	typedef int IntAr[LEN << 1];
	int size = 1, last = 1, A[LEN << 1][26];
	IntAr max, par, cnt, sz, id;

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
	void query(int t, int k) {
		// pre-work
		for (int i = 1; i <= size; i++) ++cnt[max[i]];
		for (int i = 1; i <= size; i++) cnt[i] += cnt[i - 1];
		for (int i = 1; i <= size; i++) id[cnt[max[i]]--] = i;
		for (int i = size; i > 0; i--) {
			cnt[i] = 0;
			if (t) sz[par[id[i]]] += sz[id[i]];
			else sz[id[i]] = 1;
		}
		sz[1] = 0;
		for (int i = size, cur; i > 0; i--) {
			cur = id[i];
			cnt[cur] = sz[cur];
			for (int c = 0; c < 26; c++) {
				if (!A[cur][c]) continue;
				cnt[cur] += cnt[A[cur][c]];
			}
		}

		if (k > cnt[1]) return (void)puts("-1");
		for (int cur = 1; k > 0; ) {
			for (int c = 0; c < 26; c++) {
				if (!A[cur][c]) continue;
				if (k <= cnt[A[cur][c]]) {
					putchar('a' + c);
					k -= sz[cur = A[cur][c]];
					break;
				}
				k -= cnt[A[cur][c]];
			}
		}
		putchar('\n');
	}
}
