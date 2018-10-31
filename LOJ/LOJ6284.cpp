// LOJ 6284
// Bucket Method
#include <cstdio>
#include <cstring>
#include <cmath>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define rg register
#define gch getchar
#define pch putchar
#define id(_) ((_ - 1) / bsz + 1)

const int MAXN = 1e5 + 500;
const int SQRTN = 500;

int N, bsz, A[MAXN], tag[SQRTN];

namespace FastIO {
	template <typename T>
		void read(T & x);
	template <typename T>
		void write(T x);
	template <typename T>
		inline void writeln(T x) {
			write(x), pch('\n');
		}
}
int qry_and_mdf(int fir, int lst, int c) {
	int idd = id(fir), res = 0, md = idd * bsz - bsz + 1 == fir && idd * bsz == lst;
	debug(" query and modify:\n  [%d, %d], c=%d, md=%d, blockid=%d\n", fir, lst, c, md, idd);
	debug("  tag[idd]=%d\n", tag[idd]);
#ifdef DEBUG_MD
	for (int i = fir; i <= lst; i++) debug("%4d%c", A[i], i == lst ? '\n' : ' ');
#endif
	if (~tag[idd]) res = (tag[idd] == c) * (lst - fir + 1);
	else for (int i = fir; i <= lst; i++) res += A[i] == c;
	debug("res=%d\n", res);
	if (md) tag[idd] = c;
	else {
		if (~tag[idd])
			for (int lmt = idd * bsz, i = lmt - bsz + 1; i <= lmt; i++) A[i] = tag[idd];
		for (int i = fir; i <= lst; i++) A[i] = c;
		tag[idd] = -1;
	}
	return res;
}

int main() {
	using FastIO::read;

	read(N);
	bsz = floor(sqrt(N));
	for (int i = 1; i <= N; i++) read(A[i]);

	memset(tag, 0xff, sizeof tag);
	for (int cs = 0, l, r, c; cs < N; cs++) {
		read(l), read(r), read(c);
		int idl = id(l), idr = id(r), lb = idl * bsz, rb = idr * bsz - bsz + 1, ans = 0;
		if (idl == idr) {
			printf("%d\n", qry_and_mdf(l, r, c));
			continue;
		}
		ans += qry_and_mdf(l, lb, c) + qry_and_mdf(rb, r, c);
		for (int i = idl + 1; i < idr; i++) ans += qry_and_mdf(i * bsz - bsz + 1, i * bsz, c);
		printf("%d\n", ans);
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
