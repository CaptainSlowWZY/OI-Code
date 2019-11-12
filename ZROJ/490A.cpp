#include <cstdio>
#include <set>

const int kMaxn = 1e6 + 5;

int n, n2, m, vis[2][kMaxn << 1];
std::set<int> st;

int main() {
	scanf("%d%d", &n, &m);
	for (int x, y, i = 0; i < m; ++i) { scanf("%d%d", &x, &y); st.insert(x - y); vis[x + y & 1][x + y] = 1; }
	long long ans = 0;
	n2 = n << 1;
	for (int i = 2; i <= n2; ++i) {
	//	if (vis[i & 1][i]) printf(" x + y = %d, %d\n", i, (i <= n + 1 ? i - 1 : n2 - i + 1));
		if (vis[i & 1][i]) ans += (i <= n + 1 ? i - 1 : n2 - i + 1);
		vis[i & 1][i] += vis[i & 1][i - 2];
	}
	for (std::set<int>::iterator it = st.begin(); it != st.end(); ++it) {
		int l, r;
		if (*it < 0) {
			l = 2 - *it, r = n2 + *it;
//			printf(" !x - y %d, len %d, [%d, %d] cover %d\n", *it, n + *it, l, r, vis[r & 1][r] - vis[l & 1][l - 2]);
			ans += n + *it - vis[r & 1][r] + vis[l & 1][l - 2];
		} else {
			l = 2 + *it, r = n2 - *it;
//			printf(" x - y %d, len %d, [%d, %d] cover %d\n", *it, n - *it, l, r, vis[r & 1][r] - vis[l & 1][l - 2]);
			ans += n - *it - vis[r & 1][r] + vis[l & 1][l - 2];
		}
	}
	printf("%lld\n", ans); return 0;
}
