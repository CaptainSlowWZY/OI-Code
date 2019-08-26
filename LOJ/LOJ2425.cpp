#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define fir first
#define sec second
#define pb push_back
#define FORTO(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)

typedef long long LL;
typedef std::pair<int, int> Pii;

const int kMaxn = 3e5 + 5, kLg = 19, kInf = 0x3f3f3f3f;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

int dis[kMaxn];

struct Edge {
	int to, cost, next;
} E[kMaxn << 1];
struct Trans {
	int u, v, c, l;
	void set_lca(int l_) { c = dis[u] + dis[v] - 2 * dis[l = l_]; }
	bool operator<(const Trans & t) const { return c < t.c; }
} T[kMaxn];

int n, m, ide;
int back[kMaxn], tag[kMaxn], F[kMaxn], vis[kMaxn];
std::vector<Pii> Q[kMaxn];

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar();
			register bool f = false; x = 0;
			for (; !isdigit(ch); f |= (ch == '-'), ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
	template <typename T>
		void Print(T x) {
			if (!x) return (void)(putchar('0'));
			if (x < 0) x = -x, putchar('-');
			register int arr[20], len = 0;
			for (; x; arr[len++] = x % 10, x /= 10);
			while (len) putchar(arr[--len] ^ '0');
		}
	template <>
		void Print(const char * buff) {
			for (register int i = 0; buff[i]; ++i) putchar(buff[i]);
		}
	template <typename T>
		inline void Println(T x) {
			Print(x), putchar('\n');
		}
}

bool Check(int);
void Tarjan(int, int);

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}
inline void AddEdge(int u, int v, int c) {
	E[++ide] = (Edge){v, c, back[u]}, back[u] = ide;
	E[++ide] = (Edge){u, c, back[v]}, back[v] = ide;
}

int main() {
	using fast_io::Read;
	Read(n), Read(m);
	for (int i = 1, u, v, c; i < n; i++) {
		Read(u), Read(v), Read(c);
		AddEdge(u, v, c);
	}
	for (int i = 0; i < m; i++) {
		Read(T[i].u), Read(T[i].v);
		Q[T[i].u].pb({T[i].v, i}), Q[T[i].v].pb({T[i].u, i});
	}

	for (int i = 1; i <= n; i++) F[i] = i;
	Tarjan(1, 0);
	std::sort(T, T + m);
	if (Check(0)) { puts("0"); return 0; }
	int lb = 0, ub = T[m - 1].c;
	for (int mid; ub - lb > 1; ) {
		mid = lb + ub >> 1;
		if (Check(mid)) ub = mid;
		else lb = mid;
	} printf("%d\n", ub);
	return 0;
}

int GetFa(int u) { return F[u] == u ? u : F[u] = GetFa(F[u]); }

void Tarjan(int u, int fa) {
	vis[u] = 1;
	FORTO(u) {
		if (v == fa) continue;
		dis[v] = dis[u] + E[e].cost;
		Tarjan(v, u);
	}
	for (auto & q : Q[u]) {
		if (vis[q.fir]) T[q.sec].set_lca(GetFa(q.fir));
	} F[u] = F[fa];
}

int Find(int u, int fa, int lim) {
	int res = 0, fae;
	FORTO(u) {
		if (v == fa) { fae = E[e].cost; continue; }
		res = std::max(res, Find(v, u, lim));
		tag[u] += tag[v], tag[v] = 0;
	} if (tag[u] == lim) res = std::max(res, fae);
	return res;
}

bool Check(int max) {
	if (max >= T[m - 1].c) return true;
	int k = std::upper_bound(T, T + m, (Trans){0, 0, max}) - T;
	for (int i = k; i < m; i++) {
		++tag[T[i].u], ++tag[T[i].v];
		tag[T[i].l] -= 2;
	} int del = Find(1, 0, m - k);
	return std::max(k ? T[k - 1].c : 0, T[m - 1].c - del) <= max;
}
