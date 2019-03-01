#include <cstdio>
#include <algorithm>

const int kMaxn = 1e5 + 10;

int n, zj[kMaxn], bz[kMaxn];

int Calc(int v1[], int v2[]);

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", zj + i);
	for (int i = 0; i < n; i++) scanf("%d", bz + i);

	std::sort(zj, zj + n);
	std::sort(bz, bz + n);
	printf("%d %d\n", Calc(zj, bz), 2 * n - Calc(bz, zj));
	return 0;
}

int Calc(int v1[], int v2[]) {
	int ret = 0, l1 = 0, r1 = n, l2 = 0, r2 = n;
	for (; l1 < r1; ) {
		if (v1[l1] > v2[l2]) {
			++l1, ++l2;
			ret += 2;
		}
		else if (v1[l1] < v2[l2]) {
			++l1, --r2;
		}
		else {
			if (v1[r1 - 1] > v2[r2 - 1]) {
				--r1, --r2;
				ret += 2;
			}
			else {
				if (v1[l1] == v2[r2 - 1]) ++ret;
				++l1, --r2;				
			}
		}
	}
	return ret;
}
