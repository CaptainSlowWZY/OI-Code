#include <algorithm>
#include <cstdio>

#define fir first
#define sec second

typedef std::pair<int, int> Pii;

const int kMaxn = 1e5 + 10;

int n;
int H[kMaxn];
Pii T[kMaxn];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &T[i].fir, &T[i].sec);
	}
	
	std::sort(T, T + n);
	for (int i = 0; i < n; i++) H[i] = T[i].sec;
	for (int i = 0; i < n; i++) {
		if (i) H[i] = std::min(H[i], T[i].fir - T[i - 1].fir);
		if (i + 1 < n) H[i] = std::min(H[i], T[i + 1].fir - T[i].fir);
	}

	int ans = 0;
	for (int i = 0; i < n; i++) ans += T[i].sec - H[i];
	printf("%d\n", ans);
	return 0;
}
