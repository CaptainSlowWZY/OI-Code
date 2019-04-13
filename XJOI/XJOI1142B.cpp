// cards
#include <cstdio>
#include <cstring>
#include <algorithm>

const int kMaxn = 1005;

typedef int IAr[kMaxn];

int n;
IAr A, B, len, pos, vis, DP[kMaxn];

int main() {
	for (int i = 2; i <= 1000; i++) {
		for (int j = i; j <= 1000; j++) {
			DP[i][j] = DP[i][j - i] + i - 1;
			if (j > i) {
				DP[i][j] = std::max(DP[i][j], 
								DP[i][j - i - 1] + i);
			}
		}
	}

	int t;
	scanf("%d", &t);
	for (; t--; ) {
		scanf("%d", &n); 
		for (int i = 1; i <= n; i++) {
			scanf("%d", A + i);
			pos[A[i]] = i;
		}
		for (int i = 1; i <= n; i++) scanf("%d", B + i);

		memset(vis, 0, sizeof vis);
		int ans = 0, totl = 0;
		for (int i = 1; i <= n; i++) {
			if (vis[A[i]]) continue;
			vis[A[i]] = 1;
			int & cnt = len[totl++];
			cnt = 1;
			for (int j = B[i]; j != A[i]; j = B[pos[j]]) {
				vis[j] = 1, ++cnt;
			}
			if (cnt == 1) {
				++ans, --totl;
			}
		}
		
		for (int i = 2; i <= n; i++) {
			int sum = 0;
			for (int j = 0; j < totl; j++) sum += DP[i][len[j]];
			ans = std::max(ans, sum);
		}
		printf("%d\n", ans);
	}
	return 0;
}
