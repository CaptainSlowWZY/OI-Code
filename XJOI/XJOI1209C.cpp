#pragma GCC optimize(2)
#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

typedef std::multiset<int> MSet;

const int kMaxn = 1e5 + 10;

int n, m;
MSet S[kMaxn];
int id[kMaxn], sum[kMaxn], L[kMaxn];
std::vector<int> G[kMaxn];
long long ans = 0;

void Insert(MSet & s, int & sum, int v_);
void Dfs(int u);

int main() {
	scanf("%d%d", &n, &m);
	int root = 1;
	for (int i = 1; i <= n; i++) id[i] = i;
	for (int i = 1, Bi, Ci; i <= n; i++) {
		scanf("%d%d%d", &Bi, &Ci, L + i);
		Insert(S[id[i]], sum[i], Ci);
		if (Bi) G[Bi].push_back(i);
		else root = i;
	}

	Dfs(root);

	printf("%lld\n", ans);
	return 0;
}

void Insert(MSet & s, int & sum, int v_) {
//	printf("  ins %d, sum %d, last %d\n", v_, sum, s.size() ? *s.rbegin() : -1);
	if (sum + v_ <= m) {
	//	puts("   ins1");
		s.insert(v_), sum += v_;
	} else if (s.size() && v_ < *s.rbegin()) {
		auto it = s.end();
	//	puts("   ins2");
		sum -= *(--it);
		s.erase(it), s.insert(v_);
		sum += v_;
	}
//	printf("  after ins %d, sum = %d\n", v_, sum);
}

void Merge(int u, int v) {
//	printf("\n merge %d, %d\n", u, v);
//	printf(" id[%d] %d, sum %d, sz %d\n id[%d] %d, sum %d, sz %d\n",
//			u, id[u], sum[u], (int)S[id[u]].size(), v, id[v], sum[v], (int)S[id[v]].size());
	if (S[id[u]].size() < S[id[v]].size()) {
//		puts("swap!");
		std::swap(id[u], id[v]);
		std::swap(sum[u], sum[v]);
	}
	MSet & hu = S[id[u]], & hv = S[id[v]];
	for (auto it = hv.begin(); it != hv.end(); ++it) {
//		printf(" insert %d -> %d heap\n", *it, id[u]);
		Insert(hu, sum[u], *it);
	}
}

void Dfs(int u) {
	for (auto v : G[u]) {
		Dfs(v);
		Merge(u, v);
	}
	ans = std::max(ans, (long long)S[id[u]].size() * L[u]);
}
