#include <cstdio>

int n, A[20];

int main() {
	for (int t = 10; t--; ) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", A + i);

		int flag = 0;
		for (int _xor, mask = (1 << n) - 1; mask > 0; mask--) {
			for (int i = _xor = 0; i < n; i++) {
				if (mask >> i & 1) _xor ^= A[i];
			}
			if (!_xor) { flag = 1; break; }
		}
		puts(flag ? "NO" : "YES");
	}
	return 0;
}
