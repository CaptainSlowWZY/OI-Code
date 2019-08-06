#include <cstdio>
#include <map>

int K, n;
std::map<int, int> mp;

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d", &K, &n);
		mp.clear(); ++mp[0];
		for (int ai, i = 1, sum = 0; i <= n; i++) {
			scanf("%d", &ai);
			++mp[(sum += ai % K) %= K];
		} long long ans = 0;
		for (auto pii : mp) 
			ans += 1ll * (pii.second - 1) * pii.second / 2;
		printf("%lld\n", ans);
	} return 0;
}
