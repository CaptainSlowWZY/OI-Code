#include <cstdio>
#include <map>

const int kLen = 1e5 + 10;

long long ans;

namespace sam {
	void Extend(int);
}

int main() {
	int n;
	scanf("%d", &n);
	for (int ch; n--; ) {
		scanf("%d", &ch);
		sam::Extend(ch);
		printf("%lld\n", ans);
	}

	return 0;
}

namespace sam {
	typedef int IAr[kLen << 1];

	int size = 1, last = 1;
	std::map<int, int> A[kLen << 1];
	IAr max, fa;

	inline int CalcSub(int p) {
		return max[p] - max[fa[p]];
	}
	void Extend(int ch) {
		int np = ++size, p = last;
		max[last = np] = max[p] + 1;
		for (; p && !A[p].count(ch); p = fa[p]) A[p][ch] = np;
		if (!p) fa[np] = 1;
		else {
			int q = A[p][ch];
			if (max[p] + 1 == max[q]) fa[np] = q;
			else {
				int nq = ++size;
				max[nq] = max[p] + 1;
				fa[nq] = fa[q], fa[q] = fa[np] = nq;
				A[nq] = A[q];
				for (; A[p][ch] == q; p = fa[p]) A[p][ch] = nq;
			}
		}
		ans += CalcSub(np);
	}
}
