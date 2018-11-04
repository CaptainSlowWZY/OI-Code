// miku
#include <cstdio>
#include <set>

#define rg register
#define gch getchar
#define pch putchar

typedef std::set<int> MySt;
const int MAXN = 1510;

int N, M, L, R, A[MAXN];
MySt rvsord;

namespace FastIO {
	template <typename T>
		void read(T & x) {
			rg char ch = gch();
			for (; ch < '0' || ch > '9'; ch = gch());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = gch());
		}
}
inline void swap_back(int x) {
	std::swap(A[x], A[x + 1]);
}

int main() {
	using FastIO::read;

	read(N), read(M), read(L), read(R);
	for (rg int i = 1; i <= N; i++) read(A[i]);

	for (rg int i = 1; i < N; i++)
		if (A[i] > A[i + 1]) rvsord.insert(i);
	for (rg int i = 0, li, ri; i < M; i++) {
		read(li), read(ri);
		for (MySt::iterator it = rvsord.lower_bound(li); it != rvsord.end() && *it < ri; it = rvsord.lower_bound(li)) {
			swap_back(*it);
			if (*it > 1 && A[*it - 1] > A[*it]) rvsord.insert(*it - 1);
			if (*it + 1 < N && A[*it + 1] > A[*it + 2]) rvsord.insert(*it + 1);
			rvsord.erase(it);
		}
	}
	
	for (int i = L; i <= R; i++) printf("%d ", A[i]);
	pch('\n');
	return 0;
}

// AC!!!
