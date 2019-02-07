#include <bits/stdc++.h>

int N, A[15];

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", A + i);

	for (int mask = (1 << N) - 1; mask >= 0; --mask) {
		int x = 0;
		for (int i = 0; i < N; i++)
			(x += mask >> i & 1 ? A[i] : -A[i]) %= 360;
		if (!x) {
			puts("YES");
			return 0;
		}
	}

	puts("NO");
	return 0;
}
