#include <cstdio>
#include <vector>

const int kMaxn = 3e5 + 5;

int n;
std::vector<int> pos[kMaxn];

namespace bit {
	int T[kMaxn];
	int Sum(int p) { int r = 0; for (; p; p &= p - 1) r += T[p]; return r; }
	inline int Sum(int l, int r) { return Sum(r) - Sum(l - 1); }
	void Add(int p) { for (; p <= n; p += p & -p) ++T[p]; }
}

int main() {
	scanf("%d", &n);
	for (int i = 1, ai; i <= n; ++i) {
		scanf("%d", &ai); pos[ai].push_back(i);
	}
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (pos[i].empty()) continue;
		std::vector<int> & cur = pos[i];
		int hd = 0, tl = (int)cur.size() - 1;
		for (int lc, rc; hd <= tl; ) {
			lc = cur[hd] - 1 - bit::Sum(1, cur[hd] - 1);	
			rc = n - cur[tl] - bit::Sum(cur[tl] + 1, n);
			if (lc < rc) {
				ans += lc; bit::Add(cur[hd++]);
			} else {
				ans += rc; bit::Add(cur[tl--]);
			}
		}
	} printf("%lld\n", ans);
	return 0;
}

