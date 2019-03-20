#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

const int kMaxn = 1e5 + 10;

int n, m, A[kMaxn];
std::vector<int> peo[kMaxn];
std::multiset<int> L, R;

int main() {
	scanf("%d%d", &n, &m);
	long long ans = 0;
	for (int i = 0, p, s, q, t; i < n; i++) {
		scanf("%d%d%d%d", &p, &s, &q, &t);
		if (p == q) {
			ans += std::abs(s - t);
			continue;
		}
		if (p > q) {
			std::swap(p, q), std::swap(s, t);
		}
		peo[p].push_back(s), peo[q - 1].push_back(t);
		++A[p + 1], --A[q];
	}
	
	for (int i = 1; i <= m; i++) A[i] += A[i - 1];
	for (int i = 1; i <= m; i++) {
		while (L.size() > A[i]) {
			L.erase(L.begin());
			R.erase(--R.end());
		}
		for (auto j : peo[i]) {
			if (L.empty()) {
				L.insert(j);
				R.insert(j);
			} else {
				if (j >= *R.begin()) {
					ans += j - *R.begin();
					R.insert(j), R.insert(j);
					L.insert(*R.begin()), R.erase(R.begin());
				} else if (j <= *L.rbegin()) {
					ans += *L.rbegin() - j;
					L.insert(j), L.insert(j);
					R.insert(*L.rbegin()), L.erase(--L.end());
				} else {
					L.insert(j), R.insert(j);
				}
			}
		}
	}

	printf("%lld\n", ans);
	return 0;
}
