// hard thinking!
#include <algorithm>
#include <cstdio>
#include <cstring>

const int kMaxn = 1e5 + 10;

typedef long long LL;
typedef int IAr[kMaxn];

int n;
IAr DP[60], sum0, sum1, id;
LL A[kMaxn];

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
void Sort(int);

int main() {
	scanf("%d", &n);
	LL maxa = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", A + i);
		maxa = std::max(maxa, A[i]);
	}
	
	for (int i = 1; i <= n; i++) {
		A[i] = maxa - A[i], id[i] = i;
	}
	memset(DP, 0x3f, sizeof DP);
	DP[0][0] = 0;
	for (int i = 0; i < 59; i++) {
		if (i) Sort(i - 1);
		for (int j = 1; j <= n; j++) {
			sum0[j] = sum0[j - 1] + (A[id[j]] >> i & 1 ^ 1);
			sum1[j] = sum1[j - 1] + (A[id[j]] >> i & 1);
		}
		for (int j = 0; j <= n; j++) {
			// place 0, only the 1 bit that carried would carry
			UMin(DP[i + 1][sum1[n] - sum1[n - j]],
					DP[i][j] + sum1[n - j] + sum0[n] - sum0[n - j]);
			// place 1, all the 1 bit carry
			// only 0 bit that uncarried wouldn't carry
			UMin(DP[i + 1][n - sum0[n - j]],
					DP[i][j] + sum0[n - j] + sum1[n] - sum1[n - j]);
		}
	}
	printf("%d\n", DP[59][0]);
	return 0;
}

void Sort(int k) {
	static IAr buf;
	int back = 0;
	for (int i = 1; i <= n; i++) {
		if (A[id[i]] >> k & 1 ^ 1) buf[++back] = id[i];
	}
	for (int i = 1; i <= n; i++) {
		if (A[id[i]] >> k & 1) buf[++back] = id[i];
	}
	for (int i = 1; i <= n; i++) id[i] = buf[i];
}
