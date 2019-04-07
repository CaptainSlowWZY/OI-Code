#include <cstdio>
#include <algorithm>

typedef long long LL;

struct Linebas {
	LL bas[62];
	bool extend(LL x);
} B;

int type, n, tot0;

int main() {
	scanf("%d%d", &type, &n);
	LL Ai;
	for (int i = 0; i < n; i++) {
		scanf("%lld", &Ai);
		if (!B.extend(Ai)) ++tot0;
	}

	LL ans = 0;
	if (type) {
		LL _xor = 0;
		for (int i = 0; i <= 60; i++) _xor ^= B.bas[i];
		ans = _xor * (tot0 + 1);
		int top = 60;
		for (; top >= 0 && !B.bas[top]; --top);
		for (int i = top - 1; i >= 0; i--) {
			if (!B.bas[i]) continue;
			ans += B.bas[i] ^ _xor;
		}
	} else {	
		for (int i = 0; i <= 60; i++) ans += B.bas[i];
	}

	printf("%lld\n", ans);
	return 0;
}


bool Linebas::extend(LL x) {
	for (int i = 60; i >= 0 && x; i--) {
		if (x >> i & 1 ^ 1) continue;
		if (bas[i]) {
			x ^= bas[i];
			continue;
		}
		for (int j = 0; j < i; j++) {
			if (x >> j & 1 && bas[j]) x ^= bas[j];
		}
		bas[i] = x;
		for (int j = 60; j > i; j--) {
			if (bas[j] >> i & 1) bas[j] ^= x;
		}
		return true;
	}
	return false;
}
