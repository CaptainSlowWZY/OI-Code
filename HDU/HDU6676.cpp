#include <cstdio>
#include <cstring>
#include <queue>

const int kLen = 1 << 21;

int n;
char S[kLen + 5];
std::priority_queue<int> hap;

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%s", S);
		n = strlen(S);
		int ans = 0, lst = -1;
		for (int i = 0; i < n; i++) {
			if (S[i] != '^') continue;
			if (lst + 1 == i) ans ^= 1;
			else hap.push(i - lst);
			lst = i;
		}
		if (lst + 1 == n) ans ^= 1;
		else hap.push(n - lst);
		for (int i = 21, pw; i >= 0 && !hap.empty(); i--) {
			pw = 1 << i;
			if (hap.top() >= pw) {
				if (hap.top() > pw) hap.push(hap.top() - pw);
				hap.pop(); ans ^= pw;
			}
		} int rem = 0;	
		for (; !hap.empty(); hap.pop()) rem ^= hap.top();
		ans ^= rem & 1;
		printf("%d\n", ans);
	} return 0;
}
