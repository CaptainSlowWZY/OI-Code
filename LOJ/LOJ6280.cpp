// LOJ 6280
// Bucket Method
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

#define id(_) ((_ - 1) / bsz + 1)

const int MAXN = 5e4 + 500;
const int SQRTN = 250;

typedef long long LL;
typedef LL Arr[MAXN];
typedef LL Blk[SQRTN];

int N, bsz, mod;
Arr A;
Blk tag, sum;

template <typename T1, typename T2>
inline void add(T1 & x, T2 d) { (x += d) >= mod ? (x -= mod) : 0; }

int main() {
	scanf("%d", &N);
	bsz = floor(sqrt(N));
	for (int i = 1; i <= N; i++) {
		scanf("%lld", A + i);
		sum[id(i)] += A[i];
	}

	for (int cs = 0, opt, l, r, c; cs < N; cs++) {
		scanf("%d%d%d%d", &opt, &l, &r, &c);
		int idl = id(l), idr = id(r), bfir = idl * bsz, blst = idr * bsz - bsz + 1;
		if (opt) {
			LL ans = 0;
			mod = c + 1;
			if (idl == idr) {
				for (int i = l; i <= r; i++) add(ans, A[i] + tag[idl]);
				ans = (ans + mod) % mod;
				printf("%lld\n", ans);
				continue;
			}
			for (int i = l; i <= bfir; i++) add(ans, A[i] + tag[idl]);
			for (int i = blst; i <= r; i++) add(ans, A[i] + tag[idr]);
			for (int i = idl + 1; i < idr; i++) add(ans, sum[i]);
			ans = (ans + mod) % mod;
			printf("%lld\n", ans);
		}	
		else {
			if (idl == idr) {
				for (int j = l; j <= r; j++) A[j] += c, sum[idl] += c;
				continue;
			}
			for (int j = l; j <= bfir; j++) A[j] += c, sum[idl] += c;
			for (int j = blst; j <= r; j++) A[j] += c, sum[idr] += c;
			for (int j = idl + 1; j < idr; j++) tag[j] += c, sum[j] += c * bsz;
		}
	}
	return 0;
}
