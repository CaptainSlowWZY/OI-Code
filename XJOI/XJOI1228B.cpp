#include <cstdio>
#include <vector>

#define pb push_back

const int kMaxn = 1e4;

int n;
int cnt[6], vis[6];
std::vector<int> ans;

int main() {
	ans.pb(0), ans.pb(1), ans.pb(2), ans.pb(3);
	ans.pb(4), ans.pb(5), ans.pb(2), ans.pb(3);
	cnt[1] = 1, cnt[2] = 2, cnt[3] = 2, cnt[4] = cnt[5] = 1;
	int cur = 8;
	for (int lp = 2, len, l2, t2, nr1, nr2; cur <= kMaxn; lp++) {
		t2 = l2 = lp - 1, nr1 = cur - 6 * (lp - 1), nr2 = cur - 1;
		for (len = lp * 6; len-- && cur <= kMaxn; ++cur) {
			std::fill(vis + 1, vis + 6, 0);
			if (~nr1) vis[ans[nr1]] = 1;
			if (~nr2) vis[ans[nr2]] = 1;
			if (len + 1 != lp * 6) vis[ans[cur - 1]] = 1;
			if (!len) vis[ans[cur - lp * 6 + 1]] = 1;
			int chs = -1;
			for (int i = 1; i <= 5; i++) {
				if (vis[i]) continue;
				if (chs == -1 || cnt[chs] > cnt[i]) chs = i;
			} ans.pb(chs), ++cnt[chs];
			if (!(--t2)) { nr2 = -1; }
			else { nr2 = nr1; ++nr1; }
			if (t2 < 0) t2 = l2;
		}
	}
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	} return 0;
}
