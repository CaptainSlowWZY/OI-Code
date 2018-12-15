// XJOI 1062 1
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>

const int MAXN = 2e6;

typedef long long LL;
typedef std::pair<LL, int> PLi;
typedef int IntArr[MAXN + 10];

int N;
IntArr X, Y, Z;
LL SEED, tot;
PLi B[MAXN + 5];

inline LL rd() {
	return SEED = ((SEED * 19260817) ^ 233333 ^ (SEED >> 5)) & ((1 << 30) - 1);
}
void init();
void renum(int [], int [], int []);
void count(int [], int []);

int main() {
	scanf("%d%lld", &N, &SEED);
	init();

	renum(X, Y, Z);
	renum(Y, X, Z);
	renum(Z, X, Y);
	count(X, Y);
	count(Y, Z);
	count(X, Z);

	printf("%lld\n", (LL)N * (N - 1) - tot >> 1);

	return 0;
}

namespace BIT {
	IntArr T;

	inline void init() {
		memset(T, 0, sizeof T);
	}
	void add(int p, int d = 1) {
		for (; p <= N; p += p & -p) T[p] += d;
	}
	int query(int p) {
		int ret = 0;
		for (; p > 0; p &= p - 1) ret += T[p];
		return ret;
	}
}

void init() {
	for (int i = 0; i < N; i++) X[i] = rd() % N;
	for (int i = 0; i < N; i++) Y[i] = rd() % N;
	for (int i = 0; i < N; i++) Z[i] = rd() % N;
}

void renum(int a[], int b[], int c[]) {
	for (int i = 0; i < N; i++) B[i] = PLi(a[i] * (LL)(1e8) + b[i] + c[i], i);
	std::sort(B, B + N);
	for (int i = 0; i < N; i++) a[B[i].second] = i + 1;
}

void count(int a[], int b[]) {
	BIT::init();
	static IntArr A;
	for (int i = 0; i < N; i++) A[a[i]] = b[i];
	for (int i = N; i > 0; i--) {
		tot += BIT::query(A[i]);
		BIT::add(A[i]);
	}
}
