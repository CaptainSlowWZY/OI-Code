#include <algorithm>
#include <cstdio>

int n;
int H[100005];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", H + i);
	n = std::unique(H, H + n) - H;
	int del = 0, ans = 0;
	for (int i = 1; i < n; i++) {
		if (H[i] > H[i - 1]) {
			if (del != 1) ++ans;
			del = 1;
		} else  {
			if (del != -1) ++ans;
			del = -1;
		}
	} printf("%d\n", ans + 1);
	return 0;
}
