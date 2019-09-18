#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define fir first
#define sec second
#define pb push_back

typedef long long LL;
typedef std::pair<int, int> Pii;

const int kInf = 0x3f3f3f3f;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}

int n;
std::vector<int> v1, v2;

int main() {
	scanf("%d", &n);
	if (n % 2 == 0) {
		puts("NO");
		return 0;
	}
	int cur = 1, f = 1;
	n <<= 1;
	while (cur <= n) {
		if (f) {
			v1.pb(cur);
			v2.pb(cur + 1);
		} else {
			v1.pb(cur + 1);
			v2.pb(cur);
		} f ^= 1;
		cur += 2;
	} puts("YES");
	for (auto i : v1) printf("%d ", i);
	for (auto i : v2) printf("%d ", i);
	putchar('\n');
	return 0;
}
