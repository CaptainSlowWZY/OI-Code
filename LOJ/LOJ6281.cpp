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

int N, bsz, cnt[SQRTN][2];
LL A[MAXN], sum[SQRTN];

int main() {
	scanf("%d", &N);
	bsz = floor(sqrt(N));
	for (int i = 1; i <= N; i++) {
		scanf("%lld", A + i);
		sum[id(i)] += A[i];
		if (A[i] <= 1) ++cnt[id(i)][A[i]];
	}

	for (int cs = 0, opt, l, r, c; cs < N; cs++) {
		scanf("%d%d%d%d", &opt, &l, &r, &c);
		int idl = id(l), idr = id(r), bfir = idl * bsz, blst = idr * bsz - bsz + 1;
		if (opt) {
			LL ans = 0;
			if (idl == idr) {
				for (int i = l; i <= r; i++) ans += A[i];
				printf("%lld\n", ans);
				continue;
			}
			for (int i = l; i <= bfir; i++) ans += A[i];
			for (int i = blst; i <= r; i++) ans += A[i];
			for (int i = idl + 1; i < idr; i++) ans += sum[i];
			printf("%lld\n", ans);
		}	
		else {
			if (idl == idr) {
				for (int i = l; i <= r; i++) {
					if (A[i] <= 1) continue;
					sum[idl] -= A[i];
					A[i] = floor(sqrt(A[i]));
					sum[idl] += A[i];
					if (A[i] <= 1) ++cnt[idl][A[i]];
				}
				continue;
			}
			for (int i = l; i <= bfir; i++) {
				if (A[i] <= 1) continue;
				sum[idl] -= A[i];
				A[i] = floor(sqrt(A[i]));
				sum[idl] += A[i];
				if (A[i] <= 1) ++cnt[idl][A[i]];
			}
			for (int i = blst; i <= r; i++) {
				if (A[i] <= 1) continue;
				sum[idr] -= A[i];
				A[i] = floor(sqrt(A[i]));
				sum[idr] += A[i];
				if (A[i] <= 1) ++cnt[idr][A[i]];
			}
			for (int i = idl + 1; i < idr; i++) {
				if (cnt[i][0] + cnt[i][1] == bsz) continue;
				sum[i] = 0;
				for (int j = i * bsz - bsz + 1, rb = i * bsz; j <= rb; j++) {
					if (A[j] <= 1) {
						sum[i] += A[j];
						continue;
					}
					sum[i] += A[j] = floor(sqrt(A[j]));
					if (A[j] <= 1) ++cnt[i][A[j]];
				}
			}
		}
	}
	return 0;
}
