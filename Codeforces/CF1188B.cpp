#include <cstdio>
#include <map>

#define sec second

std::map<int, int> mp;

int main() {
	int n, p, k;
	scanf("%d%d%d", &n, &p, &k);
	for (int i = 0, ai; i < n; i++) {		
		scanf("%d", &ai);
		ai = (1ll * ai * ai % p * ai % p * ai % p - 
				1ll * k * ai % p) % p;
		ai = (ai + p) % p;
		++mp[ai];
	}

	long long ans = 0;
	for (std::map<int, int>::iterator it = mp.begin(); 
			it != mp.end(); ++it) {
		ans += 1ll * it->sec * (it->sec - 1) >> 1;
	}

	printf("%lld\n", ans);
	return 0;
}
