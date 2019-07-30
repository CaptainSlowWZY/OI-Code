#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>

#define fir first
#define sec second
#define pb push_back
#define rg register
#define gch getchar
#define pch putchar
#define FORTO(_) for (int e = back[_], v = E[e].to; e; \
		v = E[e = E[e].next].to)
#define BACK(_) for (int _ = T; _ != S; _ = prv[_])

const int kMaxn = 2010, kMaxm = 2e6 + 6000, kInf = 0x3f3f3f3f;

typedef int IAr[kMaxn << 1];
typedef std::pair<int, int> Pii;
/*
struct Edge {
	int to, capt, cost, next;
} E[kMaxm << 1];*/
struct Edge {
	int to, capt, cost, rev;
};

int n, m, S, T, S1, tote, k;
int A[kMaxn];
IAr prv, prve, dis, H;
std::vector<Edge> G[kMaxn << 1];

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			rg char ch = gch();
			rg bool f = false; x = 0;
			for (; !isdigit(ch); f |= (ch == '-'), ch = gch());
			for (; isdigit(ch); ch = gch())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
}
inline void AddEdge(int u, int v, int w, int f) {
	//    printf(" from %d to %d, (%d, %d)\n", u, v, w, f);
//	E[++tote] = (Edge){v, w, f, back[u]}, back[u] = tote;
//	E[++tote] = (Edge){u, 0, -f, back[v]}, back[v] = tote;
	G[u].pb((Edge){v, w, f, (int)G[v].size()});
	G[v].pb((Edge){u, 0, -f, (int)G[u].size() - 1});
}
void Mcf(int & cost);
template <typename T>
void Fill(T ar[], int fir, int lst, T val);

int main() {
	using fast_io::Read;
	int t;
	for (Read(t); t--; ) {
		Read(n), Read(k);
		for (int i = 1; i <= n; i++) Read(A[i]);

	//	tote = 1;
		S = 0, T = (S1 = 2 * n + 1) + 1;
	//	Fill(back, 0, T, 0);
		for (int i = 0; i <= T; i++) G[i].clear();
		AddEdge(S, S1, k, 0);
		for (int i = 1; i <= n; i++) {
			AddEdge(S1, i, 1, 0);
			AddEdge(i, n + i, 1, -A[i]);
			AddEdge(n + i, T, 1, 0);
			for (int j = 1; j < i; j++) {
				if (A[j] > A[i]) continue;
				AddEdge(n + j, i, 1, 0);
			}
		}
		int ans;
		Mcf(ans);
		printf("%d\n", -ans);
	}
	return 0;
}

template <typename T>
void Fill(T ar[], int fir, int lst, T val) {
	for (int i = fir; i <= lst; i += 4) {
		ar[i] = val, ar[i + 1] = val;
		ar[i + 2] = val, ar[i + 3] = val;
	}
}

bool Dijkstra() {
	std::priority_queue<Pii, std::vector<Pii>,
		std::greater<Pii> > hap;
//	memset(prv, 0xff, sizeof prv);
	Fill(prv, 0, T, -1);
//	memset(dis, 0x3f, sizeof dis);
	Fill(dis, 0, T, kInf);

	dis[S] = 0, hap.push(Pii(dis[S], S));
	for (Pii cur; !hap.empty(); ) {
		cur = hap.top(), hap.pop();
		if (dis[cur.sec] < cur.fir) continue;
//		FORTO(cur.sec) {
		for (int i = 0; i < (int)G[cur.sec].size(); i++) {
			const Edge & e = G[cur.sec][i];
			if (e.capt <= 0) continue;
			int v = e.to;
			if (dis[v] > cur.fir + e.cost + H[cur.sec] - H[v]) {
				dis[v] = cur.fir + e.cost + H[cur.sec] - H[v];
				prv[v] = cur.sec, prve[v] = i;
				hap.push(Pii(dis[v], v));
			}
		}
	}
	return ~prv[T];
}

void Mcf(int & cost) {
	Fill(H, 0, T, 0);
	cost = 0;
	while (Dijkstra()) {
		for (int i = 0; i <= T; i++) H[i] += dis[i];
		int f = kInf;
		BACK(u) f = std::min(f, G[prv[u]][prve[u]].capt);
		cost += f * H[T];
		BACK(u) {
			Edge & e = G[prv[u]][prve[u]];
			e.capt -= f;
			G[u][e.rev].capt += f;
		}
	}
}
