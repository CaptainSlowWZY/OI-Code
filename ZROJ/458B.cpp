#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

#define fi first
#define se second

const int kMaxn = 3e5 + 5, kInf = 0x7f7f7f7f;

typedef std::pair<int, int> Pii;
typedef int Arr[kMaxn];

int n, cx, cy, pv, px, py;
Arr X, Y, iv, ix, iy, vis;
std::priority_queue<Pii, std::vector<Pii>,
	std::greater<Pii> > III, IV;

inline bool CmpV(int a, int b) { return X[a] + Y[a] < X[b] + Y[b]; }
inline bool CmpX(int a, int b) { return X[a] < X[b]; }
inline bool CmpY(int a, int b) { return Y[a] < Y[b]; }
void Update();

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", X + i, Y + i);
		iv[i] = ix[i] = iy[i] = i;
	} std::sort(iv, iv + n, CmpV);
	std::sort(ix, ix + n, CmpX);
	std::sort(iy, iy + n, CmpY);
	cx = cy = 1, pv = px = py = 0; Update();
	for (int t = 0; t < n; ++t, Update()) {
		while (pv < n && (vis[iv[pv]] ||
				X[iv[pv]] <= cx || Y[iv[pv]] <= cy)) ++pv;
		while (!III.empty() && vis[III.top().se]) III.pop();
		while (!IV.empty() && vis[IV.top().se]) IV.pop();
		Pii cur = {kInf, n};
		if (pv < n) cur = std::min(cur, {X[iv[pv]] + Y[iv[pv]] -
				cx - cy, iv[pv]});
		if (!III.empty()) cur = std::min(cur,
				{III.top().fi - cy,	III.top().se});
		if (!IV.empty()) cur = std::min(cur,
				{IV.top().fi - cx, IV.top().se});
		vis[cur.se] = 1;
		cx = std::max(cx, X[cur.se]);
		cy = std::max(cy, Y[cur.se]);
		printf("%d%c", cur.se + 1, " \n"[t + 1 == n]);
	} return 0;
}

void Update() {
	for (; px < n && X[ix[px]] <= cx; ++px)
		III.push({Y[ix[px]], ix[px]});
	for (; py < n && Y[iy[py]] <= cy; ++py)
		IV.push({X[iy[py]], iy[py]});
}
