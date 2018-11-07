// strategy
#include <cstdio>
#include <algorithm>

const int MAXN = 4005;

struct Enm {
	int atk, def, delta, id;
	bool operator<(const Enm & e) const {
		return delta < e.delta;
	}
	friend void scan(Enm & e) {
		scanf("%d%d", &e.atk, &e.def);
		e.delta = e.atk - e.def;
	}
} A[MAXN];

int N, K;

int main() {
#if !defined(LOCAL) && !defined(ONLINE_JUDGE)
	freopen("strategy.in", "r", stdin);
	freopen("strategy.out", "w", stdout);
#endif
	scanf("%d%d", &N, &K);
	for (int i = 0; i < N; i++) {
		scan(A[i]);
		A[i].id = i;
	}

	std::sort(A, A + N);
	for (int i = 0; i < N; i++) {
		long long ans = 0;
		int cnt = 0;
		for (int j = 0; j < N; j++) {
			if (A[j].id == i) continue;
			if (cnt < K && A[j].delta < 0) ans += A[j].atk, ++cnt;
			else ans += A[j].def;
		}
		printf("%lld ", ans);
	}
	putchar('\n');

#if !defined(LOCAL) && !defined(ONLINE_JUDGE)
	fclose(stdin); fclose(stdout);
#endif
	return 0;
}
