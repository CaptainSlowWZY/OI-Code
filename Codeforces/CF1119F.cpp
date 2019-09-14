#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

#define fir first
#define sec second
#define PB push_back
	
typedef long long LL;
typedef std::pair<int, int> Pii;

const int kMaxn = 250005;

class Heap {
private:
	std::priority_queue<LL> dat, ers;
	void mktop() {
		while (dat.size() && ers.size() &&
			dat.top() == ers.top()) {
			dat.pop(); ers.pop();
		}
	}
public:
	LL sum;
	int sz;
	int size() { return sz; }
	LL top() { mktop(); return dat.top(); }
	void erase(LL x) { ers.push(x); sum -= x; --sz; }
	void pop() {
		mktop();
		if (!dat.empty()) { sum -= dat.top(); dat.pop(); --sz; }
	}
	void push(LL x) { dat.push(x); sum += x; ++sz; }
	bool empty() { mktop(); return dat.empty(); }
} H[kMaxn];

int n, x;
int deg[kMaxn], vis[kMaxn];
LL DP[kMaxn][2];
Pii D[kMaxn];
std::vector<Pii> G[kMaxn];

inline void AddEdge(int u, int v, int c) {
	G[u].PB({v, c}), ++deg[u];
	G[v].PB({u, c}), ++deg[v];
}
inline bool CmpDeg(const Pii & a, const Pii & b) {
	return deg[a.fir] > deg[b.fir];
}
void Dfs(int u, int fa);
void Rls(int u);

int main() {
	scanf("%d", &n);
	LL ans = 0;
	for (int i = 1, a, b, c; i < n; i++) {
		scanf("%d%d%d", &a, &b, &c);
		AddEdge(a, b, c); ans += c;
	}
	for (int i = 1; i <= n; i++) {
		D[i] = {deg[i], i};
		std::sort(G[i].begin(), G[i].end(), CmpDeg);
	}
	std::sort(D + 1, D + n + 1);
	int j = 1;
	printf("%lld", ans);
	for (x = 1; x < n; x++) {
		ans = 0;
		while (j <= n && D[j].fir <= x) Rls(D[j++].sec);
		for (int k = j, u; k <= n; k++) {
			if (vis[u = D[k].sec] != x) {
				Dfs(u, 0); ans += DP[u][0];
			}
		}
		printf(" %lld", ans);
	}
	putchar('\n');
	return 0;
}

void Dfs(int u, int fa) {
	static std::vector<LL> dpv, buf;
	Heap & hap = H[u];
	int num = deg[u] - x;
	LL sum = 0;
	vis[u] = x;
	while (hap.size() > num) hap.pop();
	for (auto & e : G[u]) {
		int v = e.fir;
		if (v == fa) continue;
		if (deg[v] <= x) break;
		Dfs(v, u);
	} dpv.clear(); buf.clear();
	for (auto & e : G[u]) {
		int v = e.fir;
		if (v == fa) continue;
		if (deg[v] <= x) break;
		LL tmp = DP[v][1] + e.sec - DP[v][0];
		if (tmp <= 0) {
			sum += DP[v][1] + e.sec; --num;
		} else {
			sum += DP[v][0]; hap.push(tmp), dpv.PB(tmp);
		}
	}
	for (; !hap.empty() && hap.size() > num; hap.pop())
		buf.PB(hap.top());
	DP[u][0] = hap.sum + sum;
	for (; !hap.empty() && hap.size() > num - 1; hap.pop())
		buf.PB(hap.top()); 
	DP[u][1] = hap.sum + sum;
	for (auto i : buf) hap.push(i);
	for (auto i : dpv) hap.erase(i);
}

void Rls(int u) {
	for (auto & e : G[u]) {
		int v = e.fir;
		if (deg[v] <= x) break;
		H[v].push(e.sec);
	}
}
