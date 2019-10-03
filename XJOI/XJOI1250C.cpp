#include <algorithm>
// #include <cassert>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <vector>

#define fir first
#define sec second
#define pb push_back
#define pch putchar

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef std::pair<LL, int> Pli;
typedef std::pair<int, LL> Pil;
typedef std::pair<LL, LL> Pll;
typedef std::vector<int> Vi;
typedef std::vector<LL> Vl;

const int kMaxn = 1e5 + 5;

typedef int IAr[kMaxn];

int n, k, totp;
IAr smu, P, phi, np;

LL Count(int y, int x);
LL Jose(LL n, LL m);

int main() {
	scanf("%d%d", &n, &k);

	smu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!np[i]) { P[totp++] = i; smu[i] = -1; }
		for (int j = 0, d; j < totp && (d = i * P[j]) <= n; j++) {
			np[d] = 1;
			if (i % P[j] == 0) { smu[d] = 0; break; }
			smu[d] = -smu[i];
		} smu[i] += smu[i - 1];
	}
	LL per = 1;
	for (int i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		per += (LL)(smu[j] - smu[i - 1]) * (n / i) * (n / i);
	}
	LL la = Jose(per << 2, k), num;
	if (la % per == 0) {
		if (!la) printf("%d %d\n", n, 0);
		else if (la == per) printf("%d %d\n", 0, n);
		else if (la == per << 1) printf("%d %d\n", -n, 0);
		else printf("%d %d\n", 0, -n);
		return 0;
	}
	Pii drc;
	if (la < per) {
		num = la - 1; drc = {1, 1};
	} else if (la < per * 2) {
		num = 2 * per - la - 1; drc = {-1, 1};
	} else if (la < per * 3) {
		num = la - per * 2 - 1; drc = {-1, -1};
	} else {
		num = 4 * per - la - 1; drc = {1, -1};
	}
	int l1 = 0, l2 = 1, r1 = 1, r2 = 0, ans1, ans2; // 1 - y, 2 - x
	++num;
	for (int m1, m2; l1 <= n && l2 <= n && r1 <= n && r2 <= n; ) {
		m1 = l1 + r1, m2 = l2 + r2;
		if (m1 > n || m2 > n) break;
		LL tmp = Count(m1, m2);
		if (tmp >= num) {
			r1 = m1, r2 = m2;
			ans1 = m1, ans2 = m2;
		} else { l1 = m1, l2 = m2; }
	}
	int k = std::min(n / r1, n / r2);
	printf("%d %d\n", ans2 * drc.fir * k, ans1 * drc.sec * k);
	return 0;
}

LL F(LL a, LL b, LL c, LL n) {
	if (!a) return 1ll * b / c * (n + 1);
	if (a >= c || b >= c)
		return n * (n + 1) / 2 * (a / c) +
		(n + 1) * (b / c) + F(a % c, b % c, c, n);
	LL m = (a * n + b) / c;
	return n * m - F(c, c - b - 1, a, m - 1);
}

LL Count(int y, int x) {
	LL res = 0;
	for (int i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		LL lim = n / i,
			c = std::min(lim, /*lim * x % y == 0 ?
				lim * x / y - 1 : */lim * x / y);
		res += (LL)(smu[j] - smu[i - 1]) * 
			(F(y, 0, x, c) + (lim - c) * lim);
	} return res;
}

struct Mem { LL nn, kk; int stat; };

LL Jose(LL n, LL k) {
	LL r = 0;
	static std::vector<Mem> st;
	while (1) {
		if (n == 1) { r = 0; break; }
		if (k == 1) { r = n - 1; break; }
		if (k > n) { st.pb({n, k, 0}); --n; }
		else { st.pb({n, k, 1}); n -= n / k; }
	}
	for (auto it = st.rbegin(); it != st.rend(); ++it) {
		n = it->nn, k = it->kk;
		if (it->stat) {
			r -= n % k;
			if (r < 0) r += n;
			else r += r / (k - 1);
		} else r = (r + k) % n;
	} return r;
}