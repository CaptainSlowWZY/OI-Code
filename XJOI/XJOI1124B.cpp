#include <cstdio>
#include <cctype>
#include <algorithm>

const int kMaxn = 4e4, kMaxv = 6e5, kLgN = 16, kInf = 0x3f3f3f3f;

struct Node {
	int set, lson, rson, ans;
	Node(int s_ = 0, int ls_ = 0, int rs_ = 0, int a_ = -1) :
		set(s_), lson(ls_), rson(rs_), ans(a_) {}
} T[kMaxv];

int n, q, C, MOD, size;
int F[kMaxn][kLgN], exs[kMaxn];
int dis[16], mst[1 << 16], minc[1 << 8][1 << 8];

namespace fast_io {
	template <typename T>
		void Read(T & x) {
			register char ch = getchar();
			register bool f = false; x = 0;
			for (; !isdigit(ch); f |= (ch == '-'), ch = getchar());
			for (; isdigit(ch); ch = getchar())
				x = (x << 3) + (x << 1) + (ch ^ '0');
			f ? x = -x : 0;
		}
}
int Mst(int u, int len);

int main() {
	using fast_io::Read;

	Read(n), Read(C);
	// fprintf(stderr, " C = %d\n", C);
	MOD = 1 << C;
	for (int i = 0, xi; i < n; i++) {
		Read(xi);
		exs[xi] = exs[xi + MOD] = 1;
	}
	
//	build dividing-tree
	int len = MOD << 1;
	for (int i = 0; i < len; i++) {
		if (!exs[i]) continue;
		F[i][0] = ++size;
		T[size] = Node(1);
	}
	// fprintf(stderr, " MOD = %d\n",	MOD);
	for (int i = 1, m = 1; m < len; i++, m <<= 1) {
	//	m is half length of current interval
		for (int j = 0, ls, rs; j + m < len; j++) {
			ls = F[j][i - 1], rs = F[j + m][i - 1];
			if (ls + rs == 0) continue;
			F[j][i] = ++size;
			T[size] = Node(T[rs].set << m | T[ls].set, ls, rs);
		}
	}

//	pre-work
//	min-value edge between two small sets
	for (int s = 0, u = 1 << 8; s < u; s++) {
		for (int t = s; t < u; t++) {
			int & ret = minc[s][t];
			ret = kInf;
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++) {
					if (s >> i & 1 && t >> j & 1) {
						ret = std::min(ret, i ^ j);
					}
				}
			minc[t][s] = ret;
		}
	}
//	cost of MST of a small graph
	for (int m = 0, u = 1 << 16; m < u; m++) {
		int v = -1;
		for (int i = 0; i < 16; i++) {
			dis[i] = kInf;
			if (m >> i & 1 && v == -1) v = i;
		}
		int & ret = mst[m];
		if (v == -1) continue;
		dis[v] = 0;
		for (int s = m; s; ) {
			int k = -1;
			for (int i = 0; i < 16; i++) {
				if (s >> i & 1 && (k == -1 || dis[i] < dis[k])) {
					k = i;
				}
			}
			if (k == -1) break;
			ret += dis[k];
			s ^= 1 << k;
			for (int i = 0; i < 16; i++) {
				if (s >> i & 1) {
					dis[i] = std::min(dis[i], k ^ i);
				}
			}
		}
	}

	// fprintf(stderr, " MOD = %d\n",	MOD);
	Read(q);
	int del = 0;
	for (int v; q--; ) {
		Read(v);
		del = (del + MOD - v) % MOD;
		// fprintf(stderr, " id = %d\n", T[F[del][C]].set);
		printf("%d\n", MOD <= 16 ? mst[T[F[del][C]].set] : Mst(F[del][C], MOD));
	}
	return 0;
}

int MinCost(int u0, int u1, int len) {
	if (!u0 || !u1) return kInf;
	if (len == 8) return minc[T[u0].set][T[u1].set];
	int hl = len >> 1;
	int ret = std::min(MinCost(T[u0].lson, T[u1].lson, hl),
						MinCost(T[u0].rson, T[u1].rson, hl));
	if (ret < kInf) return ret;
	return std::min(ret,
			(std::min(MinCost(T[u0].lson, T[u1].rson, hl),
					MinCost(T[u0].rson, T[u1].lson, hl)) + hl));
}

int Mst(int u, int len) {
	if (!u) return 0;
	if (~T[u].ans) return T[u].ans;
	if (len <= 16) return T[u].ans = mst[T[u].set];
	return T[u].ans = Mst(T[u].lson, len >> 1) + Mst(T[u].rson, len >> 1) + 
			(T[u].lson && T[u].rson ? MinCost(T[u].lson, T[u].rson, len >> 1) + (len >> 1) : 0);
}
