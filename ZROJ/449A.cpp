#include <algorithm>
#include <cstdio>
#include <vector>

#define pb push_back
#define SZ(_) (int)_.size()

int n, P[100010];
std::vector<int> pos;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", P + i);
	pos.pb(P[0] - 1);
	for (int i = 1; i < n; ++i)
		if (P[i] != P[i - 1] + 1) pos.pb(P[i] - 1);
	int la = 0;
	for (auto i : pos) P[i] = ++la;
	std::reverse(pos.begin(), pos.end());
	for (int i = 0, j = 0; i < n; ++i) {
		if (j < SZ(pos) && i == pos[j]) {
			++j; continue;
		} P[i] = ++la;
	}
	for (int i = 0; i < n; ++i) printf("%d ", P[i]);
	puts(""); return 0;
}
