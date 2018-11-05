// BZOJ 4260
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 4e5 + 10;

int N, A[MAXN], lmx[MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			x = 0; register char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
namespace Trie {
	const int TSize = MAXN * 30;
	int son[TSize][2], sz;

	inline void init() {
		sz = 1;
		memset(son[0], 0, sizeof son[0]);
	}
	void insert(int);
	int find_mx(int);
}

int main() {
	using FastIO::read;

	read(N);
	for (int i = 1; i <= N; i++) read(A[i]);
	
	Trie::init();
	int _xor = 0;
	Trie::insert(_xor), lmx[0] = 0;
	for (int i = 1; i <= N; i++) {
		_xor ^= A[i];
		lmx[i] = std::max(lmx[i - 1], Trie::find_mx(_xor));
		Trie::insert(_xor);
	}
	_xor = 0;
	Trie::init();
	Trie::insert(_xor);
	long long ans = lmx[N];
	for (int i = N; i > 0; i--) {
		_xor ^= A[i];
		ans = std::max(ans, (long long)lmx[i - 1] + Trie::find_mx(_xor));
		Trie::insert(_xor);
	}

	printf("%lld\n", ans);
	return 0;
}

namespace Trie {
	inline int New() {
		memset(son[sz], 0, sizeof son[sz]);
		return sz++;
	}

	void insert(int val) {
		int num[31], rt = 0;
		for (int i = 0; i <= 30; i++, val >>= 1) num[i] = val & 1;
		for (int i = 30; i >= 0; i--) {
			if (!son[rt][num[i]]) son[rt][num[i]] = New();
			rt = son[rt][num[i]];
		}
	}

	int find_mx(int val) {
		int num[31], rt = 0, ret = 0;
		for (int i = 0; i <= 30; i++, val >>= 1) num[i] = val & 1;
		for (int i = 30; i >= 0; i--) {
			if (son[rt][num[i] ^ 1]) rt = son[rt][num[i] ^ 1], ret |= 1 << i;
			else rt = son[rt][num[i]];
		}
		return ret;
	}
}
