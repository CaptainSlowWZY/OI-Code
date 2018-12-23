// Luogu P4213
#include <cstdio>
#include <map>

typedef long long LL;

const int INIT_N = 1 << 22;

int N, totp, P[INIT_N + 10], summ[INIT_N + 10];
LL sump[INIT_N + 10];
std::map<int, int> Ansm;
std::map<int, LL> Ansp;

void init();
void solve();

int main() {
	init();

	int t;
	for (scanf("%d", &t); t--; ) solve();

	return 0;
}

LL Sphi(int n) {
	if (n < INIT_N) return sump[n];
	if (Ansp.count(n)) return Ansp[n];
	LL & ret = Ansp[n];
	ret = (LL)(n + 1) * n >> 1;
	for (int i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ret -= (LL)(j - i + 1) * Sphi(n / i);
	}
	return ret;
}

int Smu(int n) {
	if (n < INIT_N) return summ[n];
	if (Ansm.count(n)) return Ansm[n];
	int & ret = Ansm[n];
	ret = n > 1;
	for (int i = 2, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ret -= (LL)(j - i + 1) * Smu(n / i);
	}
	return ret;
}

void solve() {
	scanf("%d", &N);
	printf("%lld %d\n", Sphi(N), Smu(N));
}

void init() {
	sump[1] = 1, summ[1] = 1;
	for (int i = 2; i <= INIT_N; i++) {
		if (!sump[i]) P[totp++] = i, summ[i] = -1, sump[i] = i - 1;
		for (int j = 0, d; j < totp && (d = i * P[j]) <= INIT_N; j++) {
			if (i % P[j] == 0) {
				sump[d] = sump[i] * P[j];
				summ[d] = 0;
				break;
			}
			sump[d] = sump[i] * (P[j] - 1);
			summ[d] = -summ[i];
		}
	}
	for (int i = 2; i <= INIT_N; i++) {
		sump[i] += sump[i - 1];
		summ[i] += summ[i - 1];
	}
}
