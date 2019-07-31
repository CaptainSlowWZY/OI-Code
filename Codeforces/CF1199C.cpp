#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <map>

#define fir first
#define sec second

typedef long long LL;
typedef std::pair<int, int> Pii;

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}

int n, I;
std::map<int, int> cnt;
int sum[400010];

int main() {
	scanf("%d%d", &n, &I);
	I <<= 3;
	for (int Ai, i = 0; i < n; i++) {
		scanf("%d", &Ai);
		++cnt[Ai];
	}

	I /= n;
	int pw = 1;
	for (int i = 1; i <= I && pw < n; i++) pw <<= 1;
	int totx = 0;
	for (auto pii : cnt) {
		++totx;
		sum[totx] = sum[totx - 1] + pii.sec;
	}
	int all = sum[totx], ans = 0;
//	printf(" pw = %d\n", pw);
//	printf("all = %d\n", all);
	for (int i = 1; i <= totx; i++) {
		int l = std::max(0, i - pw);
	//	printf(" i = %d, l = %d\n", i, l);
		ans = std::max(ans, sum[i] - sum[l]);
	}
	ans = all - ans;
	printf("%d\n", ans);
	return 0;
}
