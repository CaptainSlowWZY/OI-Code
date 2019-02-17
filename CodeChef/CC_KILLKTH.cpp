// CodeChef KILLKTH
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

typedef long long LL;

const int LEN = 2e5 + 10;

int Q, lens;
LL G;
char S[LEN];

namespace SAM {
	void extend(int ch, int ps);
	void prep();
	int query(LL k);
}

int main() {
	scanf("%s%d", S, &Q);
	lens = strlen(S);
	for (int i = lens - 1; i >= 0; i--) SAM::extend(S[i] - 'a', i);
	SAM::prep();

	for (LL P, M; Q--; ) {
		scanf("%lld%lld", &P, &M);
		LL k = P * G % M + 1;
		int ans = SAM::query(k);
		putchar(ans);
		G += ans;
		putchar('\n');
	}

	return 0;
}

namespace SAM {
	typedef int IntAr[LEN << 1];
	int size = 1, last = 1, dfs_clock, A[LEN << 1][26];
	IntAr max, rsz, pos, par, dfn, seq;
	LL sum[LEN << 1];
	std::vector<int> G[LEN << 1];

	void extend(int ch, int ps) {
		int p = last, np = ++size;
		max[last = np] = max[p] + 1, rsz[np] = 1, pos[np] = ps;
		for (; p && !A[p][ch]; p = par[p]) A[p][ch] = np;
		if (!p) return (void)(par[np] = 1);
		int q = A[p][ch];
		if (max[q] == max[p] + 1) par[np] = q;
		else {
			int nq = ++size;
			max[nq] = max[p] + 1;
			pos[nq] = pos[q], par[nq] = par[q];
			par[np] = par[q] = nq;
			memcpy(A[nq], A[q], sizeof(A[q]));
			for (; A[p][ch] == q; p = par[p]) A[p][ch] = nq;
		}
	}
	void dfs(int u) {
		seq[++dfs_clock] = u;
		for (auto v : G[u]) {
			dfs(v);
			rsz[u] += rsz[v];
		}
	}
	inline LL calc(LL lb, LL ub) {
		return lb > ub ? 0 : (lb + ub) * (ub - lb + 1) >> 1;
	}
	inline bool cmp(int a, int b) {
		return S[pos[a] + max[par[a]]] < S[pos[b] + max[par[b]]];
	}
	void prep() {
		for (int i = 2; i <= size; i++) G[par[i]].push_back(i);
		for (int i = 1; i <= size; i++) std::sort(G[i].begin(), G[i].end(), cmp);
		dfs(1);
		for (int i = 1; i <= size; i++)
			sum[i] = sum[i - 1] + (LL)rsz[seq[i]] * calc(max[par[seq[i]]] + 1, max[seq[i]]);
	}
	int query(LL k) {
		int l = 0, r = size;
		for (int mid; r - l > 1; ) {
		//	[l, r)
			mid = l + r >> 1;
			if (sum[mid] < k) l = mid;
			else r = mid;
		}
		k -= sum[l];
		int cur = seq[l + 1], shrt = max[par[cur]] + 1;
		l = shrt - 1, r = max[cur];
		for (int mid; r - l > 1; ) {
		//	[l, r)
			mid = l + r >> 1;
			if ((LL)rsz[cur] * calc(shrt, mid) < k) l = mid;
			else r = mid;
		}
		k -= (LL)rsz[cur] * calc(shrt, l++);
		k %= l;
		if (!k) k = l;
		return S[pos[cur] + k - 1];
	}
}
