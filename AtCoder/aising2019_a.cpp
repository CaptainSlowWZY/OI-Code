#include <bits/stdc++.h>

int main() {
	int N, H, W;
	scanf("%d%d%d", &N, &H, &W);
	printf("%d\n", (N - H + 1) * (N - W + 1));
	return 0;
}
