#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>

const int kMaxn = 1e5 + 5, kMaxm = 1e3 + 5, kInf = 0x3f3f3f3f;

int n, m, k, sum;
int A[kMaxn], B[kMaxm], seq[kMaxm];

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
bool Check(int x, int sz);
int Solve(int x, int ub);

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < n; ++i) {
		scanf("%d", A + i);
		sum += A[i];
	}
	srand(time(NULL));
	for (int i = 0; i < m; ++i) seq[i] = i;
	std::random_shuffle(seq, seq + m);
	int ans = sum + 1;
	for (int i = 0; i < m; ++i) {
		if (!Check(seq[i], ans - 1)) continue;
		ans = Solve(seq[i], ans - 1);
	} printf("%d\n", ans);
	return 0;
}

bool Check(int x, int sz) {
	int rem = sz, kk = k - 1;
	for (int i = 0, ai; i < n; ++i) {
		if (sz < (ai = (A[i] + x) % m)) return false;
		if (rem < ai) {
			rem = sz;
			if (--kk < 0) return false;
		} rem -= ai;
	} return true;
}

int Solve(int x, int ub) {
	for (int mid, lb = -1; ub - lb > 1; ) {
		mid = (lb + ub) / 2;
		if (Check(x, mid)) ub = mid;
		else lb = mid;
	} return ub;
}
