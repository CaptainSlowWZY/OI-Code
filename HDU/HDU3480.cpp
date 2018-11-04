// HDU 3480
#include <cstdio>
#include <utility>
#include <algorithm>
#include <deque>

#define rg register
#define gch getchar
#define pch putchar
#define fir first
#define sec second

typedef long long LL;
typedef std::pair<LL, LL> Pll;
// typedef std::deque<Pll> Vecp;

const int MAXN = 1e4 + 5;
const int MAXM = 5005;

inline LL sqr(LL x) { return x * x; }

struct Que {
	int hd, tl;
	Pll q[MAXN];

	void init() { hd = tl = 0; }
	int size() const { return tl - hd; }
	LL back() const { return q[tl - 1].sec - sqr(q[tl - 1].fir); }
	LL find_best(LL ai);
	void insert(const Pll & nxt);
} que[2];

int N, M, A[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <>
		void write(const char *str) {
			for (rg int i = 0; str[i]; ++i) putchar(str[i]);
		}
	template <typename T>
		inline void writeln(T x) {
			write(x), pch('\n');
		}
}

inline Pll operator-(const Pll & v1, const Pll & v2) {
	return Pll(v1.fir - v2.fir, v1.sec - v2.sec);
}
inline LL operator*(const Pll & v1, const Pll & v2) {
	return v1.fir * v2.sec - v1.sec * v2.fir;
}
inline bool better(const Pll & p1, const Pll & p2, LL val) {
	return p1.sec - p2.sec <= 2 * val * (p1.fir - p2.fir);
}

void solve();

int main() {
	int t;
	for (FastIO::read(t); t--; ) solve();

	return 0;
}


void solve() {
	using FastIO::read;

	read(N), read(M);
	for (int i = 0; i < N; i++) read(A[i]);

	std::sort(A, A + N);
	Que *pre = &que[0], *nxt = &que[1];
	pre->init(), pre->insert(Pll(A[0], sqr(A[0])));
	for (int j = 0; j < M; j++) {
		nxt->init();
		for (int i = 0; i < N; i++) {
			Pll now(A[i + 1], pre->find_best(A[i]) + sqr(A[i + 1]));
			nxt->insert(now);
		}
		std::swap(pre, nxt);
	}

	static int ks = 0;
	FastIO::write("Case ");
	FastIO::write(++ks);
	putchar(':'), putchar(' ');
	FastIO::writeln(pre->back());
}

LL Que::find_best(LL ai) {
	while (hd + 1 < tl && better(q[hd + 1], q[hd], ai)) ++hd; 
	return q[hd].sec - 2 * ai * q[hd].fir + sqr(ai);
}

void Que::insert(const Pll & nxt) {
	while (hd + 1 < tl && (q[tl - 1] - q[tl - 2]) * (nxt - q[tl - 2]) <= 0) --tl; 
	q[tl++] = nxt;
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = gch());
		}
	template <typename T>
		void write(T x) {
			if (!x) return (void)pch('0');	
			if (x < 0) x = -x, pch('-');
			rg int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) pch(arr[--len] ^ '0');
		}
}

// AC!!!
