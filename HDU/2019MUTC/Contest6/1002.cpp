#include <algorithm>
#include <cstdio>

#define fir first
#define sec second

const int kMaxn = 5e4 + 10, kInf = 0x3f3f3f3f;

typedef int IAr[kMaxn];
typedef std::pair<int, int> Pii;

int n, len;
IAr A, B, avi, ans, inq;

void Lis();

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", A + i);
		for (int i = 0; i < n; i++) {
			scanf("%d", B + i); // unfreeze
			avi[i] = 1, --B[i];;
		}

		Lis(); ans[n - 1] = len;
		for (int i = n - 1; i; i--) {
			avi[B[i]] = 0;
			if (inq[B[i]]) Lis();
			ans[i - 1] = len;
		}
		for (int i = 0; i < n; i++)
			printf("%d%c", ans[i], i + 1 == n ? '\n' : ' ');
	} return 0;
}

void Lis() {
	static Pii DP[kMaxn];
	static IAr prv;
	std::fill(DP + 1, DP + n + 1, Pii(kInf, 0));
	DP[0] = Pii(0, -1), len = 0;
	for (int i = 0; i < n; i++) {
		if (!avi[i]) continue;
		auto p = std::upper_bound(DP, DP + len + 1, Pii(A[i], i));
		if (p == DP + len + 1) ++len;
		prv[i] = (p - 1)->sec;
		*p = std::min(*p, Pii(A[i], i));
	}
	std::fill(inq, inq + n, 0);
	for (int i = DP[len].sec; ~i; i = prv[i]) inq[i] = 1;
}
