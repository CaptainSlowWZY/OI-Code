// SPOJ 1812 LCS II
#include <cstdio>
#include <cstring>
#include <algorithm>

const int LEN = 1e5 + 10;

int lens;
char S[LEN];

namespace SAM {
	void extend(int ch);
	void prep();
	void match(const char *str);
	int query();
}

int main() {
	scanf("%s", S);
	lens = strlen(S);
	for (int i = 0; S[i]; i++) SAM::extend(S[i] - 'a');
	SAM::prep();
	for (; scanf("%s", S) != EOF; ) SAM::match(S);
	printf("%d\n", SAM::query());
	return 0;
}

namespace SAM {
	typedef int IntAr[LEN << 1];
	int size = 1, last = 1, A[LEN << 1][26];
	IntAr max, par, val, ans, id;

	void extend(int ch) {
		int p = last, np = ++size;
		max[np] = max[p] + 1, last = np;
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
	void prep() {
		for (int i = 1; i <= size; i++) ++val[ans[i] = max[i]];
		for (int i = 1; i <= lens; i++) val[i] += val[i - 1];
		for (int i = 1; i <= size; i++) id[val[max[i]]--] = i; 
//		memset(val, 0, sizeof val);
	}
	void match(const char *str) {
		int cur = 1, len = 0;
		for (int i = 0, ch; str[i]; i++) {
			if (A[cur][ch = str[i] - 'a']) ++len, cur = A[cur][ch];
			else {
				for (; cur && !A[cur][ch]; cur = par[cur]);
				if (!cur) cur = 1, len = 0;
				else len = max[cur] + 1, cur = A[cur][ch];
			}
			val[cur] = std::max(val[cur], len);
		}
		for (int i = size; i > 0; i--) {
			cur = id[i];
			val[par[cur]] = std::max(val[par[cur]], val[cur]);
			ans[cur] = std::min(ans[cur], val[cur]);
			val[cur] = 0;
		}
	}
	int query() {
		int ret = 0;
		for (int i = 1; i <= size; i++) ret = std::max(ret, ans[i]);
		return ret;
	}
}
