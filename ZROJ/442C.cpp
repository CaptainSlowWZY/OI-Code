// #pragma GCC optimize(2)
#include <algorithm>
#include <cstdio>

#define fir first
#define sec second

typedef long long LL;
typedef std::pair<int, LL> Pil;

const int kBit = 23, kMaxa = 1 << 23, kMaxn = 1e5 + 5;

int n, q, A[kMaxn];

namespace solver1 { void Solve(); }
namespace solver2 { void Solve(); }
namespace solver3 { void Solve(); }

int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; ++i) scanf("%d", A + i);
	if (q == 1) solver1::Solve();
	if (q == 2) solver2::Solve();
	if (q == 3) solver3::Solve();
	return 0;
}

namespace solver1 {
	int flag[kMaxn];

	void Solve() {
		int ans = 0;
		for (int cnt, i = kBit - 1; i >= 0; --i) {
			for (int j = cnt = 0; j < n; ++j) {
				if (flag[j]) continue;
				if (A[j] >> i & 1) ++cnt;
			}
			if (cnt >= 2) {
				ans |= 1 << i;
				for (int j = 0; j < n; ++j) {
					if (A[j] >> i & 1) continue;
					flag[j] = 1;
				}
			}
		}
		LL way = 0;
		for (int i = 0; i < n; ++i)
			way += 1 - flag[i];
		way = way * (way - 1) >> 1;	
		printf("%d %lld\n", ans, way);
	}
}

namespace solver2 {
	namespace trie {
		int A[kMaxn * kBit][2], cnt[kMaxn * kBit], size;

		void Insert(int x) {
			int cur = 0;
			for (int i = kBit - 1, c; i >= 0; --i) {
				if (!A[cur][c = x >> i & 1])
					A[cur][c] = ++size;
				cur = A[cur][c];
			} ++cnt[cur];
		}
		Pil Query(int x) {
			int cur = 0;
			Pil res = {0, 0};
			for (int c, i = kBit - 1; i >= 0; --i) {
				if (A[cur][c = x >> i & 1 ^ 1]) {
					res.fir |= 1 << i;
					cur = A[cur][c];
				} else cur = A[cur][c ^ 1];
			} res.sec = cnt[cur];
			return res;
		}
	}
	void Solve() {
		for (int i = 0; i < n; ++i) trie::Insert(A[i]);
		Pil ans = {0, 0};
		for (int i = 0; i < n; ++i) {
			Pil tmp = trie::Query(A[i]);
			if (tmp.fir > ans.fir)
				ans = tmp;
			else if (tmp.fir == ans.fir)
				ans.sec += tmp.sec;
		} ans.sec >>= 1;
		printf("%d %lld\n", ans.fir, ans.sec);
	}
}

namespace solver3 {
	LL B[kMaxa];

	void Fmt(LL A[], int b, int f) {
		for (int i = 0, lim = 1 << b; i < b; ++i)
			for (int j = 0; j < lim; ++j)
				if (j >> i & 1) A[j] += f * A[j ^ 1 << i];
	}
	void Solve() {
		int maxa = 0;
		for (int i = 0; i < n; ++i) {
			++B[A[i]]; 
			maxa = std::max(maxa, A[i]);
		}
		int b = 0, x = 1;
		while (x <= maxa) { ++b; x <<= 1; }
		Fmt(B, b, 1);
		for (int i = 0; i < (1 << b); ++i) B[i] *= B[i];
		Fmt(B, b, -1);
		for (int i = 0; i < n; ++i) --B[A[i]];
		int ans = (1 << b) - 1;
		while (ans && !B[ans]) --ans;
		printf("%d %lld\n", ans, B[ans] >> 1);
	}
}
