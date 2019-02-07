#include <bits/stdc++.h>

char S[5], S1[5];
int main() {
	scanf("%s", S1);
	for (int i = 0; i < 5; i++) {
		scanf("%s", S);
		if (S[0] == S1[0] || S[1] == S1[1]) {
			puts("YES");
			return 0;
		}
	}
	puts("NO");
	return 0;
}
