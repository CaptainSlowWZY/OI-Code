// SA(M) ?
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cassert>

const int kMaxn = 5e4 + 10;

namespace sam {
	void Init();
	void Extend(int ch);
	long long Calc();
}
inline int Id(char ch) {
	return islower(ch) ? ch - 'a' : ch - 'A' + 26;
}

char S[kMaxn];

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		using namespace sam;
		scanf("%s", S);
		Init();
		for (int i = 0; S[i]; i++) {
		//	assert(isalpha(S[i]));
			Extend(Id(S[i]));
		}
		printf("%lld\n", Calc());
	}

	return 0;
}

namespace sam {
	int par[kMaxn << 1], max[kMaxn << 1];
	int size, last, A[kMaxn << 1][26 << 1];

	void Init() {
		max[last = size = 1] = 0;
		par[1] = 0;
		memset(A[1], 0, sizeof A[1]);
	}
	void Extend(int ch) {
		int p = last, np = ++size;
		memset(A[np], 0, sizeof A[np]);
		max[last = np] = max[p] + 1;
		for (; p && !A[p][ch]; p = par[p]) A[p][ch] = np;
		if (!p) return (void)(par[np] = 1);
		int q = A[p][ch];
		if (max[p] + 1 == max[q]) par[np] = q;
		else {
			int nq = ++size;
			max[nq] = max[p] + 1;
			par[nq] = par[q], par[q] = par[np] = nq;
			memcpy(A[nq], A[q], sizeof A[nq]);
			for (; A[p][ch] == q; p = par[p]) A[p][ch] = nq;
		}
	}
	long long Calc() {
		long long ret = 0;
		for (int i = 1; i <= size; i++) ret += max[i] - max[par[i]];
		return ret;
	}
}
