// LOJ 6277
// Bucket Method
#include <cstdio>
#include <cmath>

#define id(_) ((_ - 1) / bsz + 1)

const int MAXN = 5e4 + 10;
const int SQRTN = 250;

int N, A[MAXN], tag[SQRTN];

int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) scanf("%d", A + i);

	int bsz = floor(sqrt(N));
	for (int i = 0, opt, l, r, c; i < N; i++) {
		scanf("%d%d%d%d", &opt, &l, &r, &c);
		if (opt) printf("%d\n", A[r] + tag[id(r)]);
		else {
			int idl = id(l), idr = id(r);
			if (idl == idr) {
				for (int j = l; j <= r; j++) A[j] += c;
				continue;
			}
			for (int j = l; j <= idl * bsz; j++) A[j] += c;
			for (int j = idl + 1; j < idr; j++) tag[j] += c;
			for (int j = idr * bsz - bsz + 1; j <= r; j++) A[j] += c;
		}
	}
	return 0;
}
