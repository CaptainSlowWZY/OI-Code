// POJ 2420
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <algorithm>

#define fir first
#define sec second

typedef std::pair<int, int> Pii;

const int MAXN = 105;
const int MAXCRD = 10000;
const double ORG_TEMP = 6300;
const double CLAMDWN = 0.989;
const double MIN_TEMP = 1e-5;

int N;
Pii C[MAXN], ans;
double ansv;

void solve();

int main() {
	srand(19260817);
	solve();
	return 0;
}

inline double sqr(double x) { return x * x; }

inline double dist(const Pii & p1, const Pii & p2) {
	return sqrt(sqr(p1.fir - p2.fir) + sqr(p1.sec - p2.sec));
}

double calc(Pii hb) {
	double ret = 0;
	for (int i = 0; i < N; i++) ret += dist(hb, C[i]);
	return ret;
}

void SA() {
	Pii ret = ans;
	double retv = ansv, temp = ORG_TEMP;
	while (temp > MIN_TEMP) {
		Pii nxt(ret.fir + (rand() & 1 ? -1 : 1) * temp * rand() / RAND_MAX, ret.sec + (rand() & 1 ? -1 : 1) * temp * rand() / RAND_MAX);
		double nxtd = calc(nxt);
		if (nxtd < retv || exp((retv - nxtd) / temp) * RAND_MAX > rand()) {
			retv = nxtd, ret = nxt;
			if (retv < ansv) {
				ansv = retv;
				ans = ret;
			}
		}
		temp *= CLAMDWN;
	}
}

void solve() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) scanf("%d%d", &C[i].fir, &C[i].sec);
	ans = C[0], ansv = calc(ans);
	for (int t = 0; t < 5; t++) SA();
	printf("%d\n", (int)round(ansv));
}
