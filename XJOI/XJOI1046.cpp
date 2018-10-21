// XJOI 1046
#include <cstdio>
#include <functional>
#include <queue>
#include <vector>
typedef long long LL;

int N;
std::priority_queue<LL, std::vector<LL>, std::greater<LL> > hp;

int main() {
	scanf("%d", &N);
	LL ans = 0;
	for (int ai, i = 0; i < N; i++) {
		scanf("%d", &ai);
		hp.push(ai);
	}
	for (; hp.size() > 1; ) {
		LL tmp = hp.top(); hp.pop();
		tmp += hp.top(); hp.pop();
		ans += tmp;
		hp.push(tmp);
	}
	printf("%lld\n", ans);
	return 0;
}

// AC!!!
