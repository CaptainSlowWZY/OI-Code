#include <algorithm>
#include <cstdio>
#include <vector>

typedef long long LL;

const int kMaxn = 1e4 + 5;

void Solve();

int main() {
	int T; scanf("%d", &T);
	for (int i = 1; i <= T; ++i) {
		printf("Case #%d: ", i);
		Solve();
	}
	return 0;
}

int n, m, k;
int A[kMaxn], vis[kMaxn], que[kMaxn << 1];
std::vector<int> cir;
LL s, spr[kMaxn << 1];
 
LL Gao(int lim, int len);

void Solve() {
	scanf("%d%lld%d%d", &n, &s, &m, &k);
	for (int i = 0; i < n; ++i) scanf("%d", A + i);
	std::fill(vis, vis + n, 0);
	LL ans = 0x3f3f3f3f3f3f3f3f;
	for (int i = 0, len, l2, t; i < n; ++i) {
		if (vis[i]) continue;
		cir.clear();
		LL sum = 0, tmp;
		for (int j = i; !vis[j]; j = (j + k) % n) {
			vis[j] = 1; cir.push_back(A[j]); sum += A[j];
		} len = (int)cir.size(), l2 = len << 1;
		for (int i = 0; i < len; ++i)
			spr[i + 1] = spr[i] + cir[i];
		for (int i = 0; i < len; ++i)
			spr[len + i + 1] = spr[len + i] + cir[i];
		tmp = Gao(std::min(m, len), l2);
		if (sum > 0 && m > len) {
			t = m / len;
			tmp = std::max(tmp, t * sum + Gao(m % len, l2));
			tmp = std::max(tmp, --t * sum + Gao(std::min(m, len), l2));
		}
		ans = std::min(ans, std::max(0ll, s - tmp));
	} printf("%lld\n", ans);
}

LL Gao(int lim, int len) {
	if (!lim) return 0;
	static int que[kMaxn << 1];
	int hd = 0, tl = 0; que[tl++] = 0;
	LL res = 0;
	for (int i = 1; i <= len; ++i) {
		while (hd < tl && que[hd] < i - lim) ++hd;
		res = std::max(res, spr[i] - spr[que[hd]]);
		while (hd < tl && spr[i] < spr[que[tl - 1]]) --tl;
		que[tl++] = i;
	} return res;
}
