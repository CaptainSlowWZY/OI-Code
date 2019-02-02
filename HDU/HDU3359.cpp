// HDU 3359
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

const int MAXS = 15;
const int MAXB = 105;
const double EPS = 1e-7;

int W, H, D, totp, id[MAXS][MAXS], cnt[MAXS][MAXS];
double A[MAXB][MAXB];

void solve();

int main() {
	int cs = 0;
	while (scanf("%d%d%d", &W, &H, &D) == 3 && W && H) {
		if (cs++) putchar('\n');
		solve();
	}
	return 0;
}

void add(int x0, int y0, int dx, int dy) {
	int nx = x0 + dx, ny = y0 + dy;
	if (nx < 0 || nx >= H || ny < 0 || ny >= W) return;
	++cnt[x0][y0], A[id[x0][y0]][id[nx][ny]] = 1;
}

void solve() {
	memset(A, 0, sizeof A);
	memset(cnt, 0, sizeof cnt);
	totp = 0;
	
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++) {
			id[i][j] = totp++;
			scanf("%lf", &A[id[i][j]][H * W]);
		}
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			for (int dx = 0; dx <= D; dx++)
				for (int dy = 0; dx + dy <= D; dy++) {
					add(i, j, dx, dy);
					if (dy) add(i, j, dx, -dy);
					if (dx) {
						add(i, j, -dx, dy);
						if (dy) add(i, j, -dx, -dy);
					}
				}
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++) A[id[i][j]][totp] *= cnt[i][j];
	
	// gauss
	for (int i = 0; i < totp; i++) {
		int r = i;
		for (int j = i + 1; j < totp; j++)
			if (fabs(A[j][i]) > fabs(A[r][i])) r = j;
		if (r ^ i) {
			for (int j = i; j <= totp; j++) std::swap(A[i][j], A[r][j]);
		}
		for (int j = totp; j >= i; j--)
			for (int k = i + 1; k < totp; k++)
				A[k][j] -= A[k][i] / A[i][i] * A[i][j];
	}
	for (int i = totp - 1; i >= 0; i--) {
		if (fabs(A[i][i]) < EPS) continue;
		for (int j = i + 1; j < totp; j++) A[i][totp] -= A[i][j] * A[j][totp];
		A[i][totp] /= A[i][i];
	}

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) printf("%8.2lf", A[id[i][j]][totp]);
		putchar('\n');
	}
}
