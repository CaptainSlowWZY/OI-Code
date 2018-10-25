// XJOI 3872
// Source: SRM515 DIV1
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstring>
#include <vector>

#ifdef LOCAL
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif
#define pb push_back

typedef std::vector<int> Veci;
typedef int IntAr[30];

int N, M;
IntAr flag, prsn, prz;
double prob[30], DP[26][26][(1 << 12) + 1];
char buff[60];

int read(char *&fir);
double dfs(int, int, int);

int main() {
	scanf("%d%d", &N, &M);
	getchar();
	int rk = 0;
	for (int i = 0; i < 23; i++) flag[i] = -2;
	for (int i = 0; i < N; i++) {
		fgets(buff, 60, stdin);
		int len = strlen(buff), prfs = 0;
		char *fir = buff;
		Veci tv;
		for (buff[len-- - 1] = '\0'; fir != buff + len; ) {
			int tmp = read(fir), ti, ci, pi;
			debug("!tmp=%d\n", tmp);
			if (~tmp) ti = tmp;
			else break;
			if (~(tmp = read(fir))) ci = tmp;
			else break;
			if (~(tmp = read(fir))) pi = tmp;
			else break;
			prsn[ti] = i, prz[ti] = ci, prob[ti] = (double)pi / (100 - prfs);
			debug("time: %d, person: %d, prize: %d, probility: %d%%=%.2f\n", ti, i, ci, pi, prob[ti]);
			tv.pb(ti), prfs += pi;
		}
		debug("tv's size=%d\n", (int)tv.size());
		if (tv.size() == 1) flag[tv[0]] = -1;
		if (tv.size() > 1) {
		   for (auto ti : tv) flag[ti] = rk; 
		   ++rk;
		}
	}
	for (int i = 0; i <= 24; i++)
		for (int j = 0; j <= 24; j++)
			for (int m = (1 << 12) - 1; m >= 0; --m) DP[i][j][m] = -1;
	printf("%.9f\n", dfs(0, M, 0));
	return 0;
}

int read(char *&fir) {
	int x = 0;
	for (; *fir && !isdigit(*fir); ++fir);
	if (!(*fir)) return -1;
	for (; *fir && isdigit(*fir); ++fir) x = (x << 3) + (x << 1) + (*fir ^ '0');
	for (; *fir && !isdigit(*fir); ++fir);
	return x;
}

inline bool eql(double x, double y) {
	return fabs(x - y) < 1e-6;
}

double dfs(int tm, int lft, int mask) {
	// flag[time] : -1 - the coming man only come this time; -2 - no one comes
	if (tm == 24 || !lft) return 0;
	if (~flag[tm] && (flag[tm] >= 0 && mask >> flag[tm] & 1 || flag[tm] == -2)) return dfs(tm + 1, lft, mask);
	if (!eql(DP[tm][lft][mask], -1)) return DP[tm][lft][mask];
	if (flag[tm] == -1) return DP[tm][lft][mask] = prob[tm] * std::max(dfs(tm + 1, lft - 1, mask) + prz[tm], dfs(tm + 1, lft, mask))
							 + (1 - prob[tm]) * dfs(tm + 1, lft, mask);
	return DP[tm][lft][mask] = prob[tm] * std::max(dfs(tm + 1, lft - 1, mask | 1 << flag[tm]) + prz[tm], dfs(tm + 1, lft, mask | 1 << flag[tm]))
							 + (1 - prob[tm]) * dfs(tm + 1, lft, mask);
}

// AC!!!
