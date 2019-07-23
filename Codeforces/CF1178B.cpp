#include <cstdio>
#include <cstring>

const int kMaxn = 1e6 + 10;

char S[kMaxn];
int begin[kMaxn], end[kMaxn];

int main() {
	scanf("%s", S);
	int len = strlen(S);
	if (len < 5) {
		puts("0");
		return 0;
	}
	int tots = 0;
	for (int i = len - 1; i >= 0; i--) {
		if (S[i] != S[i + 1]) {
			if (S[i] == 'o') {
				if (tots) begin[tots - 1] = i + 1;
			} else end[tots++] = i;
		}
	}
	int sum = 0;
	for (int i = 0; i < tots; i++) sum += end[i] - begin[i];
	int sum2 = 0;
	long long ans = 0;
	for (int i = 0, k = tots - 1; i < len; i++) {
		if (S[i] == 'v') continue;
		for (; k >= 0 && end[k] < i; --k) {
			sum -= end[k] - begin[k];
			sum2 += end[k] - begin[k];
		}
		ans += 1ll * sum * sum2;
	}

	printf("%lld\n", ans);
	return 0;
}
