#include <algorithm>
#include <cstdio>
#include <map>
#include <cassert>

const int kMod = 1e9 + 7, kMaxn = 1e6;

typedef long long LL;
typedef std::pair<int, int> Pii;
typedef int IAr[kMaxn + 10];

int totp, n, m;
IAr np, P, w, phi, sp;
std::map<Pii, LL> mp;

LL S(const Pii & p);

int main() {
	phi[1] = sp[1] = w[1] = 1;
	for (int i = 2; i <= kMaxn; i++) {
		if (!np[i]) { P[totp++] = i; phi[i] = i - 1, w[i] = i; }
		for (int j = 0, d; j < totp && (d = i * P[j]) <= kMaxn; j++) {
			np[d] = 1;
			if (i % P[j] == 0) {
				phi[d] = phi[i] * P[j], w[d] = w[i];
				break;
			}
			phi[d] = phi[i] * (P[j] - 1), w[d] = w[i] * P[j];
		} sp[i] = (sp[i - 1] + phi[i]) % kMod;
	}
	scanf("%d%d", &n, &m);
	if (n > m) std::swap(n, m);
	LL ans = 0;
	for (int i = 1; i <= n; i++) (ans += S(Pii(i, m))) %= kMod;
	printf("%lld\n", (ans + kMod) % kMod);
	return 0;
}

LL S(const Pii & p) {
	if (p.first == 0 || p.second == 0) return 0;
	if (p.first == 1 && p.second <= kMaxn) return sp[p.second];
	if (p.second == 1) return phi[p.first];
	if (mp.count(p)) return mp[p];
	LL & res = mp[p]; res = 0;
	int n = p.first, m = p.second;
	if (n == 1) {
		res = m & 1 ? (1ll * (m + 1) / 2 * m % kMod) :
			(1ll * m / 2 * (m + 1) % kMod);
	//	printf(" %lld, res %lld\n", m, res);
		for (int i = 2, j; i <= m; i = j + 1) {
			j = m / (m / i);
			(res -= 1ll * (j - i + 1) * S(Pii(1, m / i)) % kMod) %= kMod;
		}
	} else {
		LL t = n / w[n]; n = w[n];
		for (int i = 1; i * i <= n; i++) {
			if (n % i) continue;
			(res += 1ll * phi[n / i] * S(Pii(i, m / i)) % kMod) %= kMod;
			if (i * i != n) {
				(res += 1ll * phi[i] *
				 S(Pii(n / i, m / (n / i))) % kMod) %= kMod;
			}
		} (res *= t) %= kMod;
	} return res;
}
