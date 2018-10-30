// XJOI 3857
#include <cstdio>
#include <cstring>

typedef long long LL;

const int MOD = 1e9 + 7;

char str[60];

struct Info {
	int cnt[3];
	void add(int & x, int d) const {
		if ((x += d) >= MOD) x-= MOD;
	}
	Info() {
		memset(cnt, 0, sizeof cnt);
	}
	Info(int n_) {
		memset(cnt, 0, sizeof cnt);
		cnt[n_ % 3] = 1;
	}
	Info operator+(const Info & i) const {
		Info ret;
		for (int r1 = 0; r1 < 3; r1++) add(ret.cnt[r1], (cnt[r1] + i.cnt[r1]) % MOD);
		for (int r1 = 0; r1 < 3; r1++)
			for (int r2 = 0; r2 < 3; r2++) add(ret.cnt[(r1 + r2) % 3], LL(cnt[r1]) * i.cnt[r2] % MOD);
		return ret;
	}
};

Info dfs(int l, int r) {
	if (r - l <= 1)
		return Info(str[l] ^ '0');
	int mid = l + r >> 1;
	return dfs(l, mid) + dfs(mid, r);
}

int main() {
	scanf("%s", str);
	printf("%d\n", dfs(0, strlen(str)).cnt[0]);
}

// AC!!!
