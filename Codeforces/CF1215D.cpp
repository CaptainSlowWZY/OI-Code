#include <algorithm>
#include <cstdio>

const char kBc[] = {'B', 'i', 'c', 'a', 'r', 'p', '\0'};
const char kMo[] = {'M', 'o', 'n', 'o', 'c', 'a', 'r', 'p', '\0'};
int n;
char D[200005];

int main() {
	scanf("%d%s", &n, D);
	int e1, e2, s1, s2;
	for (int i = e1 = e2 = s1 = s2 = 0; i < n / 2; i++) {
		if (D[i] == '?') { ++e1; continue; }	
		s1 += D[i] ^ '0';
	}
	for (int i = n / 2; i < n; i++) {
		if (D[i] == '?') { ++e2; continue; }
		s2 += D[i] ^ '0';
	}
	if (s1 > s2) {
		std::swap(s1, s2);
		std::swap(e1, e2);
	}
	int t = std::min(e1, e2);
	e1 -= t, e2 -= t;
	int each = e1 + e2 >> 1;
	if (!e1) {
		if (!e2) {
			puts(s1 == s2 ? kBc : kMo);
		} else puts(kMo);
	} else {
		if (s1 + each * 9 == s2)
			puts(kBc);
		else
			puts(kMo);
	}
	return 0;
}
