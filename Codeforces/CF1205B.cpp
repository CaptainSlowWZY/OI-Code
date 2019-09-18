#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define fir first
#define sec second
#define pb push_back

typedef long long LL;
typedef std::pair<int, int> Pii;

const int kInf = 0x3f3f3f3f, kMaxn = 1e5 + 5;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}

int n, ans;
LL A[kMaxn];
int vis[kMaxn], tag[kMaxn], dis[kMaxn];
std::vector<int> pos[60], bit[kMaxn];

void Dfs(int u, int fa);

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", A + i);
		for (int j = 0; j < 60; j++) {
			if (A[i] >> j & 1) {
				bit[i].pb(j);
				pos[j].pb(i);
			}
		}
	}
	for (int j = 0; j < 60; j++) {
		if (pos[j].size() > 2) {
			puts("3");
			return 0;
		}
	} ans = kInf;
	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			tag[i] = 1, dis[i] = 0;
			Dfs(i, -1);
		}
	} printf("%d\n", ans == kInf ? -1 : ans);
	return 0;
}

void Dfs(int u, int fa) {
	vis[u] = 1;
	for (auto bi : bit[u]) {
		for (auto j : pos[bi]) {
			if (j == fa || j == u) continue;
			if (tag[j]) {
				ans = std::min(ans, dis[u] - dis[j] + 1);
				continue;
			} tag[j] = 1; dis[j] = dis[u] + 1; Dfs(j, u); tag[j] = 0;
		}
	}
}
