#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <bitset>

const int kMaxn = 1e7 + 5, kSize = 446, kMod = 998244353, kV = 7e6;

inline int Add(int a, int b) { return (a += b) >= kMod ? a - kMod : a; }

typedef int Arr[kMaxn];
typedef std::bitset<kSize> Bits;

int cntp, L, R, lim;
Bits bas[kV + 5];
Arr P, mp, pw2, mxp;

namespace solver1 { void Solve(int); }

int main() {
	int t, N = 1e7;
	lim = sqrt(N + 0.5);
	for (int i = 2; i <= N; ++i) {
		if (!mp[i]) {
			if (i <= lim) bas[i][cntp] = 1;
			mp[i] = i, P[mxp[i] = cntp++] = i;
		}
		for (int j = 0, d; j < cntp && (d = i * P[j]) <= N; ++j) {
			mp[d] = P[j], mxp[d] = mxp[i];
			if (d <= kV) bas[d] = bas[i] ^ bas[P[j]];
			if (!(i % P[j])) break;
		}
	}
	for (int i = pw2[0] = 1; i <= N; ++i) pw2[i] = Add(pw2[i - 1], pw2[i - 1]);
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &L, &R);
		solver1::Solve(t + 1);
	} 
	return 0;
}

namespace solver1 {
	Bits B[kSize], tmp;
	Arr tag, num;

	Bits GetBas(int x) {
		if (x <= kV) return bas[x];
		Bits res;
		for (; x > 1; x /= mp[x]) if (mp[x] <= lim) res ^= bas[mp[x]];
		return res; 
	}
	void Ins(Bits x) {
		for (int i = kSize - 1; ~i; --i) {
			if (!x[i]) continue;
			if (B[i][i]) { x ^= B[i]; continue; }
			for (int j = 0; j < i; ++j) if (B[j][j] && x[j]) x ^= B[j];
			B[i] = x; break;
		}
	}
	inline bool CmP(int a, int b) { return mxp[a] < mxp[b]; }
	void Solve(int time) {
		int size = 0, cntn;
		if (R - L >= 6900) {
			for (int i = L, t; i <= R; ++i) if (P[t = mxp[i]] > lim) {
				if (tag[t] != time) { ++size, tag[t] = time; }
			} size += kSize;
		} else {
			for (int i = cntn = 0; i < kSize; ++i) B[i].reset();
			for (int i = L; i <= R; ++i) num[cntn++] = i;
			std::sort(num, num + cntn, CmP);
			assert(R - L + 1 == cntn);
			for (int i = 0, j; i < cntn; i = j) {
				if (P[mxp[num[i]]] <= lim) {
					Ins(GetBas(num[i])), j = i + 1; continue;
				} ++size;
				for (j = i; j < cntn && mxp[num[j]] == mxp[num[i]]; ++j);
				tmp = GetBas(num[i]);
				for (int k = i + 1; k < j; ++k) Ins(GetBas(num[k]) ^ tmp);
			}
			for (int i = 0; i < kSize; ++i) if (B[i].any()) ++size;
		}
		printf("%d\n", pw2[R - L + 1 - size]);
	}
}
