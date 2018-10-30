// separate
#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef DEBUG_MD
	#define debug(format, ...) fprintf(stderr, format, __VA_ARGS__)
#else
	#define debug(format, ...) 0
#endif
#define RG register

const int MAXN = 2010;
const int INF = 0x3f3f3f3f;

int N, M, mn, mx, mnx, mny, A[MAXN][MAXN], vis[MAXN][MAXN];

namespace FastIO {
	template <typename T>
		void read(T & x) {
			RG char ch = getchar();
			for (; ch < '0' || ch > '9'; ch = getchar());
			for (x = 0; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
		}
}
bool check(int d);

int main() {
	using FastIO::read;
	
	read(N), read(M);
	mn = INF, mx = 0;
	for (RG int i = 0; i < N; i++)
		for (RG int j = 0; j < M; j++) {
			read(A[i][j]);
			mx = std::max(mx, A[i][j]);
			if (A[i][j] < mn) {
				mn = A[i][j];
				mnx = i, mny = j;
			}
		}
	debug("mx=%d; mn=%d, (%d, %d)\n", mx, mn, mnx, mny);

	int lb = -1, ub = mx - mn, mid;
	while (ub - lb > 1) {
		// (lb, ub]
		int mid = (lb + ub) / 2;
		if (check(mid)) ub = mid;
		else lb = mid;
	}

	printf("%d\n", ub);
	return 0;
}

bool check(int d) {
	debug("check d=%d\n", d);

	int fail = 0;
	memset(vis, 0, sizeof vis);
	for (int i = mnx; i < N; i++)
		for (int j = mny; j < M; j++) {
			vis[i][j] = 1;
			if (mn + d < A[i][j]) { fail = 1; break; }
		}
	debug(" fail first? %d\n", fail);
	if (!fail) {
		int lb = -1, ub = -1, lx = N - 1, uy = M - 1;		// left-bound, upper-bound
		for (; lb + 1 < mny && lx >= mnx; --lx) {
			int ny = mny - 1;
			for (; ny > lb && mn + d >= A[lx][ny]; --ny) vis[lx][ny] = 1;
			lb = ny;
		}
		for (; ub + 1 < mnx && uy > lb; --uy) {
			int nx = mnx - 1;
			for (; nx > ub && mn + d >= A[nx][uy]; --nx) vis[nx][uy] = 1;
			ub = nx;
		}
		int mn1 = INF, mx1 = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M && !vis[i][j]; j++) {
				mn1 = std::min(mn1, A[i][j]);
				mx1 = std::max(mx1, A[i][j]);
			}
		}
		if (mx1 - mn1 <= d) return true;
	}

	fail = 0;
	memset(vis, 0, sizeof vis);
	for (int i = 0; i <= mnx; i++)
		for (int j = 0; j <= mny; j++) {
			vis[i][j] = 1;
			if (mn + d < A[i][j]) { fail = 1; break; }
		}
	debug(" fail second? %d\n", fail);
	if (!fail) {
		int rb = M, bb = N, rx = 0, by = 0;		// right-bound, bottem-bound
		for (; rb - 1 > mny && rx <= mnx; ++rx) {
			int ny = mny + 1;
			for (; ny < rb && mn + d >= A[rx][ny]; ++ny) vis[rx][ny] = 1;
			rb = ny;
		}
		for (; bb - 1 > mnx && by < rb; ++by) {
			int nx = mnx + 1;
			for (; nx < bb && mn + d >= A[nx][by]; ++nx) vis[nx][by] = 1;
			bb = nx;
		}
		int mn1 = INF, mx1 = 0;
		for (int i = N - 1; i >= 0; i--) {
			for (int j = M - 1; j >= 0 && !vis[i][j]; j--) {
				mn1 = std::min(mn1, A[i][j]);
				mx1 = std::max(mx1, A[i][j]);
			}
		}
		if (mx1 - mn1 <= d) return true;
	}

	fail = 0;
	memset(vis, 0, sizeof vis);
	for (int i = mnx; i < N; i++)
		for (int j = 0; j <= mny; j++) {
			vis[i][j] = 1;
			if (mn + d < A[i][j]) { fail = 1; break; }
		}
	if (!fail) {
		int rb = M, ub = -1, rx = N - 1, uy = 0;		// right-bound, upper-bound
		for (; rb - 1 > mny && rx >= mnx; --rx) {
			int ny = mny + 1;
			for (; ny < rb && mn + d >= A[rx][ny]; ++ny) vis[rx][ny] = 1;
			rb = ny;
		}
		for (; ub + 1 < mnx && uy < rb; ++uy) {
			int nx = mnx - 1;
			for (; nx > ub && mn + d >= A[nx][uy]; --nx) vis[nx][uy] = 1;
			ub = nx;
		}
		int mn1 = INF, mx1 = 0;
		for (int i = 0; i < N; i++) {
			for (int j = M - 1; j >= 0 && !vis[i][j]; j--) {
				mn1 = std::min(mn1, A[i][j]);
				mx1 = std::max(mx1, A[i][j]);
			}
		}
		if (mx1 - mn1 <= d) return true;
	}

	fail = 0;
	memset(vis, 0, sizeof vis);
	for (int i = 0; i <= mnx; i++)
		for (int j = mny; j < M; j++) {
			vis[i][j] = 1;
			if (mn + d < A[i][j]) { fail = 1; break; }
		}
	if (!fail) {
		int lb = -1, bb = N, lx = 0, by = M - 1;		// left-bound, bottem-bound
		for (; lb + 1 < mny && lx <= mnx; ++lx) {
			int ny = mny - 1;
			for (; ny > lb && mn + d >= A[lx][ny]; --ny) vis[lx][ny] = 1;
			lb = ny;
		}
		for (; bb - 1 > mnx && by > lb; --by) {
			int nx = mnx - 1;
			for (; nx < bb && mn + d >= A[nx][by]; ++nx) vis[nx][by] = 1;
			bb = nx;
		}
		int mn1 = INF, mx1 = 0;
		for (int i = N - 1; i >= 0; i--) {
			for (int j = 0; j < M && !vis[i][j]; j++) {
				mn1 = std::min(mn1, A[i][j]);
				mx1 = std::max(mx1, A[i][j]);
			}
		}
		if (mx1 - mn1 <= d) return true;
	}
	return false;
}
