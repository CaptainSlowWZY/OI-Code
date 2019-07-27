#pragma GCC optimize(2)
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <unordered_map>

typedef long long LL;

namespace bsgs {
	LL ExBsgs(LL A, LL B, LL P);
}
	
int main() {
	LL a, p, b;
	while (~scanf("%lld%lld%lld", &a, &p, &b) && a + p + b) {
		LL ans = bsgs::ExBsgs(a, b, p);
		if (~ans) printf("%lld\n", ans);
		else puts("No Solution");
	}
	return 0;
}

namespace bsgs {
	void ExtGcd(LL a, LL b, LL & x, LL & y) {
		if (b) {
			ExtGcd(b, a % b, y, x);
			y -= a / b * x;
		}
		else { x = 1, y = 0; }
	}
	LL Inv(LL a, LL mod) {
		LL x, y;
		ExtGcd(a, mod, x, y);
		return (x % mod + mod) % mod;
	}
	LL Bsgs(LL A, LL B, LL P) {
		LL M = (LL)ceil(sqrt(P + 0.5));
		std::unordered_map<LL, LL> mp;
		LL pw = 1;
		for (LL i = 0; i < M; i++, (pw *= A) %= P)
			if (!mp.count(pw)) mp[pw] = i;
		LL k = Inv(pw, P);
		pw = B;
		for (LL i = 0; i < M; i++, (pw *= k) %= P)
			if (mp.count(pw)) return i * M + mp[pw];
		return -1;
	}
	LL ExBsgs(LL A, LL B, LL P) {
		LL delta = 0;
		for (LL g; (g = std::__gcd(A, P)) != 1; ++delta) {
			if (B == 1) return delta;
			if (B % g) return -1;
			P /= g;
			B = B / g * Inv(A / g, P) % P;
		}
		LL ret = Bsgs(A, B, P);
		if (~ret) return ret + delta;
		return -1;
	}
}
