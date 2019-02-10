// POJ 2417
// BSGS template
#include <cstdio>
#include <cmath>
#include <utility>

#define fir first
#define sec second

typedef long long LL;
typedef std::pair<LL, LL> PLL;

class Hashmap {
private:
	static const int ARSZ = 5e4 + 2000;
	static const int HSHV = 51031;
	PLL tb[ARSZ];
public:
	Hashmap() {}
	void clear() {
		for (int i = 0; i < ARSZ; i++) tb[i] = PLL(0, 0);
	}
	void insert(LL key, LL val) {
		LL k = key % HSHV;
		for (; k < ARSZ && tb[k].fir; ++k >= ARSZ ? k -= ARSZ : 0)
			if (tb[k].fir == key) return;
		tb[k] = PLL(key, val);
	}
	LL operator[](LL key) const {
		LL k = key % HSHV;
		for (; k < ARSZ && tb[k].fir != key; ++k >= ARSZ ? k -= ARSZ : 0)
			if (!tb[k].fir) return -1;
		return tb[k].sec;
	}
} mp;

LL P, A, B;

void BSGS();

int main() {
	while (scanf("%lld%lld%lld", &P, &A, &B) == 3) BSGS();

	return 0;
}

void extgcd(LL a, LL b, LL & x, LL & y) {
	if (b) {
		extgcd(b, a % b, y, x);
		y -= a / b * x;
	}
	else { x = 1, y = 0; }
}

LL inv(LL a) {
	LL x, y;
	extgcd(a, P, x, y);
	return (x % P + P) % P;
}

void BSGS() {
	LL M = (LL)ceil(sqrt(P + 0.5));
	LL pw = 1;
	mp.clear();
	for (LL i = 0; i < M; i++, (pw *= A) %= P) mp.insert(pw, i);
	LL k = inv(pw);
	pw = B;
	for (LL i = 0, tmp; i < M; i++, (pw *= k) %= P)
		if (~(tmp = mp[pw])) {
			printf("%lld\n", i * M + tmp);
			return;
		}
	puts("no solution");
}
