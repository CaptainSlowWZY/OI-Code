// Codeforces 873 F
#include <cstdio>
#include <cstring>
#include <algorithm>

const int LEN = 2e5 + 5;

char S[LEN], T[LEN];

namespace SAM {
	void extend(int ch, int tag);
	long long query();
}

int main() {
	scanf("%*d%s%s", S, T);
	for (int i = 0; S[i]; i++) SAM::extend(S[i] - 'a', T[i] ^ '0' ^ 1);
	printf("%lld\n", SAM::query());
	return 0;
}

namespace SAM {
	typedef int IntAr[LEN << 1];
	int size = 1, last = 1, A[LEN << 1][26];
	IntAr max, par, cnt, rsz, id;

	void extend(int ch, int tag) {
		int p = last, np = ++size;
		max[last = np] = max[p] + 1, rsz[np] = tag;
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
	long long query() {
		// pre-work
		for (int i = 1; i <= size; i++) ++cnt[max[i]];
		for (int i = 1; i <= size; i++) cnt[i] += cnt[i - 1];
		for (int i = 1; i <= size; i++) id[cnt[max[i]]--] = i;
		for (int i = size; i > 0; i--) rsz[par[id[i]]] += rsz[id[i]];
		long long ret = 0;
		for (int i = 2; i <= size; i++) {
			ret = std::max(ret, (long long)rsz[i] * max[i]);
		}
		return ret;
	}
}
