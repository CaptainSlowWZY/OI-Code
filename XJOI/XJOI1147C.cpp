#include <cstdio>
#include <algorithm>

const int kMaxn = 1e6 + 10;

typedef long long LL;
typedef LL LAr[kMaxn];

int n, type;
LAr A, B, C, ansa, ansb;

int main() {
	scanf("%d%d", &n, &type);
	for (int i = 1; i < n; i++) scanf("%lld", A + i);
	for (int i = 1; i < n; i++) scanf("%lld", B + i);
	
	if (type) {
		for (int i = 0; i < n; i++) scanf("%lld", C + i);
		ansa[0] = 0, ansb[0] = C[0];
		for (int i = 1; i < n; i++) {
			ansa[i] = A[i] - ansa[i - 1];
			ansb[i] = std::max(C[i] - ansa[i], B[i] - ansb[i - 1]);
		}
		for (int i = 0; i < n; i++) {
			printf("%lld%c", ansa[i], i + 1 == n ? '\n' : ' ');
		}
		for (int i = 0; i < n; i++) {
			printf("%lld%c", ansb[i], i + 1 == n ? '\n' : ' ');
		}
	} else {
		if (n & 1) {
			puts("bukejiedewodeyiqie");
			return 0;
		}
		LL last = 0;
		printf("0 ");
		for (int i = 1; i < n; i++) {
			printf("%lld ", last = A[i] - last);
		}
		last = 0;
		printf("\n0 ");
		for (int i = 1; i < n; i++) {
			printf("%lld ", last = B[i] - last);
		}
	}
	return 0;
}
