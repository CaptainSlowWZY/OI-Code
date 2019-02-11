#include <bits/stdc++.h>

#define fir first
#define sec second

typedef std::pair<int, int> Pii;

int N, M, K;
std::priority_queue<Pii, std::vector<Pii>, std::greater<Pii> > hp;
std::vector<Pii> V;

inline bool cmp(const Pii & p1, const Pii & p2) {
	return p1.sec < p2.sec;
}

int main() {
	scanf("%d%d%d", &N, &M, &K);
	for (int ai, i = 0; i < N; i++) {
		scanf("%d", &ai);
		if (hp.size() < M * K) hp.push(Pii(ai, i));
		else if (ai > hp.top().fir) {
			hp.pop();
			hp.push(Pii(ai, i));
		}
	}

	long long ans = 0;
	for (; !hp.empty(); hp.pop()) V.push_back(hp.top()), ans += hp.top().fir;
	printf("%lld\n", ans);
	std::sort(V.begin(), V.end(), cmp);
//	for (auto p : V) printf("%d idx = %d\n", p.fir, p.sec);
	int t = 0, c = 0;
	for (auto p : V)
		if (++t == M) {
			if (++c == K) break;
			printf("%d ", p.sec + 1);
			t = 0;
		}
	putchar('\n');
	return 0;
}
