// HDU 4870
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <utility>

#define fir first
#define sec second

typedef std::pair<int, int> Pii;

const int MAXS = 400;
const double EPS = 1e-12;

int tots, stat[22][22];
double P, A[MAXS][MAXS];

void solve();

int main() {
	for (int i = 0; i <= 20; i++)
		for (int j = 0; j <= i; j++)
			stat[i][j] = tots++;

	while (scanf("%lf", &P) == 1) solve();

	return 0;
}

void solve() {
	memset(A, 0, sizeof A);

	for (int i = 0; i < 20; i++)
		for (int j = 0; j <= i; j++) {
			Pii nxt(i, j + 1);
			if (nxt.sec > nxt.fir) std::swap(nxt.fir, nxt.sec);
			A[stat[i][j]][stat[nxt.fir][nxt.sec]] += P;
			nxt = Pii(i, std::max(j - 2, 0));
			A[stat[i][j]][stat[nxt.fir][nxt.sec]] += 1 - P;
			A[stat[i][j]][stat[i][j]] += -1;
			A[stat[i][j]][tots] = -1;
		}

	// gauss
	for (int i = 0; i < tots; i++) {
		int r = i;
		for (int j = i + 1; j < tots; j++)
			if (fabs(A[j][i]) > fabs(A[r][i])) r = j;
		if (r ^ i) {
			for (int j = i; j <= tots; j++) std::swap(A[i][j], A[r][j]);
		}
		if (fabs(A[i][i]) < EPS) continue;
		for (int j = tots; j >= i; j--)
			for (int k = i + 1; k < tots; k++)
				A[k][j] -= A[k][i] / A[i][i] * A[i][j];
	}
	for (int i = tots - 1; i >= 0; i--) {
		if (fabs(A[i][i]) < EPS) continue;
		for (int j = i + 1; j < tots; j++)
			A[i][tots] -= A[i][j] * A[j][tots];
		A[i][tots] /= A[i][i];
	}

	printf("%lf\n", A[0][tots]);
}
