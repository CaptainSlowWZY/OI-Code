#include <algorithm>
#include <cstdio>
#include <cstring>

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

int n, x, y;
int A[100010];
int main() {
	scanf("%d%d%d", &n, &x, &y);
	for (int i = 1; i <= n; i++) scanf("%d", A + i);

	for (int i = 1; i <= n; i++) {
			int flag = 1;
			for (int j = std::max(1, i - x); j < i; j++) 
				flag &= A[j] > A[i];
			for (int j = i + 1; j <= i + y && j <= n; j++)
				flag &= A[j] > A[i];
			if (flag) {
				printf("%d\n", i);
				return 0;
			}
	}
	return 0;
}
