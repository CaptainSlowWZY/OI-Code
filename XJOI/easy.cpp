// easy
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <algorithm>
#include <utility>
#include <set>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define rg register
#define gch getchar
#define forsn(u) for (rg int v, e = last[u]; e; e = E[e].next)
#define fir first
#define sec second

const int MAXN = 6e5 + 10;

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef std::set<Pii> MySt;
typedef MySt::iterator Iter;
typedef int Arr[MAXN];

struct Edge {
	int to, next;
} E[MAXN << 1];

int N, tote;
LL ans, total[MAXN];
Arr last, pos, id;
MySt intr[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x);
}
inline void add_edge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}
void dfs(int u, int fa, int dep);

int main() {
	using FastIO::read;

	read(N);
	for (int i = 1, ui, vi; i < N; i++) {
		read(ui), read(vi);
		add_edge(ui, vi);
	}
	for (int i = 0, pi; i < N; i++) {
		read(pi);
		pos[pi] = i;
	}

	dfs(1, 0, 1);
	
	printf("%lld\n", ans);
	return 0;
}

LL calc(Pii p) {
	LL len = p.sec- p.fir + 1;
	return len * (len + 1) >> 1;
}

void merge(int & i1, int i2) {
	if (intr[i1].size() < intr[i2].size()) std::swap(i1, i2);
	MySt & sur = intr[i2], & trg = intr[i1];
	LL & trgt = total[i1];
	for (auto p : sur) {
		Iter pre = trg.lower_bound(p), nxt = trg.upper_bound(p);
		if (pre == trg.begin() || (--pre)->sec + 1 != p.fir) {
		//	prefix not found
			if (nxt == trg.end() || nxt->fir != p.sec + 1) {
			//	next not found
				trg.insert(p);
				trgt += calc(p);
			}
			else {
				p.sec = nxt->sec;
				trgt -= calc(*nxt), trg.erase(nxt);
				trgt += calc(p), trg.insert(p);
			}
		}
		else {
		// able to merge with the prefix
			if (nxt == trg.end() || nxt->fir != p.sec + 1) {
			// next not found
				p.fir = pre->fir;
				trgt -= calc(*pre), trg.erase(pre);
				trgt += calc(p), trg.insert(p);
			}
			else {
				p = Pii(pre->fir, nxt->sec);
				trgt -= calc(*nxt) + calc(*pre), trg.erase(nxt), trg.erase(pre);
				trgt += calc(p), trg.insert(p);
			}
		}
	}
}

void dfs(int u, int fa, int dep) {
	id[u] = u;
	intr[u].insert(Pii(pos[u], pos[u])), total[u] = 1;
	LL sumfv = 0;
	forsn(u) {
		if ((v = E[e].to) == fa) continue;
		dfs(v, u, dep + 1);
		sumfv += total[id[v]];
		merge(id[u], id[v]);
	}
	ans += (total[id[u]] - sumfv) * dep;
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = gch());
		}
}
