#include <cstdio>

int n;

int main() {
	scanf("%d", &n);
	int _xor = 0;
	for (int i = 0, ai; i < n; i++) {
		scanf("%d", &ai);
		_xor ^= ai;
	}

	puts(_xor ? "No" : "Yes");
	return 0;
}
