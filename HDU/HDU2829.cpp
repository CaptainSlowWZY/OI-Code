#include <algorithm>
#include <cstdio>
#include <cstring>

const int kMaxn = 1010;

typedef int IAr[kMaxn];
typedef long long LL;

struct Info {
	int u, l, r;
} que[kMaxn];

int n, m;
IAr sum, sumq, left, nxtl;
LL DP[2][kMaxn], *prv, *nxt;

LL W(LL *dp, int l, int r) {
	LL t = sum[r] - sum[l];
	return dp[l] + t * t - sumq[r] + sumq[l];
}

int main() {
	while (~scanf("%d%d", &n, &m) && n + m) {
		++m;
		for (int i = 1, ai; i <= n; i++) {
			scanf("%d", &ai);
			sum[i] = sum[i - 1] + ai, sumq[i] = sumq[i - 1] + ai * ai;
		}
		
		memset(left, 0, sizeof left);
		prv = DP[0], nxt = DP[1];
		prv[0] = 0;
		LL ans = 0x7fffffffffffffff;
		for (int k = 1; k <= m; k++) {
			int hd = 0, tl = 1;
			que[0] = (Info){0, 1, n};
			for (int i = 1; i <= n; i++) {
				nxt[i] = W(prv, left[i], i);

				for (; hd < tl && que[hd].r < i; ++hd);
				nxtl[i] = que[hd].u, ++que[hd].l;
				for (; hd < tl && W(nxt, que[tl - 1].u, que[tl - 1].l) >=
						W(nxt, i, que[tl - 1].l); --tl);
				if (hd == tl) que[tl++] = (Info){i, i + 1, n};
				else {
					int l = que[tl - 1].l, r = que[tl - 1].r;
					for (int mid; l <= r; ) {
						mid = l + r >> 1;
						if (W(nxt, que[tl - 1].u, mid) >= 
								W(nxt, i, mid)) r = mid - 1;
						else l = mid + 1;
					}
					if (l <= n) {
						que[tl - 1].r = l - 1;
						que[tl++] = (Info){i, l, n};
					}
				}
			}
			ans = std::min(ans, nxt[n]);
			std::swap(prv, nxt);
			for (int i = 1; i <= n; i++) left[i] = nxtl[i];
		}

		printf("%lld\n", ans >> 1);
	}
	return 0;
}
