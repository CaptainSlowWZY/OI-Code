#include <bits/stdc++.h>

class Bit_Set {
private:
	static const int ArSize = 235/* The size of array*/;
	static const int CellSize = 30/* The size of cell*/;
	int Set[ArSize];
public:
	Bit_Set() {/*  memset(Set, 0, sizeof Set);  */}
	void clear() { memset(Set, 0, sizeof Set); }
	int bit(int ind) const {
//	index should base from 1
		--ind;
		return Set[ind / CellSize] >> ind % CellSize & 1;
	}
	void set_bit(int ind, int num) {
		--ind;
		if (num) Set[ind / CellSize] |= 1 << ind % CellSize;
		else Set[ind / CellSize] &= ~(1 << ind % CellSize);
	}
	void unite(const Bit_Set & b1, const Bit_Set & b2) {
		for (int i = 0; i < ArSize; i++) Set[i] = b1.Set[i] ^ b2.Set[i];
	}
	void prodc(const Bit_Set & b1, const Bit_Set & b2) {
		for (int i = 0; i < ArSize; i++) Set[i] = b1.Set[i] & b2.Set[i];
	}
	int query(const Bit_Set & b) const;
} ST[100010], ORG[7010], FUCK[7010];

int N, Q, mu[7100], flag[7100], totp, P[7100];

namespace FastIO {
	template <typename T>
	void read(T & x) {
		x = 0; register char ch = getchar();
		for (; ch < '0' || ch > '9'; ch = getchar());
		for (; ch >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + (ch ^ '0'), ch = getchar());
	}
}
void init();

int main() {
	init();
	using FastIO::read;
	read(N), read(Q);
	for (int o, a, b, c; Q--; ) {
		read(o);
		switch (o) {
			case 1	:
				read(a), read(b);
				ST[a] = ORG[b];
				break;
			case 2	:
				read(a), read(b), read(c);
				ST[a].unite(ST[b], ST[c]);
				break;
			case 3	:
				read(a), read(b), read(c);
				ST[a].prodc(ST[b], ST[c]);
				break;
			case 4	:
				read(a), read(b);
				putchar('0' ^ ST[a].query(FUCK[b]));
		}
	}
	putchar('\n');
	return 0;
}

void init() {
	mu[1] = 1;
	for (int i = 2; i <= 7000; i++) {
		if (!flag[i]) P[totp++] = i, mu[i] = -1;
		for (int j = 0, pd; j < totp && (pd = i * P[j]) <= 7000; j++) {
			flag[pd] = 1;
			if (i % P[j] == 0) {
				mu[pd] = 0;
				break;
			}
			mu[pd] = -mu[i];
		}
	}
	for (int i = 1; i <= 7000; i++)
		for (int j = i; j <= 7000; j += i) {
			ORG[j].set_bit(i, 1);
			if (mu[j / i]) FUCK[i].set_bit(j, 1);
		}
}

int Bit_Set::query(const Bit_Set & b) const {
	int ret = 0;
	for (int i = 0; i < ArSize; i++)
		ret += __builtin_popcount(Set[i] & b.Set[i]);
	return ret % 2;
}