#include <algorithm>
#include <cstdio>

const int kMaxn = 105, kInf = 0x7fffffff;

int n;
int W[kMaxn];

bool Check(int x, int n1, int n2, int n5) {
	for (int i = 0; i <= n1; i++) {
		for (int j = 0; j <= n2; j++) {
			for (int k = 0; k <= n5; k++)
				if (i + j * 2 + 5 * k == x) return true;
		}
	} return false;
}

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		int inv = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", W + i);
			if (W[i] % 10) inv = 1;
			W[i] /= 10;
		}
		if (inv) { puts("-1"); continue; }
		int ans = kInf;
		for (int n1 = 0; n1 <= 1; n1++) {
			for (int n2 = 0; n2 <= 3; n2++) {
				for (int n10, n5 = 0; n5 <= 1; n5++) {
					for (int i = inv = n10 = 0; i < n; i++) {
						if (W[i] >= 10 && Check(W[i] % 10 + 10, n1, n2, n5))
							n10 = std::max(n10, W[i] / 10 - 1);
						else {
							if (!Check(W[i] % 10, n1, n2, n5)) { inv = 1; break; }
							n10 = std::max(n10, W[i] / 10);
						}
					} if (inv) continue;
					ans = std::min(ans, n1 + n2 + n5 + n10);
				}
			}
		} printf("%d\n", ans);
	} return 0;
}
