#include <bits/stdc++.h>
char S[510][510];
int N, ans;
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%s", S[i]);

	for (int i = 1; i + 1 < N; i++)
		for (int j = 1; j + 1 < N; j++)
			if (S[i][j] == 'X' &&
				S[i - 1][j - 1] == 'X' &&
				S[i - 1][j + 1] == 'X' && 
				S[i + 1][j - 1] == 'X' &&
				S[i + 1][j + 1] == 'X')
				++ans;
	printf("%d\n", ans);
	return 0;
}
