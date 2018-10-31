// LOJ 6283
// Bucket Method
#include <cstdio>
#include <cmath>

#define id(_) ((_ - 1) / bsz + 1)
#define rg register
#define gch getchar
#define pch putchar

typedef long long LL;

const int MAXN = 1e5 + 500;
const int SQRTN = 320;
const int MOD = 10007;

int N, bsz, A[MAXN], plus[SQRTN], multt[SQRTN];

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
inline void add(int &x, int d) {
	if ((x += d) >= MOD) x -= MOD;
}
inline void mult(int &x, LL y) {
	x = y * x % MOD;
}
void push_down(int id) {
	for (int lmt = id * bsz, i = lmt - bsz + 1; i <= lmt; i++) mult(A[i], multt[id]), add(A[i], plus[id]);
	multt[id] = 1, plus[id] = 0;
}

int main() {
	using FastIO::read;

	read(N);
	bsz = floor(sqrt(N));
	for (rg int i = 1; i <= N; i++) read(A[i]);

	for (rg int i = 1, lmt = id(N); i <= lmt; i++) multt[i] = 1;
	for (rg int cs = 0, opt, l, r, c; cs < N; cs++) {
		read(opt), read(l), read(r), read(c);
		int lid = id(l), rid = id(r), lb = lid * bsz, rb = rid * bsz - bsz + 1;
		if (!opt) {
			if (lid == rid) {
				push_down(lid);
				for (int i = l; i <= r; i++) add(A[i], c);
				continue;
			}
			push_down(lid), push_down(rid);
			for (int i = l; i <= lb; i++) add(A[i], c);
			for (int i = rb; i <= r; i++) add(A[i], c);
			for (int i = lid + 1; i < rid; i++) add(plus[i], c);
		}
		if (opt == 1) {
			if (lid == rid) {
				push_down(lid);
				for (int i = l; i <= r; i++) mult(A[i], c);
				continue;
			}
			push_down(lid), push_down(rid);
			for (int i = l; i <= lb; i++) mult(A[i], c);
			for (int i = rb; i <= r; i++) mult(A[i], c);
			for (int i = lid + 1; i < rid; i++) mult(plus[i], c), mult(multt[i], c);
		}
		if (opt == 2) FastIO::writeln(((LL)A[r] * multt[rid] % MOD + plus[rid]) % MOD);
	}

	return 0;
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch(); rg int f = 0;
			for (; ch < '0' || ch > '9'; ch = gch()) f |= ch == '-';
			for (x = 0; ch >= '0' && ch <= '9'; ch = gch()) x = (x << 3) + (x << 1) + (ch ^ '0');
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
