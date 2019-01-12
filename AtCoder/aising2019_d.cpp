#include <bits/stdc++.h>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif

typedef long long LL;

const int MAXN = 1e5 + 10;

int N, Q, A[MAXN], MAX_DELTA, MINA = 1e9 + 100, MAXA;
LL sum[MAXN], sume[MAXN], sumo[MAXN];

void solve();

int main() {
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; i++) {
		scanf("%d", A + i);
		MINA = std::min(MINA, A[i]);
		MAXA = std::max(MAXA, A[i]);
	}

	MAX_DELTA = MAXA - MINA;
	for (int i = 1; i <= N; i++) {
		sum[i] = sum[i - 1] + A[i];
		sumo[i] = sumo[i - 1] + LL(i & 1 ? A[i] : 0);
		sume[i] = sume[i - 1] + LL(i & 1 ? 0 : A[i]);
	}

	for (int i = 0; i < Q; i++) solve();

	return 0;
}

void solve() {
	int X;
	scanf("%d", &X);

	int p = std::lower_bound(A + 1, A + 1 + N, X) - A;
	if (p >= N || !MAX_DELTA || p + 1 == N && A[p] == X)
		return (void)printf("%lld\n", N & 1 ? sumo[N] : sume[N]);
	if (p == 1)
		return (void)printf("%lld\n", sum[N] - sum[N / 2]);

	int l = 0, r = 1e9 + 1, left, right;	// [l, r)
	while (r - l > 1) {
		int mid = l + r >> 1;
		debug("  [%d, %d), mid=%d, range[%d, %d]\n", l, r, mid, std::max(0, X - mid), X + mid);
		left = std::lower_bound(A + 1, A + 1 + N, std::max(0, X - mid)) - A,
		right = std::upper_bound(A + 1, A + 1 + N, X + mid) - A - 1;
		debug("   Now: left=%d, A[left]=%d, right=%d, A[right]=%d\n", left, A[left], right, A[right]);
		if (right - left + 1 > N - right)	// Aoki get more
			r = mid;
		else	// Takahashi get more
			l = mid;
	}

	left = std::lower_bound(A + 1, A + 1 + N, std::max(0, X - l)) - A,
	right = std::upper_bound(A + 1, A + 1 + N, X + l) - A - 1;
	debug("l=%d, interval: [%d, %d]\n", l, left, right);
	if (right - left + 1 != N - right) left = std::max(1, right - N + right + 1);
	printf("%lld\n", (left & 1 ? sume[left - 1] : sumo[left - 1]) + sum[N] - sum[right]);
}
