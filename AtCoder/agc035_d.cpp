#include <cstdio>
#include <map>

typedef long long LL;

const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

struct Stat {
	int l, xl, r, xr;
	bool operator<(const Stat & s) const {
		return l != s.l ? l < s.l :
			(r != s.r ? r < s.r : 
			 (xl != s.xl ? xl < s.xl : xr < s.xr));
	}
};

int n;
int A[20];
std::map<Stat, LL> DP;

LL Solve(int l, int xl, int r, int xr);

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", A + i);

	printf("%lld\n", Solve(0, 1, n - 1, 1) + A[0] + A[n - 1]);
	return 0;
}

LL Solve(int l, int xl, int r, int xr) {
	if (r - l <= 1) return 0;
	Stat cur = (Stat){l, xl, r, xr};
	auto it = DP.find(cur);
	if (it != DP.end()) return it->second;
	LL res = kInf64;
	for (int i = l + 1; i < r; i++) {	
		res = std::min(res, Solve(l, xl, i, xl + xr) +
							Solve(i, xl + xr, r, xr) +
							(LL)A[i] * (xl + xr));
	}
	return DP[cur] = res;
}
