#include <cstdio>
#include <cctype>
#include <algorithm>
#include <map>

#define len first
#define way second

typedef long long LL;
typedef std::pair<int, int> Pii;

const int kMaxn = 1e5 + 10, MOD = 1 << 30;

struct Point {
	int x, y, z, id;
	bool operator<(const Point & p) const {
		return z == p.z ? 
			(x == p.x ? y < p.y : x < p.x) :
			z < p.z;
	}
} P[kMaxn];

int n, limz;
Pii DP[kMaxn];
std::map<int, int> mp;

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
template <typename T>
inline void Add(T & x, LL y) {
	x = (x + y) % MOD;
}
inline void Umax(Pii & x, const Pii & y) {
	x.len == y.len ? Add(x.way, y.way) : 
		(x.len < y.len ? (void)(x = y) : (void)0);
}
void Solve(int l, int r);

int main() {
	using fast_io::Read;

	int t;
	for (Read(t); t--; ) {
		Read(n);
		mp.clear();
		for (int i = 0; i < n; i++) {
			Read(P[i].x), Read(P[i].y), Read(P[i].z);
			mp[P[i].y], P[i].id = i;
		}

		std::sort(P, P + n);
		limz = 0;
		for (std::map<int, int>::iterator it = mp.begin();
			it != mp.end(); ++it) {
			it->second = ++limz;
		}
		for (int i = 0; i < n; i++) {
			P[i].y = mp[P[i].y];
			DP[i] = Pii(1, 1);
		}
		Solve(0, n);

		Pii ans(0, 0);
		for (int i = 0; i < n; i++) {
			Umax(ans, DP[i]);
		}
		Add(ans.way, MOD);

		printf("%d %d\n", ans.len, ans.way);
	}

	return 0;
}

int VER;

namespace bit {
	Pii T[kMaxn];
	int ver[kMaxn];

	void Update(int p, const Pii & ret) {
		for (; p <= limz; p += p & -p) {
			if (ver[p] == VER) Umax(T[p], ret);
			else {
				ver[p] = VER, T[p] = ret;
			}
		}
	}
	Pii Query(int p) {
		Pii ret(0, 0);
		for (; p; p &= p - 1) {
			if (ver[p] == VER) Umax(ret, T[p]);
		}
		return ret;
	}
}

inline bool cmp(const Point & pa, const Point & pb) {
	return pa.x == pb.x ? pa.y < pb.y : pa.x < pb.x;
}

void Solve(int l, int r) {
	if (r - l <= 1) return;

	int mid = l + r >> 1;
	Solve(l, mid);
	static Point buf[kMaxn];
	for (int i = l; i < r; i++) {
		buf[i] = P[i];
	}
	int p1 = l, p2 = mid;
	++VER;
	std::sort(buf + l, buf + mid, cmp);
	std::sort(buf + mid, buf + r, cmp);
	for (; p1 < mid && p2 < r; ) {
		using namespace bit;
		if (buf[p1].x <= buf[p2].x) {
			Update(buf[p1].y, DP[buf[p1].id]);
			p1++;
		}
		else {
			Pii cur(Query(buf[p2].y));
			++cur.len;
			Umax(DP[buf[p2++].id], cur);
		}
	}
	for (; p2 < r; p2++) {
		Pii cur(bit::Query(buf[p2].y));
		++cur.len;
		Umax(DP[buf[p2].id], cur);
	}
	Solve(mid, r);
}
