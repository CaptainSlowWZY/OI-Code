#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long double LD;

const int kMaxn = 1e5 + 10;

struct Info {
	int u, l, r;
} que[kMaxn];

int n, L, P;
int sum[kMaxn], left[kMaxn], col[kMaxn];
char S[kMaxn][32];
LD DP[kMaxn];

LD FPow(LD bs, int ex) {
	LD res = 1;
	for (; ex; bs *= bs, ex >>= 1) {
		if (ex & 1) res *= bs;
	}
	return res;
}
LD W(int l, int r) {
	return DP[l] + FPow(abs(sum[r] - sum[l] + r - l - 1 - L), P);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d%d", &n, &L, &P);
		for (int i = 1; i <= n; i++) {
			scanf("%s", S[i]);
			sum[i] = sum[i - 1] + strlen(S[i]);
		}
	/*	for (int i = 1; i <= n; i++)
			printf(" sum %d = %d\n", i, sum[i]);
		puts("");*/
		DP[0] = 0;
		int hd = 0, tl = 1;
		que[0] = (Info){0, 1, n};
		for (int i = 1; i <= n; i++) {
			for (; hd + 1 < tl && que[hd].r < i; ++hd);
			DP[i] = W(que[hd].u, i); left[i] = que[hd].u;
		/*	printf(" DP[%d] = %.0Lf\n", i, DP[i]);
			printf(" left %d = %d\n", i, left[i]);
			for (int j = hd; j < tl; j++)
				printf("   que %d [%d, %d]\n", que[j].u, que[j].l, que[j].r);*/
			++que[hd].l;
			for (; hd < tl && W(que[tl - 1].u, que[tl - 1].l) >=
				W(i, que[tl - 1].l); --tl);
			if (hd == tl) {
				que[tl++] = (Info){i, i + 1, n};
				continue;
			}
			int l = que[tl - 1].l, r = que[tl - 1].r;
			//	printf("  Binary Search in [%d, %d]\n", l, r);
			for (int mid; l <= r; ) {
				mid = l + r >> 1;
				if (W(que[tl - 1].u, mid) >= W(i, mid)) r = mid - 1;
				else l = mid + 1;
			}
			if (l <= n) {
				que[tl - 1].r = l - 1;
				que[tl++] = (Info){i, l, n};
			}
		}

		if (DP[n] > 1e18) puts("Too hard to arrange");
		else {
			printf("%.0Lf\n", DP[n]);
			int totc = 0;
			for (int i = n; i > 0; i = left[i]) {
				++totc;
				for (int j = i; j > left[i]; j--) col[j] = totc;
			}
			col[n + 1] = -1;
			for (int i = 1; i <= n; i++) {
				printf("%s", S[i]);
				putchar(col[i] != col[i + 1] ? '\n' : ' ');
			}
		}
		puts("--------------------");
	}
	return 0;
}
