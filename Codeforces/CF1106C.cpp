#include <bits/stdc++.h>
int N, A[(int)3e5 + 10];
inline long long sqr(long long x) {return x * x;}
int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d", A + i);
	std::sort(A, A + N);
	long long ans = 0;
	for (int i = 0; i + i < N; i++) {
		if (i == N - 1 - i) ans += sqr(A[i]);
		else ans += sqr(A[i] + A[N - 1 - i]);
	}
	printf("%lld\n", ans);
	return 0;
}
