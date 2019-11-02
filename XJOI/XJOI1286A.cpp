#include <algorithm>
#include <cstdio>

const int kMaxn = 1e5 + 5;

int n, k, V[kMaxn], Q[kMaxn], flag[kMaxn];

int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i) scanf("%d", V + i);
	std::sort(V, V + n);
	int hd = 0, tl = n, bk = 0;
	while (hd < tl) {
		while (hd < tl && V[hd] + V[tl - 1] <= k)
			flag[hd++] = 1;
		if (hd == tl) break;
		if (hd + 1 == tl) { Q[bk++] = V[hd]; break; }
		Q[bk++] = V[hd++], Q[bk++] = V[--tl]; 
	}
	for (int i = n - 1; i >= 0; --i) if (flag[i]) Q[bk++] = V[i];
//	for (int i = 0; i < n; ++i) printf("%d%c", Q[i], " \n"[i + 1 == n]);
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		++ans; if (i + 1 < n && Q[i] + Q[i + 1] <= k) ++i;
	} printf("%d\n", ans);
	return 0;
}
