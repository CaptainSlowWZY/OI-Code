#include <cstdio>
#include <set>

int n;
int SG[25], A[25];
std::set<int> S;

int main() {
	SG[0] = 0;
	for (int i = 1; i <= 21; i++) {
		S.clear();
		for (int j = 0; j < i; j++) {
			for (int k = j; k < i; k++) S.insert(SG[j] ^ SG[k]);
		}
		for (int j = 0; ; j++) {
			if (!S.count(j)) {
				SG[i] = j;
				break;
			}
		}
	}

	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		int sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", A + i);
			if (A[i] & 1) sum ^= SG[n - i];
		}
		if (sum) {
			int cnt = 0;
			for (int i = 1; i < n; i++) {
				if (!A[i]) continue;
				for (int j = i + 1; j <= n; j++) {
					for (int k = j; k <= n; k++) {
						if (sum ^ SG[n - i] ^ SG[n - j] ^ SG[n - k])
							continue;
						if (!cnt)
							printf("%d %d %d\n", i - 1, j - 1, k - 1);
						++cnt;
					}
				}
			}
			printf("%d\n", cnt);
		} else puts("-1 -1 -1\n0");
	}
	return 0;
}
