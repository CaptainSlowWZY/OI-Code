#include <cstdio>
#include <cmath>
#include <algorithm>
#include <utility>

#define fir first
#define sec second
typedef std::pair<int, int> Pii;

class Hashmap {
private:
	static const int ARSZ = 5e4 + 2000, HS = 51031;
	Pii tb[ARSZ];
public:
	Hashmap() {}
	void clear() {
		for (int i = 0; i < ARSZ; i++) tb[i] = Pii(0, 0);
	}
	void insert(const Pii & p) {
		int i = p.fir % HS;
		for (; i < ARSZ && tb[i].fir; ++i >= ARSZ ? i -= ARSZ : 0)
			if (tb[i].fir == p.fir) return;
		tb[i] = p;
	}
	int operator[](int key) const {
		int i = key % HS;
		for (; i < ARSZ && tb[i].fir != key; ++i >= ARSZ ? i -= ARSZ : 0)
			if (!tb[i].fir) return -1;
		return tb[i].sec;
	}
} mp;

int EXBSGS(int, int, int);

int main() {
	int A, B, P;
	while (scanf("%d%d%d", &A, &P, &B) == 3 && A + P + B) {
		B %= P;
		int ret = EXBSGS(A, B, P);
		if (~ret) printf("%d\n", ret);
		else puts("No Solution");
	}

	return 0;
}

void extgcd(int a, int b, int &x, int &y) {
	if (b) { extgcd(b, a % b, y, x); y -= a / b * x; }
	else { x = 1, y = 0; }
}

int inv(int a, int p) {
	int x, y;
	extgcd(a, p, x, y);
	return (x % p + p) % p;
}

int BSGS(int a, int b, int p) {
	int m = ceil(sqrt(p + 0.5)), pw = 1;
	mp.clear();
	for (int j = 0; j < m; j++, pw = (long long)pw * a % p) mp.insert(Pii(pw, j));
	int t = inv(pw, p);
	pw = b;
	for (int i = 0, tmp; i < m; i++, pw = (long long)pw * t % p)
		if (~(tmp = mp[pw])) return i * m + tmp;
	return -1;
}

int EXBSGS(int a, int b, int P) {
	int d = 0;
	for (int g; (g = std::__gcd(a, P)) != 1; ++d) {
		if (b == 1) return d;
		if (b % g) return -1;
		P /= g, b = b / g * (long long)inv(a / g, P) % P;
	}
	int ret = BSGS(a, b, P);
	return ~ret ? ret + d : -1;
}
