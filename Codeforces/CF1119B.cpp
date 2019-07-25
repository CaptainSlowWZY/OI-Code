#include <cstdio>
#include <algorithm>

int n, h;
int A[3010];

bool Check(int);

int main() {
	scanf("%d%d", &n, &h);
	for (int i = 0; i < n; i++) scanf("%d", A + i);

	for (int i = 1; i <= n; i++) {
		if (!Check(i)) {
			printf("%d\n", i - 1);
			return 0;
		}
	}
	printf("%d\n", n);
	return 0;
}

bool Check(int k) {
	static int B[3010];
	for (int i = 0; i < k; i++) B[i] = A[i];
	std::sort(B, B + k);
	int need = 0;
	for (int i = k - 1; i >= 0; i -= 2) {
		need += B[i];
	}
	return need <= h;
}
