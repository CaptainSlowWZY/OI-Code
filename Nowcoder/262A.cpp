#include <algorithm>
#include <cstdio>

int d, n;
int A[129][129];

int main() {
	scanf("%d%d", &d, &n);
	for (int i = 0, x, y, k; i < n; i++) {
		scanf("%d%d%d", &x, &y, &k);
		A[x][y] = k;
	}
	
	int ans = 0, way = 1;
	for (int x = 0; x < 129; x++) {
		for (int y = 0; y < 129; y++) {
			int cnt = 0;
			for (int i = std::max(0, x - d);
					i <= std::min(128, x + d); i++) {
				for (int j = std::max(0, y - d);
						j <= std::min(128, y + d); j++)
					cnt += A[i][j];
			}
			if (cnt > ans) {
				ans = cnt, way = 1;
			} else if (cnt == ans) ++way;
		}
	} printf("%d %d\n", way, ans);
	return 0;
}
