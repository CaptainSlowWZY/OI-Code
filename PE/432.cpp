#include <algorithm>
#include <cstdio>
#include <map>
#include <cassert>

typedef long long LL;
typedef std::pair<LL, LL> Pii;

const int kMod = 1e9;

int totp, np[520000], P[520000], w[520000];
int phi[520000], mu[520000], sp[520000];
std::map<Pii, LL> mp;

LL S(const Pii & p);

int main() {
	LL n = 510510, m = 1e11;
//	m = 1e6;
	mu[1] = phi[1] = sp[1] = w[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!np[i]) {
			P[totp++] = i; phi[i] = i - 1, mu[i] = -1, w[i] = i; 
		}
		for (int j = 0, d; j < totp && (d = i * P[j]) <= n; j++) {
			np[d] = 1;
			if (i % P[j] == 0) {
				phi[d] = phi[i] * P[j], mu[d] = 0, w[d] = w[i];
				break;
			}
			phi[d] = phi[i] * (P[j] - 1);
			mu[d] = -mu[i], w[d] = w[i] * P[j];
		} sp[i] = (sp[i - 1] + phi[i]) % kMod;
	}
	printf("%lld\n", (S(Pii(n, m)) + kMod) % kMod);
	return 0;
}

LL S(const Pii & p) {
	if (p.first == 0 || p.second == 0) return 0;
	if (p.first == 1 && p.second <= 510510) return sp[p.second];
	if (p.second == 1) return phi[p.first];
	if (mp.count(p)) return mp[p];
	LL & res = mp[p], n = p.first, m = p.second; res = 0;
	if (n == 1) {
		res = m & 1 ? ((m + 1) / 2 % kMod * (m % kMod) % kMod) :
			(m / 2 % kMod * ((m + 1) % kMod) % kMod);
	//	printf(" %lld, res %lld\n", m, res);
		for (LL i = 2, j; i <= m; i = j + 1) {
			j = m / (m / i);
			(res -= (j - i + 1) % kMod * S(Pii(1, m / i)) % kMod) %= kMod;
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
