#include <cstdio>
#include <cstring>

const int kMaxn = 3e5 + 5;

char S[kMaxn];

int main() {
	scanf("%s", S);
	int len = strlen(S), nxt = len;
	long long ans = 0;
	for (int i = len - 1; i >= 0; i--) {
		for (int j = 1; i + j * 2 < nxt; j++) {
			if (S[i] == S[i + j] && S[i + j] == S[i + j * 2]) {
				nxt = i + j * 2;
				break;
			}
		}
		ans += len - nxt;
	}
	printf("%lld\n", ans);
	return 0;
}
