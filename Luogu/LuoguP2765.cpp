// Luogu P2765
#include <bits/stdc++.h>

int N;
std::vector<int> P[60];

bool judge(int x) {
	int y = (int)floor(sqrt(x + 0.5));
	return y * y == x;
}

int main() {
	scanf("%d", &N);
	int ans = 1;
	for (; ; ++ans) {
		int suc = 0;
		for (int i = 0; i < N; i++)
			if (!P[i].size() || judge(*P[i].rbegin() + ans)) {
				P[i].push_back(ans);
				suc = 1;
				break;
			}
		if (!suc) break;
	}

	printf("%d\n", ans - 1);
	for (int i = 0; i < N; i++) {
		for (auto b : P[i]) printf("%d ", b);
		putchar('\n');
	}
	return 0;
}
