// BZOJ 1049
// HAOI 2006
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>

typedef long long LL;

const int MAXN = 35005, INF = 0x7f7f7f7f;

int N, B[MAXN], DP[MAXN], F[MAXN];
LL G[MAXN];
std::vector<int> V[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; !isdigit(ch); ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
		}
}

int main() {
	using FastIO::read;
	read(N);
	B[0] = INF;
	for (int i = 1, Ai; i <= N; i++) {
		read(Ai);
		B[i] = Ai - i;
		B[0] = std::min(B[0], B[i]);
		B[N + 1] = std::max(B[N + 1], B[i]);
	}

	int top = 0;
	memset(DP, 0x7f, sizeof DP);
	DP[0] = 0;
	for (int i = 1; i <= N + 1; i++) {
		int l = 0, r = top + 1;
		for (int mid; r - l > 1; ) {	// [l, r)
			mid = l + r >> 1;
			if (DP[mid] <= B[i]) l = mid;
			else r = mid;
		}
		F[i] = l + 1, V[F[i]].push_back(i);
		DP[l + 1] = std::min(DP[l + 1], B[i]);
		if (l + 1 > top) top = l + 1;
	}
	printf("%d\n", N - top + 1);

	V[0].push_back(0);
	for (int i = 1; i <= N + 1; i++) {
		G[i] = 0x3f3f3f3f3f3f3f3f;
		std::vector<int> & cur = V[F[i] - 1];
		for (std::vector<int>::iterator j = cur.begin(); j != cur.end(); ++j) {
			if (*j >= i || B[*j] > B[i]) continue;
			LL w = 0;
			for (int k = *j + 1; k < i; k++) w += abs(B[k] - B[*j]);
			G[i] = std::min(G[i], G[*j] + w);
			for (int k = i - 1; k > *j; k--)
				G[i] = std::min(G[i], G[*j] + (w += abs(B[k] - B[i]) - abs(B[k] - B[*j])));
		}
	}
	printf("%lld\n", G[N + 1]);
	return 0;
}
