#include <algorithm>
#include <cstdio>
#include <cstring>
#include <bitset>

int n, m;
int SG[205][205];

int Dfs(int, int);

int main() {
	memset(SG, 0xff, sizeof SG);
	while (~scanf("%d%d", &n, &m)) {
		if (n > m) std::swap(n, m);
		puts(Dfs(n, m) ? "WIN" : "LOSE");	
	}
	return 0;
}

int Dfs(int x, int y) {
	if (x > y) std::swap(x, y);
	if (~SG[x][y]) return SG[x][y];
	std::bitset<205> flag;
	for (int i = 2; i <= x - i; ++i)
		flag[Dfs(i, y) ^ Dfs(x - i, y)] = 1;
	for (int i = 2; i <= y - i; ++i)
		flag[Dfs(x, i) ^ Dfs(x, y - i)] = 1;
	int i = 0;
	while (flag[i]) ++i;
	return SG[x][y] = i;
}
