#include <algorithm>
#include <cstdio>

using std::max;

const int kMaxn = 3e5 + 10, kLg3 = 12;

typedef long long LL;
typedef LL LAr[kMaxn];

int n, m;
int F[kLg3][kMaxn], cnt[kMaxn], num[kMaxn], pw3[kLg3];
LAr H, mul[kLg3], add[kLg3], ned[kLg3];

inline LL Div(LL x, LL y) {
	return (x + y - 1) / y;
}
int Exped(int u, LL f, int & num);

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", &ned[0][i]);
//	H[0] = 0x7fffffffffffffff;
	for (int i = 2, ai; i <= n; i++) {
		LL Vi;
		scanf("%d%d%lld", &F[0][i], &ai, &Vi);
		if (ai) mul[0][i] = Vi;
		else { mul[0][i] = 1, add[0][i] = Vi; }
	}

	F[0][1] = n + 1, mul[0][1] = 1;
	for (int i = pw3[0] = 1; i < kLg3; i++) pw3[i] = pw3[i - 1] * 3;
	for (int i = 0; i + 1 < kLg3; i++) {
		for (int u = 1, f1, f2; u <= n; u++) {
			F[i + 1][u] = F[i][f2 = F[i][f1 = F[i][u]]];
			if (!F[i + 1][u] || !f1 || !f2) continue;
			mul[i + 1][u] = mul[i][u] * mul[i][f1] * mul[i][f2];
			add[i + 1][u] = mul[i][f2] * mul[i][f1] * add[i][u] +
				add[i][f1] * mul[i][f2] + add[i][f2];
			ned[i + 1][u] = max(max(ned[i][u],
					Div(ned[i][f1] - add[i][u], mul[i][u])),
					Div(Div(ned[i][f2] - add[i][f1], mul[i][f1])
						- add[i][u], mul[i][u]));
		}
	}

	LL Si;
	for (int i = 0, Ci; i < m; i++) {
		scanf("%lld%d", &Si, &Ci);
		++cnt[Exped(Ci, Si, num[i])];
	}

	for (int i = 1; i <= n; i++) printf("%d\n", cnt[i]);
	for (int i = 0; i < m; i++) printf("%d\n", num[i]);
	return 0;
}

int Exped(int u, LL f, int & num) {
	num = 0;
	for (int i = kLg3 - 1; i >= 0; i--) {
		if (!F[i][u]) continue;
		if (f >= ned[i][u]) {
			(f *= mul[i][u]) += add[i][u];
			u = F[i][u], num += pw3[i], ++i;
		}
	}
	return u;
}
