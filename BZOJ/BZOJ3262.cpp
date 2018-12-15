// BZOJ 3262
#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(fommat, ...) 0
#endif
#define rg register
#define pch putchar
#define gch getchar

const int MAXN = 1e5;
const int MAXK = 2e5;

struct Flower {
	int a, b, c, id;

	bool operator<(const Flower & f) const {
		return a ^ f.a ? a < f.a : (b ^ f.b ? b < f.b : c < f.c);
	}
	int operator!=(const Flower & f) const {
		return a ^ f.a | b ^ f.b | c ^ f.c;
	}
} F[MAXN + 10], B[MAXN + 10];

int N, K, ans[MAXN + 10], cnt[MAXN + 10];

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <>
		inline void read<Flower>(Flower & f) {
			read(f.a), read(f.b), read(f.c);
		}
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), pch('\n');
		}
}
namespace BIT {
	int lmt;

	inline void set_limit(int l_) { lmt = l_; }
}
void solve(int l, int r);

int main() {
	using FastIO::read;

	read(N), read(K);
	BIT::set_limit(K);
	for (rg int i = 0; i < N; i++) read(F[i]), F[i].id = i;

	std::sort(F, F + N);
	solve(0, N);
	int sum = 1;
	for (rg int i = N - 2; i >= 0; i--)
		if (F[i] != F[i + 1]) sum = 1;
		else ans[F[i].id] += sum++;
//	for (rg int i = 0; i < N; i++) debug(" (%d, %d, %d) id=%d, ans=%d\n", F[i].a, F[i].b, F[i].c, F[i].id, ans[F[i].id]);

	for (rg int i = 0; i < N; i++) cnt[ans[i]]++;
	for (rg int i = 0; i < N; i++) FastIO::writeln(cnt[i]);

	return 0;
}

namespace BIT {
	int T[MAXK + 10];

/*	inline void init() {
		memset(T, 0, sizeof(int) * (lmt + 5));
	}*/
	void add(int p, int d = 1) {
		for (; p <= lmt; p += p & -p) T[p] += d;
	}
	int query(int p) {
		int ret = 0;
		for (; p > 0; p &= p - 1) ret += T[p];
		return ret;
	}
}

void solve(int l, int r) {
	if (r - l <= 1) return;

	int mid = l + r >> 1;
	solve(l, mid);
	solve(mid, r);

	int i = l, j = mid, k = l;
	for (; i < mid && j < r; )
		if (F[i].b <= F[j].b) BIT::add(F[i].c), B[k++] = F[i++];
		else ans[F[j].id] += BIT::query(F[j].c), B[k++] = F[j++];
	for (; j < r; j++) ans[F[j].id] += BIT::query(F[j].c), B[k++] = F[j];
	for (rg int ii = l; ii < i; ii++) BIT::add(F[ii].c, -1);
	for (; i < mid; i++) B[k++] = F[i];
	for (i = l; i < r; i++) F[i] = B[i];
}

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; ch = gch())
				x = (x << 1) + (x << 3) + (ch ^ '0');
		}

	template <typename T>
		void write(T x) {
			if (!x) return (void)pch('0');
			if (x < 0) pch('-'), x = -x;
			rg int arr[20], len = 0;
			for (; x; x /= 10) arr[len++] = x % 10;
			while (len) pch(arr[--len] ^ '0');
		}
}
