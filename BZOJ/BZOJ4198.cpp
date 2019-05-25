// NOI2015
#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

#define fir first
#define sec second

typedef std::pair<long long, int> PLi;

int n, k;
std::priority_queue<PLi, std::vector<PLi>, std::greater<PLi> > hp;

inline PLi operator+(const PLi & a, const PLi & b) {
	return PLi(a.fir + b.fir, std::max(a.sec, b.sec));
}

int main() {
	scanf("%d%d", &n, &k);
	long long wi;
	for (int i = 0; i < n; i++) {
		scanf("%lld", &wi);
		hp.push(PLi(wi, 0));
	}	

	if ((n - 1) % (k - 1)) {
		for (int i = k - 1 - (n - 1) % (k - 1); i; --i) {
			hp.push(PLi(0, 0));
		}
	}
	long long ans = 0;
	for (; hp.size() > 1; ) {
		PLi u(0, 0);
		for (int i = 0; i < k; i++) {
			u = u + hp.top();
			hp.pop();
		}
		ans += u.fir;
		++u.sec;
		hp.push(u);
	}
	
	printf("%lld\n%d\n", ans, hp.top().sec);
	return 0;
}
