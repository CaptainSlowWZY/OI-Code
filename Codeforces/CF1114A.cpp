#include <bits/stdc++.h>

int main() {
	int x, y, z, a, b, c;
	scanf("%d%d%d", &x, &y, &z);
	scanf("%d%d%d", &a, &b, &c);
	if (a < x) {
		puts("NO");
		return 0;
	}
	a -= x;
	if (a + b < y) {
		puts("NO");
		return 0;
	}
	if (a + b + c < y + z) puts("NO");
	else puts("YES");
	return 0;
}
