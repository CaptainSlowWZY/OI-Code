// BZOJ 1021
// SHOI 2008
#include <cstdio>
#include <cstring>

const int VAL[] = {0, 100, 50, 20, 10, 5, 1};

int A[3][7], S[3], T[3], DP[7][1005][1005];

inline void upd_min(int & x, int y) { x > y ? x = y : 0; }

int main() {
	int AB, BC, CA;
	scanf("%d%d%d", &AB, &BC, &CA);
	for (int i = 0; i < 3; i++)
		for (int j = 1; j <= 6; j++) {
			scanf("%d", &A[i][j]);
			S[i] += A[i][j] * VAL[j];
		}

	T[0] = S[0] - AB + CA;
	T[1] = S[1] + AB - BC;
	T[2] = S[2] + BC - CA;
	if (T[0] < 0 || T[1] < 0 || T[2] < 0) {
		puts("impossible");
		return 0;
	}
	memset(DP, 0x7f, sizeof DP);
	int INF = DP[0][0][0];
	DP[0][S[0]][S[1]] = 0;
	int sum = S[0] + S[1] + S[2];
	for (int i = 1; i <= 6; i++)
		for (int a = 0; a <= sum; a++)
			for (int b = 0; a + b <= sum; b++) {
				if (DP[i - 1][a][b] == INF) continue;
			//	A -> B, C
				for (int o = 1; o <= A[0][i] && o * VAL[i] <= a; o++)
					for (int tb = 0; tb <= o; tb++)
						upd_min(DP[i][a - o * VAL[i]][b + tb * VAL[i]], DP[i - 1][a][b] + o);
			//	B -> A, C
				for (int o = 1; o <= A[1][i] && o * VAL[i] <= b; o++)
					for (int ta = 0; ta <= o; ta++)
						upd_min(DP[i][a + ta * VAL[i]][b - o * VAL[i]], DP[i - 1][a][b] + o);
			//	C -> A, B
				for (int o = 1; o <= A[2][i] && o * VAL[i] <= sum - a - b; o++)
					for (int ta = 0; ta <= o; ta++)
						upd_min(DP[i][a + ta * VAL[i]][b + (o - ta) * VAL[i]], DP[i - 1][a][b] + o);
			//	A, B -> C
				for (int oa = 0; oa <= A[0][i] && oa * VAL[i] <= a; oa++)
					for (int ob = 0; ob <= A[1][i] && ob * VAL[i] <= b; ob++) {
						if (oa + ob == 0) continue;
						upd_min(DP[i][a - oa * VAL[i]][b - ob * VAL[i]], DP[i - 1][a][b] + oa + ob);
					}
			//	A, C -> B
				for (int oa = 0; oa <= A[0][i] && oa * VAL[i] <= a; oa++)
					for (int oc = 0; oc <= A[2][i] && oc * VAL[i] <= sum - a - b; oc++) {
						if (oc + oa == 0) continue;
						upd_min(DP[i][a - oa * VAL[i]][b + (oa + oc) * VAL[i]], DP[i - 1][a][b] + oa + oc);
					}
			//	B, C -> A
				for (int ob = 0; ob <= A[1][i] && ob * VAL[i] <= b; ob++)
					for (int oc = 0; oc <= A[2][i] && oc * VAL[i] <= sum - a - b; oc++) {
						if (oc + ob == 0) continue;
						upd_min(DP[i][a + (ob + oc) * VAL[i]][b - ob * VAL[i]], DP[i - 1][a][b] + ob + oc);
					}
				upd_min(DP[i][a][b], DP[i - 1][a][b]);
			}

	if (DP[6][T[0]][T[1]] == INF) puts("impossible");
	else printf("%d\n", DP[6][T[0]][T[1]]);
	
	return 0;
}
