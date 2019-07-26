#include <algorithm>
#include <cstdio>
#include <cstring>

const int kMaxn = 2e5 + 10;

char S[kMaxn];

namespace sam {
	void Extend(int);
	void Init();
	void Match(char *);
	int Ans();
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}
template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}

int main() {
	scanf("%s", S);
	for (int i = 0; S[i]; i++) sam::Extend(S[i] - 'a');

	sam::Init();
	while (~scanf("%s", S)) sam::Match(S);

	printf("%d\n", sam::Ans());
	return 0;
}

namespace sam {
	int size = 1, last = 1;
	int max[kMaxn], A[kMaxn][26], par[kMaxn];
	int id[kMaxn], val[kMaxn], ans[kMaxn];;

	void Extend(int ch) {
		int np = ++size, p = last;
		max[last = np] = max[p] + 1;
		for (; p && !A[p][ch]; p = par[p]) A[p][ch] = np;
		if (!p) return (void)(par[np] = 1);
		int q = A[p][ch];
		if (max[q] == max[p] + 1) par[np] = q;
		else {
			int nq = ++size;
			max[nq] = max[p] + 1;
			memcpy(A[nq], A[q], sizeof A[q]);
			par[nq] = par[q], par[q] = par[np] = nq;
			for (; A[p][ch] == q; p = par[p]) A[p][ch] = nq;
		}
	}
	void Init() {
		for (int i = 1; i <= size; i++) ++val[ans[i] = max[i]];
		for (int i = 1; i <= size; i++) val[i] += val[i - 1];
		for (int i = 1; i <= size; i++) id[val[max[i]]--] = i;
		memset(val, 0, sizeof val);
	}
	void Match(char str[]) {
		int len = 0, cur = 1;
		for (int i = 0; str[i]; i++) {
			if (A[cur][str[i] -= 'a']) {
				cur = A[cur][str[i]], ++len;
			} else {
				for (; cur && !A[cur][str[i]]; cur = par[cur]);
				if (!cur) {
					cur = 1, len = 0;
				} else {
					len = max[cur] + 1, cur = A[cur][str[i]];
				}
			}
			UMax(val[cur], len);
		}
		for (int i = size, u; i; i--) {
			u = id[i];
			UMax(val[par[u]], val[u]);
			UMin(ans[u], val[u]);
			val[u] = 0;
		}
	}
	int Ans() {
		int res = 0;
		for (int i = 1; i <= size; i++) UMax(res, ans[i]);
		return res;
	}
}
