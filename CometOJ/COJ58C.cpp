#include <algorithm>
#include <cstdio>

#define int LL

typedef long long LL;

const int kMaxn = 1e5 + 10;
const LL kInf64 = 0x7f7f7f7f7f7f7f7f;

int n, k;
int A[kMaxn], B[kMaxn], C[kMaxn];
LL sumc[kMaxn], ans[kMaxn];

signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%lld%lld", A + i, B + i);	
		if (i) {
			C[i] = A[i] * B[i - 1];
			sumc[i] = sumc[i - 1] + C[i];
		}
	}
	if (n == 2) {
		printf("%lld\n", std::min(sumc[1],
					std::min(sumc[1] * k, sumc[1] * k * k)));
		return 0;
	}
	ans[1] = sumc[n - 1] - sumc[1] + k * C[1];
//	printf("ans1 %lld\n", ans[1]);
	LL minprv = kInf64, minans = std::min(sumc[n - 1], ans[1]), cur;
	for (int i = 2; i < n; i++) {
		if (i == 2) {
			ans[1] = ans[i - 1] - C[1] - C[2] +
				k * k * C[1] + k * C[2];
		} else if (i + 1 == n) {
			ans[1] = ans[1] - k * C[i - 1] - C[i] + 
				k * k * (C[i - 1] + C[i]);
			ans[i - 1] = ans[i - 1] - C[i] + k * k * C[i];	
			minprv = minprv - C[i] - k * C[i - 1] +
				k * k * (C[i - 1] + C[i]);
		} else {
			ans[1] = ans[1] - k * C[i - 1] - C[i] +
				k * k * C[i - 1] + k * C[i];
			ans[i - 1] = ans[i - 1] - C[i] + k * C[i];
			minprv = minprv - k * C[i - 1] - C[i] +
				k * k * C[i - 1] + k * C[i];
		}
	//	printf(" ans %d=%lld\n", i - 1, ans[i - 1]);
		ans[i] = sumc[i - 1] + sumc[n - 1] - sumc[i] + k * C[i];
		cur = std::min(std::min(ans[1], minprv),
				std::min(ans[i], ans[i - 1]));
		minans = std::min(minans, cur);
		if (i > 2) minprv = std::min(minprv, ans[i - 1]);
	} printf("%lld\n", minans);
	return 0;
}
