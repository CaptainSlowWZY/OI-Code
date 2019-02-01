#include <bits/stdc++.h>
#define fir first
#define sec second
typedef long long LL;
typedef std::pair<int, int> Dish;
typedef std::set<Dish> myset;
const int MAXN = 1e5 + 10;
int N, M, have[MAXN], cost[MAXN];
LL rem = 0;
myset St;
int main() {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", have + i);
		rem += have[i];
	}
	for (int i = 0, ci; i < N; i++) {
		scanf("%d", cost + i);
		St.insert(Dish(cost[i], i));
	}

	for (int i = 0; i < M; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		if (!rem) {
			puts("0");
			continue;
		}
		--a;
		long long ans = 0;
		if (have[a] >= b) {
			rem -= b;
			if (!(have[a] -= b)) {
				myset::iterator it = St.find(Dish(cost[a], a));
				if (it != St.end())St.erase(it);
			}
			ans = (long long)cost[a] * b;
		}
		else if (b > rem) {
			ans = 0;
			St.clear();
			memset(have, 0, sizeof have);
			rem = 0;
		}
		else {
			rem -= b;
			ans = (LL)cost[a] * have[a];
			b -= have[a], have[a] = 0;
			myset::iterator it = St.find(Dish(cost[a], a));
			if (it != St.end()) St.erase(it);
			for (; b > 0; ) {
				it = St.begin();
				if (it == St.end()) {
					ans = 0;
					break;
				}
				if (have[it->sec] >= b) {
	//				printf(" b = %d\n", b);
	//				printf(" ans = %lld\n", ans);
					ans += (LL)it->fir * b;
	//				printf(" ans = %lld\n", ans);
					if (!(have[it->sec] -= b)) St.erase(it);
					b = 0;
				}
				else {
	//				printf("id: %d\n", it->sec);
					b -= have[it->sec];
					ans += (LL)it->fir * have[it->sec];
					have[it->sec] = 0;
					St.erase(it);
				}
			}
		}
		printf("%lld\n", ans);
	}

	return 0;
}
