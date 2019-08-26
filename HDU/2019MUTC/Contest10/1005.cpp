#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>

#define fir first
#define sec second

typedef long long LL;
typedef std::pair<LL, LL> Pii;

const int kMaxn = 1e5 + 5;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

int n;
Pii A[kMaxn];
std::map<LL, int> B;

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		assert(B.empty());
		for (int i = 0; i < n; i++) {
			scanf("%lld%lld", &A[i].fir, &A[i].sec);
			++B[A[i].sec];
		}
		std::sort(A, A + n, std::greater<Pii>());
		LL ub = -1, ans = kInf64;
		for (int i = 0; i < n; i++) {
			if (!(--B[A[i].sec])) B.erase(A[i].sec);
			if (ub >= A[i].fir) {
				ans = std::min(ans, ub - A[i].fir);
			} else if (B.empty()) {
				ans = std::min(ans, A[i].fir - ub);
			} else {
				auto it = B.lower_bound(A[i].fir);
				if (~ub) ans = std::min(ans, A[i].fir - ub);
				if (it != B.end())
					ans = std::min(ans, it->fir - A[i].fir);
				if (it != B.begin()) 
					ans = std::min(ans, A[i].fir - (--it)->fir);
			} ub = std::max(ub, A[i].sec);
		}
		assert(ans >= 0);
		printf("%lld\n", ans);
	} return 0;
}
