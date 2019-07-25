#include <cstdio>
#include <algorithm>

int n, A[300010];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", A + i);

	int l = 1, r = n;
	if (A[l] == A[r]) {
		for (; l < r && A[l + 1] == A[l]; l++);
		for (; l < r && A[r - 1] == A[r]; r--);
		printf("%d\n", std::max(n - l - 1, r - 2));
	} else printf("%d\n", n - 1);	
	return 0;
}
