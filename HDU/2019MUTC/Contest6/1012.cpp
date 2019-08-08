#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

#define fir first
#define sec second

typedef std::pair<int, int> Pii;
typedef long long LL;

const int kMaxn = 1e5 + 10;

int n;
int fa[kMaxn], deg[kMaxn], H[kMaxn];
std::priority_queue<Pii> hap;

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			if (fa[i] = i >> 1) ++deg[fa[i]];
			scanf("%d", H + i);
		}
		for (int i = 1; i <= n; i++) {
			if (!deg[i]) hap.push(Pii(H[i], i));
		} LL ans1 = 0, ans2 = 0;
		for (int f, t = 0; !hap.empty(); t++) {
			Pii cur = hap.top(); hap.pop();
		//	printf(" t %d, val %d, id %d\n", t, cur.fir, cur.sec);
			if (t & 1) ans2 += cur.fir;
			else ans1 += cur.fir;
			if ((f = fa[cur.sec]) && !(--deg[f]))
				hap.push(Pii(H[f], f));
		} printf("%lld %lld\n", ans1, ans2);
	} return 0;
}
