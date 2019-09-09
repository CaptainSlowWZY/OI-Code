#include <algorithm>
#include <cstdio>

const int kMaxn = 1e5 + 5, kMod = 99999997;

typedef int IAr[kMaxn];

int n, ans;
IAr A, B, pos, id, rank;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }
inline bool CmpA(int a, int b) { return A[a] < A[b]; }
inline bool CmpB(int a, int b) { return B[a] < B[b]; }
void Divide(int fir, int lst);

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", A + i);
		pos[i] = id[i] = i;
	}
	for (int i = 0; i < n; i++) scanf("%d", B + i);

	std::sort(pos, pos + n, CmpA);
	std::sort(id, id + n, CmpB);
	for (int i = 0; i < n; i++) rank[id[i]] = i;
	for (int i = 0; i < n; i++) B[i] = pos[rank[i]];
	Divide(0, n);
	printf("%d\n", ans);
	return 0;
}

void Divide(int fir, int lst) {
	if (lst - fir <= 1) return;
	int mid = fir + lst >> 1;
	Divide(fir, mid); Divide(mid, lst);
	static IAr buf;
	int i = fir, j = mid, k = fir;
	while (i < mid && j < lst) {
		if (B[i] < B[j]) {
			buf[k++] = B[i++];
		} else {
			ans = Add(ans, mid - i);
			buf[k++] = B[j++];
		}
	}
	while (i < mid) buf[k++] = B[i++];
	while (j < lst) buf[k++] = B[j++];
	for (i = fir; i < lst; i++) B[i] = buf[i];
}
