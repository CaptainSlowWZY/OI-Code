#include <algorithm>
#include <cstdio>

#define x first
#define y second

typedef std::pair<int, int> Pii;

const int kMaxk = 1e5 + 5;

int K;

class BIT {
private:
	int A[kMaxk];
public:
	void clear() { std::fill(A, A + K + 1, 0); }
	void modify(int p) { for (; p <= K; p += p & -p) ++A[p]; }
	int query(int p) {
		int res = 0;
		for (; p; p &= p - 1) res += A[p];
		return res;
	}
} bit[2];

int n, m, cntl, cntr, cntu, cntd;
int X[kMaxk], Y[kMaxk];
Pii L[kMaxk], R[kMaxk], U[kMaxk], D[kMaxk];
char T[5];

void Solve();

int main() {
	int t;
	for (scanf("%d", &t); t--; ) Solve();
	return 0;
}

void Solve() {
	scanf("%d%d%d", &n, &m, &K);
	cntl = cntr = cntu = cntd = 0;
	for (int i = 0; i < K; i++) {
		scanf("%d%d%s", X + i, Y + i, T);
		switch (T[0]) {
			case 'L': L[cntl++] = {X[i], Y[i]}; break;
			case 'R': R[cntr++] = {X[i], Y[i]}; break;
			case 'U': U[cntu++] = {X[i], Y[i]}; break;
			case 'D': D[cntd++] = {X[i], Y[i]}; break;
		}
	}
	std::sort(R, R + cntr); std::sort(U, U + cntu);
	std::sort(D, D + cntd); std::sort(Y, Y + K);
	for (int i = 0; i < cntr; i++)
		R[i].y = std::lower_bound(Y, Y + K, R[i].y) - Y + 1;
	for (int i = 0; i < cntu; i++)
		U[i].y = std::lower_bound(Y, Y + K, U[i].y) - Y;
	for (int i = 0; i < cntd; i++)
		D[i].y = std::lower_bound(Y, Y + K, D[i].y) - Y + 1;
	bit[0].clear(), bit[1].clear();
	long long ans = 1;
	int pu = 0, pd = 0;
	for (int i = 0; i < cntr; i++) {
		while (pu < cntu && U[pu].x < R[i].x)
			ans += bit[0].query(K - U[pu++].y);
		while (pd < cntd && D[pd].x < R[i].x)
			ans += bit[1].query(D[pd++].y);
		bit[0].modify(K - R[i].y + 1); bit[1].modify(R[i].y);
	}
	while (pu < cntu) ans += bit[0].query(K - U[pu++].y);
	while (pd < cntd) ans += bit[1].query(D[pd++].y);
	for (int i = 0; i < cntl; i++) L[i].x = -L[i].x;
	for (int i = 0; i < cntu; i++) U[i].x = -U[i].x;
	for (int i = 0; i < cntd; i++) D[i].x = -D[i].x;
	std::sort(L, L + cntl);
	for (int i = 0; i < cntl; i++)
		L[i].y = std::lower_bound(Y, Y + K, L[i].y) - Y + 1;
	std::reverse(U, U + cntu); std::reverse(D, D + cntd);
	bit[0].clear(), bit[1].clear();
	pu = pd = 0;
	for (int i = 0; i < cntl; i++) {
		while (pu < cntu && U[pu].x < L[i].x)
			ans += bit[0].query(K - U[pu++].y);
		while (pd < cntd && D[pd].x < L[i].x)
			ans += bit[1].query(D[pd++].y);
		bit[0].modify(K - L[i].y + 1); bit[1].modify(L[i].y);
	}
	while (pu < cntu) ans += bit[0].query(K - U[pu++].y);
	while (pd < cntd) ans += bit[1].query(D[pd++].y);
	printf("%lld\n", ans);
}
