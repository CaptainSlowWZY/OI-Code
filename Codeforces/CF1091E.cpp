// Codeforces Good Bye 2018 E
#include <cstdio>
#include <algorithm>
#include <functional>
#include <vector>

typedef long long LL;

const int MAXN = 5e5;

int N, A[MAXN + 5];
LL sum[MAXN + 5];
std::vector<int> ans;

int main() {
	scanf("%d", &N);
	int odd = 0;
	for (int i = 1; i <= N; i++) {
		scanf("%d", A + i);
		(odd += A[i] & 1) &= 1;
	}

	std::sort(A + 1, A + 1 + N, std::greater<int>() );
	for (int i = 1; i <= N; i++) sum[i] = sum[i - 1] + A[i];
	LL lb = 0, ub = N;
	for (int i = 1; i <= N; i++) {
		int k = std::lower_bound(A + i + 1, A + 1 + N, i, std::greater<int>() ) - A;
		LL S1 = sum[i], S2 = sum[N] - sum[k - 1] + LL(k - i - 1) * i + LL(i - 1) * i;
		if (S1 > S2 + i) { puts("-1"); return 0; }
		lb = std::max(lb, S1 - S2);
		ub = std::min(ub, S2 + i + A[i] - S1);
	}
	for (int i = lb; i <= ub; i++)
		if ((i & 1) == odd) ans.push_back(i);

	if (ans.empty()) puts("-1");
	else {
		for (auto d0 : ans) printf("%d ", d0);
		putchar('\n');
	}

	return 0;
}
