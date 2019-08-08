#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define fir first
#define sec second
#define pb push_back

const int kMaxn = 15;

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef int IAr[kMaxn];

const int kInf = 0x3f3f3f3f;
const LL kInf64 = 0x3f3f3f3f3f3f3f3f;

template <typename T> inline
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
template <typename T> inline
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}
inline LL Calc(int gx, int gy, int x, int y) {
//	printf("    calc [%d, %d] x = %d, y = %d\n", gx, gy, x, y);
	if (x > gx || y > gy) return 0;
	return 1ll * ((gx - x) / 60 + 1) * ((gy - y) / 60 + 1);
}

int n, m, nx, ny;
IAr X, X0, Y, Y0, mod, rem;
int cnt[65][65];

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d%d", X + i, Y + i, mod + i, rem + i);
			X0[i] = X[i], Y0[i] = Y[i];
		}
		nx = ny = n;
		X[nx++] = 0, X[nx++] = m, Y[ny++] = 0, Y[ny++] = m;
		std::sort(X, X + nx); std::sort(Y, Y + ny);
		nx = std::unique(X, X + nx) - X, ny = std::unique(Y, Y + ny) - Y;
		LL ans = 0;
		for (int i = 0; i + 1 < nx; i++) {
			for (int j = 0; j + 1 < ny; j++) {
				int x0 = X[i], x1 = i + 2 == nx ? m : X[i + 1] - 1,
					y0 = Y[j], y1 = j + 2 == ny ? m : Y[j + 1] - 1;
			//	printf(" X[%d, %d], Y[%d, %d]\n", x0, x1, y0, y1);
				memset(cnt, 0, sizeof cnt);
				for (int x = 0; x < 60; x++) {
					for (int y = 0; y < 60; y++) {
						for (int k = 0; k < n; k++) {
							int r = (llabs((LL)x0 + x - X0[k]) +
								llabs((LL)y0 + y - Y0[k])) % mod[k];
							if (r == rem[k]) ++cnt[x][y];
						}
					}
				}
				for (int x = 0; x < 60; x++) {
					for (int y = 0; y < 60; y++) {
						if (cnt[x][y] != n) continue;
						ans += Calc(x1 - x0, y1 - y0, x, y);
					}
				}
			}
		} printf("%lld\n", ans);
	} return 0;
}
