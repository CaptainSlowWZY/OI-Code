// ABC 107 D
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
const int MAXN = 1e5 + 10;
typedef int IntAr[MAXN];
typedef long long LL;

int N;
IntAr A, B, C, D;
LL tot;

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}
LL count(int);
void merge(int l, int r);

// #define DEBUG_MD_

int main() {
	using FastIO::read;
	read(N);
	for (int i = 0; i < N; i++) scanf("%d", &A[i]);
	memcpy(B, A, sizeof(int) * N);
	std::sort(B, B + N);
	int lb = -1, mid, ub = std::unique(B, B + N) - B - 1;
	LL pos = (LL(N) * (N + 1) >> 2) + 1;
#ifdef DEBUG_MD_
	printf("pos=%lld\n", pos);
#endif 
	for (; ub - lb > 1; ) { // (lb, ub]
		mid = lb + ub >> 1;
		assert(mid >= 0);
		if (count(B[mid]) >= pos) ub = mid;
		else lb = mid;
	}
	// return 0;
	printf("%d\n", B[ub]);
	return 0;
}

LL count(int key) {
	C[0] = 0;
	for (int i = 1; i <= N; i++) C[i] = C[i - 1] + (A[i - 1] > key ? -1 : 1);
	tot = 0;
	merge(0, N + 1);
#ifdef DEBUG_MD_
	printf("key=%d, tot=%lld\n", key, tot);
#endif 
	return tot;
}

void merge(int l, int r) {
	// merge sort interval [l, r)
	if (r - l <= 1) return;
	int mid = l + r >> 1;
	merge(l, mid);
	merge(mid, r);
#ifdef DEBUG_MD_
	printf("[%d, %d)\n", l, r);
#endif
	int i, j, k;
	for (i = l, j = mid, k = l; i < mid && j < r; )
		if (C[i] < C[j]) {
			D[k++] = C[i++];
			tot += r - j;
		}
		else D[k++] = C[j++];
	for (; i < mid; ) D[k++] = C[i++];
	for (; j < r; ) D[k++] = C[j++];
	memcpy(C + l, D + l, sizeof(int) * (r - l));
}

// AC!!!
