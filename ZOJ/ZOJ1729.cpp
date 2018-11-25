// ZOJ 1729
#include <cstdio>
const int MAXL = 1e5 + 10;

int len;
char S[MAXL];

void solve();

int main() {
	int t;
	scanf("%d", &t);
	for (; t--; ) solve();

	return 0;
}

void solve() {
	scanf("%d%s", &len, S);

	int p1 = 0, p2 = 1, k = 0;
	for (; p1 < len && p2 < len && k < len; ) {
		int tmp = S[(p1 + k) % len] - S[(p2 + k) % len];
		if (!tmp) ++k;
		else {
			if (tmp > 0) p1 += k + 1;
			else p2 += k + 1;
			if (p1 == p2) ++p2;
			k = 0;
		}
	}
	printf("%d\n", p1);
}
