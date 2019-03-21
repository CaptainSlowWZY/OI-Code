#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>

#define forto(_) for (int e = last[_], v = E[e].to; e; v = E[e = E[e].next].to)
#ifdef DEBUG
	#define db(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define db(format, ...) 0
#endif

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

typedef long long LL;

const int kMaxn = 2e4 + 10, kMaxq = 2e5 + 10;

struct Edge {
	int to, next;
} E[kMaxn << 1];
struct Query {
	int u, v, id;
};

int n, q, tote, centr, allsz;
int last[kMaxn], sz[kMaxn], vis[kMaxn];
LL V[kMaxn], ans[kMaxq];
std::vector<Query> qur[kMaxq];
int deal[kMaxq];

inline void AddEdge(int u, int v) {
	E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	E[++tote] = (Edge){u, last[v]}, last[v] = tote;
}
void Solve(int);

int main() {
	using fast_io::Read;

	Read(n), Read(q);
	for (int i = 1; i <= n; i++) Read(V[i]);
	for (int i = 1, u, v; i < n; i++) {
		Read(u), Read(v);
		AddEdge(u, v);
	}
	for (int i = 0, x, y; i < q; i++) {
		Read(x), Read(y);
		deal[i] = -1;
		qur[1].push_back((Query){x, y, i});
	}

	Solve(1);

	for (int i = 0; i < q; i++) {
		fast_io::Println(ans[i]);
		if (deal[i] == -1) printf("%d\n", i);
		assert(~deal[i]);
	}
	return 0;
}

inline void Umax(int & x, int y) {
	x < y ? x = y : 0;
}

void FindCen(int u, int fa) {
	static int mxsz[kMaxn];
	sz[u] = 1, mxsz[u] = 0;
	forto(u) {
		if (v == fa || vis[v]) continue;
		FindCen(v, u);
		Umax(mxsz[u], sz[v]);
		sz[u] += sz[v];
	}
	Umax(mxsz[u], allsz - sz[u]);
	if (centr == -1 || mxsz[u] <= mxsz[centr]) centr = u;
}

class Linb {
private:
	static const int kLen = 61;
	LL bas[kLen];
public:
	Linb(LL x = 0) {
		memset(bas, 0, sizeof bas);
		if (x) insert(x);
	}
	Linb(const Linb & b1, const Linb & b2) {
		memcpy(bas, b1.bas, sizeof b1.bas);
		for (int i = 0; i < kLen; i++) {
			if (!b2.bas[i]) continue;
			insert(b2.bas[i]);
		}
	}
	void insert(LL x) {
		for (int i = kLen - 1; i >= 0; i--) {
			if (x >> i & 1 ^ 1) continue;
			if (bas[i]) x ^= bas[i];
			else {
				for (int j = 0; j < i; j++) {
					if (x >> j & 1) x ^= bas[j];
				}
				bas[i] = x;
				for (int j = i + 1; j < kLen; j++) {
					if (bas[j] >> i & 1) bas[j] ^= x;
				}
				return;
			}
		}
	}
	LL maxor() const {
		LL ret = 0;
		for (int i = kLen - 1; i >= 0; i--) {
			if (!bas[i]) continue;
			ret ^= bas[i];
		}
		return ret;
	}
/*	void deb() const {
		puts(" ###### DEBUGER FOR LINEAR BASIS ######");
		for (int i = kLen - 1; i >= 0; i--) {
			printf(" bit %2d ", i);
			for (int j = kLen - 1; j >= 0; j--) {
				putchar('0' ^ (bas[i] >> j & 1));
			}
			putchar('\n');
		}
		puts(" ######   E   N   D   ######\n");
	}*/
} L[kMaxn];

int top[kMaxn];

void DfsSub(int u, int fa, int tp) {
	top[u] = tp, sz[u] = 1;
	forto(u) {
		if (vis[v] || v == fa) continue;
		L[v] = L[u];
		L[v].insert(V[v]);
		DfsSub(v, u, tp);
		sz[u] += sz[v];
	}
}

void Solve(int u) {
	db(" Solve %d, subtree-size = %d\n", u, sz[u]);
	allsz = u == 1 ? n : sz[u], centr = -1;
	FindCen(u, 0);
	db("  center = %d\n", centr);
	L[centr] = V[centr], top[centr] = centr, sz[centr] = 1;
	forto(centr) {
		if (vis[v]) continue;
		L[v] = L[centr];
		L[v].insert(V[v]);
		DfsSub(v, centr, v);
		sz[centr] += sz[v];
	//	qur[v].clear();
	}
	static std::vector<Query> tmp;
	db(" Query of %d\n", u);
	for (std::vector<Query>::iterator it = qur[u].begin();
			it != qur[u].end(); ++it) {
		if (top[it->u] == top[it->v] && top[it->u] != centr) {
			db("  Query %d (%d, %d) top = %d\n",
					it->id, it->u, it->v, top[it->u]);
			tmp.push_back(*it);
			continue;
		}
		db("  Dealing with query (%d, %d)\n", it->u, it->v);
		ans[it->id] = Linb(L[it->u], L[it->v]).maxor();
		deal[it->id] = 0;
	}
	qur[u].clear(), vis[centr] = 1;
	for (std::vector<Query>::iterator it = tmp.begin();
			it != tmp.end(); ++it) {
		qur[top[it->u]].push_back(*it);
	}
	tmp.clear();
	forto(centr) {
		if (vis[v]) continue;
		Solve(v);
	}
}
