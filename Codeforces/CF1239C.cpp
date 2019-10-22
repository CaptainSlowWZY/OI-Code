#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

const int kMaxn = 1e5 + 5;

int n, p;
int A[kMaxn], id[kMaxn], que[kMaxn];
long long ans[kMaxn];
std::priority_queue<int, std::vector<int>, std::greater<int> > wait;

inline bool CmpA(int a, int b) {
	return A[a] == A[b] ? a < b : A[a] < A[b];
}

int main() {
	scanf("%d%d", &n, &p);
	for (int i = 0; i < n; ++i) {
		scanf("%d", A + i); id[i] = i;
	} std::sort(id, id + n, CmpA);
	int hd = 0, tl = 0, cur = 0;
	long long la = 0;
	while (hd < tl || cur < n || !wait.empty()) {
		if (hd == tl) {
			if (wait.empty()) que[tl++] = id[cur++];
			else { que[tl++] = wait.top(); wait.pop(); }
		} ans[que[hd]] = la = std::max(la, 1ll * A[que[hd]]) + p;
		++hd;
		while (cur < n && A[id[cur]] <= la) {
			if (tl && id[cur] < que[tl - 1])
				que[tl++] = id[cur++];
			else
				wait.push(id[cur++]);
		}
	}
	for (int i = 0; i < n; ++i) printf("%lld ", ans[i]);
	putchar('\n'); return 0;
}
