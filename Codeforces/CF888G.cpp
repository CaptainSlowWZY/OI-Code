#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

typedef long long LL;

const int kMaxn = 2e5 + 10, kInf = 0x7fffffff;

int n;

namespace trie {
	LL ans;

	void Insert(int val_);
	void Dfs(int u);
	inline LL Solve() {
		Dfs(0);
		return ans;
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0, ai; i < n; i++) {
		scanf("%d", &ai);
		trie::Insert(ai);
	}

	printf("%lld\n", trie::Solve());
	return 0;
}

namespace trie {
	int size = 1, top, T[kMaxn << 5][2], sz[kMaxn << 5], S[40];
	LL mxor, ret0;

	void Insert(int val_) {
		static int num[32];
		for (int i = 0; i < 30; i++) num[i] = val_ >> i & 1;
		int u = 0;
		for (int i = 29, bit; i >= 0; i--) {
			if (!T[u][bit = num[i]]) {
				memset(T[size], 0, sizeof T[size]);
				T[u][bit] = size++;
			}
			u = T[u][bit];
		}
		sz[u] = 1;
	}
	void Calc(int u0, int u1) {
		if (T[u0][0]) {
			S[top++] = 0;
			Calc(T[u0][0], u1);
		}
		if (T[u0][1]) {
			S[top++] = 1;
			Calc(T[u0][1], u1);
		}
		if (T[u0][0] || T[u0][1]) {
			--top;
			return;
		}
		LL ret = 1;
		for (int i = 0; i < top; i++) {
			ret <<= 1;
			if (T[u1][S[i]]) u1 = T[u1][S[i]];
			else {
			//	assert(T[u1][S[i] ^ 1]);
				u1 = T[u1][S[i] ^ 1];
				ret |= 1;
			}
		}
		mxor = std::min(mxor, ret), --top;
	}
	void Dfs(int u) {
		int v1 = T[u][0], v2 = T[u][1];
		if (v1) {
			Dfs(v1);
			sz[u] += sz[v1];
		}
		if (v2) {
			Dfs(v2);
			sz[u] += sz[v2];
			if (v1) {
				mxor = kInf;
				if (sz[v1] < sz[v2]) Calc(v1, v2);
				else Calc(v2, v1);
				ans += mxor, top = 0;
			}
		}
	}
}
