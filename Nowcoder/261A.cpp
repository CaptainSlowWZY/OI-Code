#include <cstdio>

const int kMaxn = 1e5 + 5;

int n, top;
int H[kMaxn], S[kMaxn];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", H + i);

	long long ans = 0;
	for (int i = 0; i < n; i++) {
		if (!top || H[i] > S[top - 1]) {
			if (top) ans += H[i] - S[top - 1];
			else ans += H[i];
			S[top++] = H[i];
		} else {
			while (top && H[i] <= S[top - 1]) --top;
			S[top++] = H[i];
		}
	} printf("%lld\n", ans);
	return 0;
}
