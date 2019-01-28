// BZOJ 1005
#include <cstdio>
#include <vector>

#define pch putchar

const int MAXN = 1e3 + 10;
const int BASE = 1e3;
const int JSTD[] = {100, 10, 1};

int N, totp, len, P[MAXN], flag[MAXN], num[MAXN], cnt[MAXN];
std::vector<int> D;

void init();
void facit(int, int);
void mult(int);

int main() {
	scanf("%d", &N);
	int totd = 0, nolim = 0;
	for (int i = 0, Di; i < N; i++) {
		scanf("%d", &Di);
		if (Di == -1 || Di == 1) {
			if (Di == -1) ++nolim;
			continue;
		}
		if (!Di) return puts("0"), 0;
		D.push_back(Di - 1);
		totd += Di - 1;
	}

	if (totd > N - 2) return puts("0"), 0;

	init();
	int rem = N - 2, sz = (int)D.size();
	if (sz) {
		for (int i = 2; i <= rem; i++) facit(i, 1);
		for (int i = 0; i < sz; rem -= D[i++])
			for (int j = 2; j <= D[i]; j++) facit(j, -1);
		for (int i = 2; i <= rem; i++) facit(i, -1);
	}

	num[0] = len = 1;
	for (int i = 0; i < totp; i++)
		for (; cnt[i]--; ) mult(P[i]);
	for (int i = 0; i < rem; i++) mult(nolim);

	printf("%d", num[len - 1]);
	for (int i = len - 2; i >= 0; i--) {
		for (int j = 0; j < 3 && num[i] < JSTD[j]; j++) pch('0');
		if (num[i]) printf("%d", num[i]);
	}
	pch('\n');

	return 0;
}

void init() {
	for (int i = 2; i <= N; i++) {
		if (!flag[i]) P[totp++] = i;
		for (int j = 0; j < totp && i * P[j] <= N; j++) {
			flag[i * P[j]] = 1;
			if (i % P[j] == 0) break;
		}
	}
}

void facit(int n, int v) {
	for (int i = 0; i < totp && P[i] <= n; i++)
		if (n % P[i] == 0) {
			int counter = 0;
			for (; n % P[i] == 0; n /= P[i]) ++counter;
			cnt[i] += counter * v;
		}
}

void mult(int a) {
	for (int i = 0; i < len; i++) num[i] *= a;
	for (int i = 0; i < len; i++)
		if (num[i] >= BASE) {
			num[i + 1] += num[i] / BASE;
			num[i] %= BASE;
		}
	for (; num[len]; ++len)
		if (num[len] >= BASE) {
			num[len + 1] += num[len] / BASE;
			num[len] %= BASE;
		}
}
