#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>

#define fir first
#define sec second
#define ID(_) ((_ + bsz - 1) / bsz)

typedef std::pair<int, int> Pii;

const int kMaxn = 1e5 + 10, kSqrt = 320;

int n, c, m, bsz, totb;
int A[kMaxn], cnt[kMaxn], id[kMaxn];
int ans[kSqrt][kSqrt], sff[kSqrt][kMaxn];

void SB3(int fir, int lst, int & res, int sffl[], int sffr[]);

int main() {
	scanf("%d%d%d", &n, &c, &m);
	for (int i = 1; i <= n; i++) scanf("%d", A + i);

	bsz = (int)ceil(sqrt(n));
//	bsz = 1;
	for (int l = 1; l <= n; l += bsz) {
		++totb;
		for (int i = l; i <= n && i < l + bsz; i++)
			id[i] = totb;
	}
	id[n + 1] = ++totb;
	for (int l = 1, cur; l <= n; l += bsz) {
		cur = id[l];
		for (int i = l, eve = 0; i <= n; i++) {
			if (sff[cur][A[i]] && !(sff[cur][A[i]] & 1)) --eve;
			if (!(++sff[cur][A[i]] & 1)) ++eve;
			if (id[i] != id[i + 1]) ans[cur][id[i]] = eve;
		}
	}
	
	for (int l, r, res, lastans = 0; m--; ) {
		scanf("%d%d", &l, &r);
		l = (l + lastans) % n + 1;
		r = (r + lastans) % n + 1;
		if (l > r) std::swap(l, r);
		int idl = ID(l), idr = ID(r);
	//	printf(" l %d, idl %d; r %d, idr %d\n", l, idl, r, idr);
		if (idl < idr) {
			res = ans[idl + 1][idr - 1];
		//	printf("  res = %d\n", res);
			SB3(l, idl * bsz, res, sff[idl + 1], sff[idr]);
			SB3((idr - 1) * bsz + 1, r, res, sff[idl + 1], sff[idr]);
			for (int i = l; i <= idl * bsz; i++) --cnt[A[i]];
			for (int i = (idr - 1) * bsz + 1; i <= r; i++) --cnt[A[i]];
		} else {
			res = 0;
			for (int i = l; i <= r; i++) {
			//	printf("  !! A[%d] = %d, cntA_i = %d\n", i, A[i], cnt[A[i]]);
				if (cnt[A[i]]) {
					if (cnt[A[i]] & 1) ++res;
					else --res;
				}
				++cnt[A[i]];
			}
			for (int i = l; i <= r; i++) --cnt[A[i]];
		}
		printf("%d\n", lastans = res);
	}
	return 0;
}

void SB3(int fir, int lst, int & res, int sffl[], int sffr[]) {
	for (int i = fir, tmp; i <= lst; i++) {
		if (tmp = sffl[A[i]] - sffr[A[i]]) {
			if (tmp + cnt[A[i]] & 1) ++res;
			else --res;
		} else if (cnt[A[i]]) {
			if (cnt[A[i]] & 1) ++res;
			else --res;
		}
	//	printf("     A[%d] = %d, tmp = %d\n", i, A[i], tmp);
		++cnt[A[i]];
	}
}
