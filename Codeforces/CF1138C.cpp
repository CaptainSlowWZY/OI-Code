#include <bits/stdc++.h>

int n, m, a[1010][1010];
std::vector<int> row[1010], col[1010];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &a[i][j]);
			row[i].push_back(a[i][j]);
			col[j].push_back(a[i][j]);
		}
	}

	for (int i = 0; i < n; i++) {
		std::sort(row[i].begin(), row[i].end());
		row[i].erase(std::unique(row[i].begin(), row[i].end()), row[i].end());
	}
	for (int i = 0; i < m; i++) {
		std::sort(col[i].begin(), col[i].end());
		col[i].erase(std::unique(col[i].begin(), col[i].end()), col[i].end());
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int idr = std::lower_bound(row[i].begin(), row[i].end(), a[i][j]) - row[i].begin(),
				idc = std::lower_bound(col[j].begin(), col[j].end(), a[i][j]) - col[j].begin();
			int myid = std::max(idr, idc);
//			printf("i = %d, j = %d, myid = %d, idr = %d, idc = %d\n", i, j, myid, idr, idc);
			printf("%d ", myid + std::max((int)row[i].size() - idr, (int)col[j].size() - idc));
		}
		putchar('\n');
	}
	return 0;
}
