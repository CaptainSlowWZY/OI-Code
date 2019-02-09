// Codeforces Hello 2019
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <utility>
#include <vector>

#define fir first
#define sec second

const int MAXN = 1e5 + 10;

typedef std::pair<int, int> Pii;
typedef std::vector<int> Vi;

int N, top, A[MAXN], pre[MAXN];
Pii S[MAXN];
Vi LDS[MAXN];
std::vector<Vi> ans;

void solve();

int main() {
	int t;
	for (scanf("%d", &t); t--; ) solve();
	
	return 0;
}

int LIS() {
	top = 0;
	for (int i = 0; i < N; i++)
		if (~A[i]) {
			int p = std::lower_bound(S, S + top, Pii(A[i], -1)) - S;
//			printf(" A[%d] = %d\n", i, A[i]);
			if (p == top) S[top++] = Pii(A[i], i), pre[i] = p ? S[p - 1].sec : -1; 
			else {
				if (p) pre[i] = S[p - 1].sec;
				else pre[i] = -1;
//				printf("  pre = %d\n", pre[i]);
//				if (S[p].fir > A[i])
				{
					S[p] = Pii(A[i], i);
				}
			}
		}
	return top;
}

int calc(int l) {
	int x = (int)sqrt(l + 0.5);
	for (; x * (x + 1) > l * 2; --x);
	for (; x * (x + 1) < l * 2; ++x);
	return x;
}

void solve() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", A + i);
		LDS[i].clear();
	}
	ans.clear();
	int len = N, anscnt = 0;
	for (; len > 0; ) {
		int k = calc(len), l = LIS();
//		printf("len=%d, k=%d, l=%d\n", len, k, l);
		if (l >= k) {
			std::vector<int> V;
			for (int i = S[l - 1].sec; ~i; i = pre[i]) {
				V.push_back(A[i]);
				A[i] = -1;
			}
			top = -1;
			std::reverse(V.begin(), V.end());
			ans.push_back(V);
			++anscnt;
			len -= l;
		}
		else {
			top = 0;
			for (int i = 0; i < N; i++)
				if (~A[i]) {
					int p = std::lower_bound(S, S + top, Pii(A[i], -1)) - S;
					if (p == top) {
						S[top++] = Pii(A[i], -1);
						LDS[top - 1].push_back(A[i]);
					}
					else {
						S[p] = Pii(A[i], -1);
						LDS[p].push_back(A[i]);
					}
				}
			anscnt += top, len = 0;
		}
	}
	
	printf("%d\n", anscnt);
	for (auto & V : ans) {
		printf("%d", (int)V.size());
		for (auto i : V) printf(" %d", i);
		putchar('\n');
	}
	for (int i = 0; i < top; i++) {
		printf("%d", (int)LDS[i].size());
		for (auto j : LDS[i]) printf(" %d", j);
		putchar('\n');
	}
}
