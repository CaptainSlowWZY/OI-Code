#include <bits/stdc++.h>
int n, a[100010];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", a + i);
	}

	int last = a[0], cnt = 1, len = 0, ans = 0;
	for (int i = 1; i < n; i++) {
		if (a[i] != last) {
			ans = std::max(ans, std::min(cnt, len) * 2);
			last = a[i];
			len = cnt;
			cnt = 1;
		}
		else ++cnt;
	}
	ans = std::max(ans, std::min(cnt, len) * 2);
	printf("%d\n", ans);
	return 0;
}
