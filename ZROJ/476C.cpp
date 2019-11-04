#include <algorithm>
#include <cstdio>
#include <cstring>

const int kMaxn = 2e5 + 5, kInf = 0x3f3f3f3f;

typedef int Arr[kMaxn];
typedef int Tre[kMaxn << 1];

int n, rj;
Arr P, W;
Tre J, D;

int Qry(int, int, int);
void Mdf(int, int, int, int);

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", P + i);
	for (int i = 1; i <= n; ++i) scanf("%d", W + i);
	P[n + 1] = n + 1;
	memset(D, 0x3f, sizeof D);
	int ans = 0;
	for (int i = 1; i <= n + 1; ++i) {
		rj = 0, ans = Qry(1, n + 1, P[i]);
		ans = (ans == kInf ? 0 : ans) + W[i];	
		Mdf(1, n + 1, i, ans);
	} printf("%d\n", ans);
	return 0;
}

inline int Id(int l, int r) { return l + r | l != r; }

#define LSON Id(l, mid)
#define RSON Id(mid + 1, r)

int Gao(int l, int r) {
	int cur = Id(l, r);
	if (rj > J[cur]) return kInf;
	if (l == r) {
		rj = std::max(rj, J[cur]);
		return D[cur];
	} int mid = l + r >> 1, res = kInf;
	if (J[RSON] > rj) res = Gao(mid + 1, r);
	if (J[LSON] > rj) res = std::min(res, Gao(l, mid));
	return res;
}

int Qry(int l, int r, int qr) {
	if (r <= qr) return Gao(l, r);
	int mid = l + r >> 1, res = kInf;
	if (qr > mid) res = Qry(mid + 1, r, qr);
	return std::min(res, Qry(l, mid, qr));
}
	
void Mdf(int l, int r, int p, int v) {
	int cur = Id(l, r);
	if (l == r) return (void)(J[cur] = p, D[cur] = v);
	int mid = l + r >> 1;
	if (P[p] <= mid) Mdf(l, mid, p, v);
	else Mdf(mid + 1, r, p, v);
	J[cur] = std::max(J[LSON], J[RSON]);
}
