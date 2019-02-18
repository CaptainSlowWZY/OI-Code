// BZOJ 4199
// NOI 2015
#include <cstdio>
#include <cstring>
#include <algorithm>

const int LEN = 3e5 + 5, INF = 0x7f7f7f7f;

int N, A[LEN];
long long ans1[LEN], ans2[LEN], NINF64;
char S[LEN];

namespace SAM {
	void extend(int ch, int v_);
	void solve();
}
template <typename T>
inline void umin(T & x, const T & y) { x > y ? x = y : 0; }
template <typename T>
inline void umax(T & x, const T & y) { x < y ? x = y : 0; }

int main() {
	scanf("%d%s", &N, S);
	for (int i = 0; i < N; i++) scanf("%d", A + i);

	for (int i = N - 1; i >= 0; i--) SAM::extend(S[i] - 'a', A[i]);
	SAM::solve();

	for (int i = 0; i < N; i++) printf("%lld %lld\n", ans1[i], ans2[i] != NINF64 ? ans2[i] : 0);
	return 0;
}

namespace SAM {
	typedef int IntAr[LEN << 1];
	int size = 1, last = 1, A[LEN << 1][26], DP[LEN << 1][2];
	IntAr max, tot, par, cnt, id;

	void extend(int ch, int v_) {
		int p = last, np = ++size;
		max[last = np] = max[p] + 1, tot[np] = 1, DP[np][0] = DP[np][1] = v_;
		for (; p && !A[p][ch]; p = par[p]) A[p][ch] = np;
		if (!p) par[np] = 1;
		else {
			int q = A[p][ch];
			if (max[q] == max[p] + 1) par[np] = q;
			else {
				int nq = ++size;
				max[nq] = max[p] + 1;
				par[nq] = par[q], DP[nq][0] = INF, DP[nq][1] = -INF;
				par[np] = par[q] = nq;
				memcpy(A[nq], A[q], sizeof(A[q]));
				for (; A[p][ch] == q; p = par[p]) A[p][ch] = nq;
			}
		}
	}
	void _debug() {
		for (int i = 1; i <= size; i++) {
			printf(" A%d: ", i);
			printf(" parent->%d, tot = %d, max = %d\n", par[i], tot[i], max[i]);
			for (int c = 0; c < 26; c++)
				if (A[i][c]) printf("  --%c-> %d\n", 'a' + c, A[i][c]);
		}
	}
	void solve() {
#ifndef ONLINE_JUDGE
		_debug();
#endif
//		DP[1][0] = INF, DP[1][1] = -INF;
		for (int i = 1; i <= size; i++) ++cnt[max[i]];
		for (int i = 1; i <= N; i++) cnt[i] += cnt[i - 1];
		for (int i = 1; i <= size; i++) id[cnt[max[i]]--] = i;
		memset(ans2, 0x80, sizeof ans2);
		NINF64 = ans2[0];
		for (int i = size, cur, fa; i > 0; i--) {
			cur = id[i], fa = par[cur];
			ans1[max[fa]] += (long long)tot[fa] * tot[cur];
			tot[fa] += tot[cur];
			if (DP[cur][1] != -INF && DP[fa][1] != -INF) umax(ans2[max[fa]], (long long)DP[cur][1] * DP[fa][1]);
			if (DP[cur][0] != INF && DP[fa][0] != INF) umax(ans2[max[fa]], (long long)DP[cur][0] * DP[fa][0]);
			umax(DP[fa][1], DP[cur][1]);
			umin(DP[fa][0], DP[cur][0]);
		}
		for (int i = N; i > 0; i--) {
			ans1[i - 1] += ans1[i];
			umax(ans2[i - 1], ans2[i]);
		}
	}
}
