#include <algorithm>
#include <cassert>
#include <cstdio>

#define fir first
#define sec second

typedef std::pair<int, int> Pii;

const int kMaxn = 305, kInf = 0x3f3f3f3f;

int n, m, q;
Pii C[kMaxn];
int A[kMaxn][kMaxn], D[kMaxn][kMaxn], vis[kMaxn];

inline void UMin(int & x, int y) {
	if (x > y) x = y;
}
void Floyd(int k);
void SPath(int d);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &C[i].fir);
		C[i].sec = i + 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			A[i][j] = D[i][j] = kInf;
	}
	for (int x, y, z; m--; ) {
		scanf("%d%d%d", &x, &y, &z);
		UMin(A[x][y], z); UMin(A[y][x], z);
	}

	std::sort(C, C + n);
	int cur = 0;
	Floyd(C[0].sec);
	for (int i = 1; i < n; i++) {
		if (C[i].fir == C[cur].fir)
			Floyd(C[i].sec);
		else {
			SPath(C[cur].fir);
			Floyd(C[cur = i].sec);
		}
	} SPath(C[cur].fir);

	scanf("%d", &q);
	for (int x, y; q--; ) {
		scanf("%d%d", &x, &y);
		printf("%d\n", D[x][y]);
	} return 0;
}

void Floyd(int k) {
	//  printf(" F %d\n", k);
	vis[k] = 1;
	for (int i = 1; i <= n; i++) {
	//	if (!vis[i]) continue;
		for (int j = 1; j <= n; j++) {
		//	if (!vis[j]) continue;
			UMin(A[i][j], A[i][k] + A[k][j]);
		}
	}
}

void SPath(int d) {
	//  printf(" SP d = %d\n", d);
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) continue;
		for (int j = 1; j <= n; j++) {
			if (!vis[j]) continue;
			UMin(D[i][j], A[i][j] + d);
		}
	}
}
