// BZOJ 2298
// HAOI 2011
#include <cstdio>
#include <algorithm>

const int MAXN = 1e5 + 5;

struct Wzy {
	int l, r, cnt;
	bool operator!=(const Wzy & w) const {
		return l != w.l || r != w.r;
	}
	bool operator<(const Wzy & w) const {
		return l == w.l ? r < w.r : l < w.l;
	}
} A[MAXN];

int N, tot, DP[MAXN];

inline bool cmp(const Wzy & w1, const Wzy & w2) {
	return w1.r == w2.r ? w1.l < w2.l : w1.r < w2.r;
}
int find(int lb, int rb, const Wzy & w) {
	++rb;
	for (int mid; rb - lb > 1; ) {	// [lb, rb)
		mid = lb + rb >> 1;
		if (A[mid].r < w.l) lb = mid;
		else rb = mid;
	}
	return lb;
}

int main() {
	scanf("%d", &N);
	for (int i = 0, ai, bi; i < N; i++) {
		scanf("%d%d", &ai, &bi);
		++ai, bi = N - bi;
		if (ai > bi) continue;
		A[++tot] = (Wzy){ai, bi, 0};
	}

	std::sort(A + 1, A + 1 + tot);
	int tot0 = tot;
	A[tot = 1].cnt = 1;
	for (int i = 2; i <= tot0; i++)
		if (A[i] != A[tot]) {
			A[++tot] = A[i];
			A[tot].cnt = 1;
		}
		else ++A[tot].cnt;
	std::sort(A + 1, A + 1 + tot, cmp);

	DP[0] = 0, A[0] = (Wzy){0, 0, 0};
	for (int i = 1; i <= tot; i++) {
		int k = find(0, i - 1, A[i]);
		A[i].cnt = std::min(A[i].cnt, A[i].r - A[i].l + 1);
		DP[i] = std::max(DP[i - 1], DP[k] + A[i].cnt);
	}

	printf("%d\n", N - DP[tot]);
	return 0;
}	
