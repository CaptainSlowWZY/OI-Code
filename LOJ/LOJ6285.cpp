// LOJ 6285
// Bucket Method
#pragma GCC diagnostic error "-std=c++11"
#pragma GCC optimize(2)
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <utility>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define fir first
#define sec second
#define rg register
#define gch getchar
#define pch putchar
#define pb push_back
#define id(_) ((_ - 1) / bsz + 1)

const int MAXN = 1e5 + 500;
const int SQRTN = 350;

typedef std::pair<int, int> Pii;
typedef int Arr[MAXN];

int N, bsz, totrk;
Arr A, B, cnt, sum[SQRTN];
Pii mode[SQRTN][SQRTN];

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
inline bool cmp(const Pii & p1, const Pii & p2) {
	return p1.fir ^ p2.fir ? p1.fir < p2.fir : p1.sec > p2.sec;
}
inline int get_id(int v) {
	return std::lower_bound(B + 1, B + 1 + totrk, v) - B;
}

int main() {
	using FastIO::read;

	read(N);
	bsz = floor(sqrt(N));
	for (rg int i = 1; i <= N; i++) read(A[i]);
	
	memcpy(B + 1, A + 1, sizeof(int) * N);
	std::sort(B + 1, B + 1 + N);
	totrk = std::unique(B + 1, B + 1 + N) - B - 1;
	for (rg int i = 1; i <= N; i++) A[i] = get_id(A[i]);
	debug("totrk=%d\n", totrk);

	for (rg int i = 1, lmti = id(N); i <= lmti; i++) {
		for (rg int j = 1; j <= totrk; j++) sum[i][j] = sum[i - 1][j];
		for (rg int j = i * bsz - bsz + 1, lmt = std::min(i * bsz, N); j <= lmt; j++) ++sum[i][A[j]];
	}

	using std::max;
	for (rg int i = 1, lmti = id(N); i <= lmti; i++) {
		mode[i][i - 1] = Pii(0, 0);
		for (rg int j = i; j <= lmti; j++) {
			Pii now = mode[i][j - 1];
			for (rg int num, k = j * bsz - bsz + 1, lmt = std::min(N, j * bsz); k <= lmt; k++) {
				num = A[k];
				now = max(now, Pii(sum[j][num] - sum[i - 1][num], num), cmp);
			}
			mode[i][j] = now;
		}
	}
//	return 0;

	for (rg int cs = 0, l, r; cs < N; cs++) {
		read(l), read(r);
		int idl = id(l), idr = id(r), lb = idl * bsz, rb = idr * bsz - bsz + 1;
		Pii ans(0, 0);
		if (idl + 1 >= idr) {
			for (rg int i = l; i <= r; i++) ++cnt[A[i]];
			for (rg int i = l, num; i <= r; i++) {
				if (!cnt[num = A[i]]) continue;
				ans = max(ans, Pii(cnt[num], num), cmp), cnt[num] = 0;
			}
			FastIO::writeln(B[ans.sec]);
			continue;
		}
		ans = mode[idl + 1][idr - 1];
		for (rg int i = l; i <= lb; i++) ++cnt[A[i]];
		for (rg int i = rb; i <= r; i++) ++cnt[A[i]];
		for (rg int i = l, num; i <= lb; i++) {
			if (!cnt[num = A[i]]) continue;
			ans = max(ans, Pii(cnt[num] + sum[idr - 1][num] - sum[idl][num], num), cmp), cnt[num] = 0;
		}
		for (rg int i = rb, num; i <= r; i++) {
			if (!cnt[num = A[i]]) continue;
			ans = max(ans, Pii(cnt[num] + sum[idr - 1][num] - sum[idl][num], num), cmp), cnt[num] = 0;
		}
		FastIO::writeln(B[ans.sec]);
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