// LOJ 6277
// Bucket Method
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

#define id(_) ((_ - 1) / bsz + 1)

const int MAXN = 5e4 + 500;
const int SQRTN = 250;

int N, bsz, A[MAXN], B[MAXN], tag[SQRTN];

inline void resort(int id) {
	memcpy(B + id * bsz - bsz + 1, A + id * bsz - bsz + 1, sizeof(int) * bsz);
	std::sort(B + id * bsz - bsz + 1, B + id * bsz + 1);
}

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", A + i);

	bsz = floor(sqrt(N));
	for (int i = 1; i * bsz <= N; ++i) resort(i);
	for (int i = 0, opt, l, r, c; i < N; i++) {
		scanf("%d%d%d%d", &opt, &l, &r, &c);
		int idl = id(l), idr = id(r), bfir = idl * bsz, blst = idr * bsz - bsz + 1;
		if (opt) {
			c *= c;
			int ans = 0;
			if (idl == idr) {
				for (int j = l; j <= r; j++)
					if (A[j] + tag[idl] < c) ++ans;
				printf("%d\n", ans);
				continue;
			}
			for (int j = l; j <= bfir; j++)
				if (A[j] + tag[idl] < c) ++ans;
			for (int j = blst; j <= r; j++)
				if (A[j] + tag[idr] < c) ++ans;
			for (int j = idl + 1; j < idr; j++)
				ans += std::lower_bound(B + j * bsz - bsz + 1, B + j * bsz + 1, c - tag[j]) - (B + j * bsz - bsz + 1);
			printf("%d\n", ans);
		}	
		else {
			if (idl == idr) {
				for (int j = l; j <= r; j++) A[j] += c;
				resort(idl);
				continue;
			}
			for (int j = l; j <= bfir; j++) A[j] += c;
			resort(idl);
			for (int j = blst; j <= r; j++) A[j] += c;
			resort(idr);
			for (int j = idl + 1; j < idr; j++) tag[j] += c;
		}
	}
	return 0;
}
