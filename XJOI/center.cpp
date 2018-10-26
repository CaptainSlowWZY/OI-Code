// center
#pragma GCC diagnostic error "-std=c++11"
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...)
#endif
#define fir first
#define sec second
#define pb push_back

typedef std::pair<int, int> Pii;

const int MAXN = 1005;
const int MAXM = 1e5 + 5;
const int INF = 0x3f3f3f3f;

class Bit_set {
private:
	static const int ArSize = 34;
	static const int CellSize = 30;
	int Set[ArSize];
public:
	Bit_set() { /*memset(Set, 0, sizeof Set);*/ }
	void clear() { memset(Set, 0, sizeof Set); }
	bool operator[](int ind) const {
//	index should base on 1
		--ind;
		return Set[ind / CellSize] >> ind % CellSize & 1;
	}
	void set_bit(int ind, int num) {
		--ind;
		if (num) Set[ind / CellSize] |= 1 << ind % CellSize;
		else Set[ind / CellSize] &= ~(1 << ind % CellSize);
	}
	void merge(const Bit_set & b) {
		for (int i = 0; i < ArSize; i++) Set[i] |= b.Set[i];
	}
	int count() const {
		int tot = 0;
		for (int i = 0; i < ArSize; i++) tot += __builtin_popcount(Set[i]);
		return tot;
	}
} reach[MAXN][MAXN];

int N, M, Q, tote, last[MAXN], vis[MAXN];
Pii D[MAXN];
std::vector<int> G[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), putchar('\n');
		}
}
void init();

int main() {
	using FastIO::read;

	read(N), read(M), read(Q);
	for (int i = 0, ui, vi; i < M; i++) {
		read(ui), read(vi);
		G[ui].pb(vi), G[vi].pb(ui);
	}
	
	init();

	for (int k; Q--; ) {
		read(k);
		Bit_set ans;
		ans.clear();
		for (int ui, di; k--; ) {
			read(ui), read(di);
			ans.merge(reach[ui][di]);
		}
		FastIO::writeln(ans.count());
	}
	return 0;
}

void init() {
	for (int i = 1; i <= N; i++) {
		memset(vis, 0, sizeof vis);
		for (int j = 1; j <= N; j++) D[j] = Pii(INF, j);
		std::queue<int> Q;
		Q.push(i), vis[i] = 1, D[i].fir = 0;
		for (int u; !Q.empty(); Q.pop())
			for (auto v : G[u = Q.front()]) {
				if (vis[v]) continue;
				vis[v] = 1, D[v].fir = D[u].fir + 1, Q.push(v);
			}

		std::sort(D + 1, D + 1 + N);
#ifdef DEBUG_MD
		debug("start=%d\n", i);
		for (int j = 1; j <= N; j++) debug("  ->%d: dist=%d\n", D[j].sec, D[j].fir);
#endif
		int d = 0;
		for (int j = 1; j <= N && D[j].fir < INF; j++) {
			for (; d < D[j].fir; ++d) reach[i][d + 1] = reach[i][d];
			reach[i][d].set_bit(D[j].sec, 1);
		}
		for (; d < N; ++d) reach[i][d + 1] = reach[i][d];
	}
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
	template <typename T>
		void write(T x) {
			if (!x) return (void)putchar('0');
			if (x < 0) x = -x, putchar('-');
			int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) putchar(arr[--len] ^ '0');
		}
}

// AC!!!
