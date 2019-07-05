#include <cstdio>
#include <algorithm>

const int kMaxn = 3e5 + 5;

int n, q;
int A[kMaxn], last[20], go[kMaxn][20];

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; i++) scanf("%d", A + i);
	
	for (int i = 0; i < 19; i++) last[i] = go[n][i] = n;
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < 19; j++) {
			if (A[i] >> j & 1) {
				go[i][j] = i;
			}
			else {
				go[i][j] = n;
				for (int k = 0; k < 19; k++) {
					if (A[i] >> k & 1) go[i][j] = std::min(go[i][j], go[last[k]][j]);
				}
			}
		}
		for (int j = 0; j < 19; j++) {
			if (A[i] >> j & 1) last[j] = i;
		}
	}

	for (int flag, x, y; q--; ) {
		scanf("%d%d", &x, &y);
		--x, --y;
		for (int i = flag = 0; i < 19; i++) {
			if (A[y] >> i & 1) {
				flag |= go[x][i] <= y;
			}
		}
		puts(flag ? "Shi" : "Fou");
	}

	return 0;
}
