#include <cstdio>

int n;
int A[10010];

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", A + i);
		int ans = 0;
		for (int i = n & 1; i < n; i += 2) {
			ans ^= A[i + 1] - A[i];
		}
		if (n & 1) ans ^= A[0];
		puts(ans ? "TAK" : "NIE");
	}
	return 0;
}
