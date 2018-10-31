// LOJ 6279
// Bucket Method
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

#define id(_) ((_ - 1) / bsz + 1)

const int MAXN = 1e5 + 600;
const int SQRTN = 500;

int N, bsz, A[MAXN], B[MAXN], tag[SQRTN];

inline void resort(int id) {
	memcpy(B + id * bsz - bsz + 1, A + id * bsz - bsz + 1, sizeof(int) * bsz);
	std::sort(B + id * bsz - bsz + 1, B + id * bsz + 1);
}
inline void upd_max(int & x, int d) { x < d ? x = d : 0; }

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", A + i);

	bsz = floor(sqrt(N));
	for (int i = 1; i * bsz <= N; ++i) resort(i);
	for (int i = 0, opt, l, r, c; i < N; i++) {
		scanf("%d%d%d%d", &opt, &l, &r, &c);
		int idl = id(l), idr = id(r), bfir = idl * bsz, blst = idr * bsz - bsz + 1;
		if (opt) {
			int ans = -1;
			if (idl == idr) {
				for (int j = l; j <= r; j++)
					if (A[j] + tag[idl] < c) upd_max(ans, A[j] + tag[idl]);
				printf("%d\n", ans);
				continue;
			}
			for (int j = l; j <= bfir; j++)
				if (A[j] + tag[idl] < c) upd_max(ans, A[j] + tag[idl]);
			for (int j = blst; j <= r; j++)
				if (A[j] + tag[idr] < c) upd_max(ans, A[j] + tag[idr]);
			for (int j = idl + 1; j < idr; j++) {
				int *ptr = std::lower_bound(B + j * bsz - bsz + 1, B + j * bsz + 1, c - tag[j]);
				if (ptr == B + j  * bsz - bsz + 1) continue;
				upd_max(ans, *(--ptr) + tag[j]);
			}
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
