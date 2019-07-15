#include <cstdio>

const int kMaxn = 1e5 + 10;

int n;
int con[kMaxn];

int main() {
	scanf("%d", &n);

	int k = 0, pw = 1;
	for (; pw < n; ++k, pw <<= 1);
	if (pw == n) {
		puts("No");
		return 0;
	} else puts("Yes");

	puts("1 2");
	puts("2 3");
	printf("3 %d\n", n + 1);
	printf("%d %d\n", n + 1, n + 2);
	printf("%d %d\n", n + 2, n + 3);
	con[2] = n + 2, con[3] = 3;
	if (n == 3) return 0;
	for (int i = 4; i < n; i += 2) {
		printf("%d %d\n", i, i + 1);
		printf("%d %d\n", i, n + 1);
		printf("%d %d\n", n + 1, n + i + 1);
		printf("%d %d\n", n + i + 1, n + i);
		con[i] = i, con[i + 1] = n + i + 1;
	}
	if (n & 1 ^ 1) {
		for (int i = 2; i < n; i++) {
			if ((n ^ 1 ^ i) < n) {
				printf("%d %d\n", n, con[i]);
				printf("%d %d\n", con[n ^ 1 ^ i], n + n);
				break;
			}
		}
	}

	return 0;
}
