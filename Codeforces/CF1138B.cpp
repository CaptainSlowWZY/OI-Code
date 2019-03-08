#include <bits/stdc++.h>

const int kMaxn = 5010;

int n;
char C[kMaxn], A[kMaxn];

int main() {
	scanf("%d%s%s", &n, C, A);

	int totc = 0, tota = 0, totall = 0, tot0 = 0;
	for (int i = 0; i < n; i++) {
		if (C[i] == '1' && A[i] == '0') totc++;
		if (C[i] == '0' && A[i] == '1') tota++;
		if (C[i] == '1' && A[i] == '1') totall++;
		if (C[i] == '0' && A[i] == '0') tot0++;
	}
	for (int i = 0; i <= totall; i++) {
		for (int j = 0; j <= totc; j++) {
		//	determine clowns in 1 = i + j
			if (i + j > n / 2) continue;
			int c1 = i + j, a2 = totall - i;
			if (c1 < a2) continue;
			int need = c1 - a2;
			if (need > tota) continue;
			int cur1 = i + j + tota - need;
			int n0 = n / 2 - cur1;
			if (n0 >= 0 && n0 <= tot0) {
				int cnt1 = i, cnt2 = j, cnt3 = n0, cnt4 = tota - need;
//				printf(" i = %d, j = %d, need = %d\n", i, j, need);
//				printf(" cnt1 %d, cnt2 %d, cnt3 %d\n", cnt1, cnt2, cnt3);
				for (int k = 0; k < n; k++) {
					if (C[k] == '1' && A[k] == '1' && cnt1 > 0) {
						printf("%d ", k + 1);
						--cnt1;
					}
					if (C[k] == '1' && A[k] == '0' && cnt2 > 0) {
						printf("%d ", k + 1);
						--cnt2;
					}
					if (C[k] == '0' && A[k] == '0' && cnt3 > 0) {
						printf("%d ", k + 1);
						--cnt3;
					}
					if (C[k] == '0' && A[k] == '1' && cnt4 > 0) {
						printf("%d ", k + 1);
						--cnt4;
					}
//					if (cnt1 + cnt2 + cnt3 + cnt4 == 0) break;
				}
				printf("\n");
				return 0;
			}
		}
	}

	puts("-1");
	return 0;
}
