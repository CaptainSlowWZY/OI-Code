#include <cstdio>

int main() {
	int s;
	scanf("%d", &s);
//	printf("%d\n", s);

	for (int i = 1; i <= 498; i++)
		for (int j = 1; i + j <= 498; j++) {
			if (i * j > s) continue;
			if (i * j == s) {
//				puts("Case 1");
				for (int u = 1; u <= i; u++) printf("%d %d\n", u, i + 1);
				for (int u = 1; u <= j; u++) printf("%d %d\n", i + 1 + u, i + 1 + j + 1);
				printf("%d %d\n0 0\n", i + 1, i + 1 + j + 1);
				return 0;
			}
			int rem = s - i * j;
			if (rem > j - 1 && rem - j + 1 + i + j + 2 <= 500) {
//				puts("Case 2");
				int t = rem - j + 1;
				for (int u = 1; u <= i; u++) printf("%d %d\n", u, i + 1);
				for (int u = 1; u <= j; u++) printf("%d %d\n", i + 1 + u, i + 1 + j + 1);
				printf("%d %d\n", i + 1, i + 1 + j + 1);
				for (int u = 1, prv = i + 2; u <= t; u++) {
					printf("%d %d\n", prv, i + j + 2 + u);
					prv = i + j + 2 + u;
				}
				puts("0 0");
				return 0;
			}
			else if (rem > i - 1 && rem - i + 1 + i + j + 2 <= 500) {
//				puts("Case 3");
				int t = rem - i + 1;
				for (int u = 1; u <= i; u++) printf("%d %d\n", u, i + 1);
				for (int u = 1; u <= j; u++) printf("%d %d\n", i + 1 + u, i + 1 + j + 1);
				printf("%d %d\n", i + 1, i + 1 + j + 1);
				for (int u = 1, prv = 1; u <= t; u++) {
					printf("%d %d\n", prv, i + j + 2 + u);
					prv = i + j + 2 + u;
				}
				puts("0 0");
				return 0;
			}	
		}

	return 0;
}
