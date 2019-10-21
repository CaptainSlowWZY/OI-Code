#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>

#define fir first
#define sec second
#define SZ(_) (int)_.size()

typedef std::pair<int, int> Pii;

const int kMaxn = 2e5 + 5, kInf = 0x3f3f3f3f;

int n, m, lens, lent;
int A[kMaxn], DP[kMaxn], mxl[kMaxn];
char S[kMaxn], T[kMaxn];
Pii que[kMaxn];
std::vector<Pii> vec;
std::multiset<int> val;

namespace smt {
	void Build(int l, int r);
	int Query(int l, int r, int ql, int qr);
}
template <typename T> inline 
void UMax(T & x, const T & y) {
	if (x < y) x = y;
}
template <typename T> inline 
void UMin(T & x, const T & y) {
	if (x > y) x = y;
}
inline bool Cmp1(const Pii & a, const Pii & b) {
	return a.sec == b.sec ? a.fir < b.fir : a.sec < b.sec;
}
inline bool Cmp2(const Pii & a, const Pii & b) {
	return a.fir == b.fir ? a.sec < b.sec : a.fir > b.fir;
}
inline void Erase(int v) {
	auto it = val.find(v); val.erase(it);
}
void Gao();

int main() {
	scanf("%d%d%s", &n, &m, S);
	for (int i = 1; i <= n; ++i) scanf("%d", A + i);
	smt::Build(1, n);
	while (m--) {
		scanf("%s", T); Gao();
	}
	for (int i = 1; i <= n; ++i) {
		if (!mxl[i]) continue;
		vec.push_back({mxl[i], i});
	} std::sort(vec.begin(), vec.end(), Cmp1);
	int tl = 0;
	for (int i = tl = 1; i < SZ(vec); ++i) {
		if (vec[i].fir <= vec[i - 1].fir && vec[i].sec >= vec[i - 1].sec)
			continue;
		vec[tl++] = vec[i];
	} vec.erase(vec.begin() + tl, vec.end());
	std::sort(vec.begin(), vec.end(), Cmp2);
	for (int i = tl = 1; i < SZ(vec); ++i) {
		if (vec[i].fir <= vec[i - 1].fir && vec[i].sec >= vec[i - 1].sec)
			continue;
		vec[tl++] = vec[i];
	} vec.erase(vec.begin() + tl, vec.end());
	vec.push_back({0, 0});
	std::sort(vec.begin(), vec.end());
	int hd = tl = 0;
	for (int i = 1; i < SZ(vec); ++i) {
		DP[i] = DP[i - 1] + smt::Query(1, n, vec[i].fir, vec[i].sec);
		while (hd < tl && vec[que[hd].sec].sec < vec[i].fir)
			Erase(que[hd++].fir);
		if (hd < tl) {
			val.erase(val.find(que[hd].fir));
			que[hd] = {smt::Query(1, n, vec[i].fir,
				vec[que[hd].sec].sec) + DP[que[hd].sec - 1], que[hd].sec};
			val.insert(que[hd].fir);
			UMin(DP[i], *val.begin());
			que[tl++] = {DP[i - 1] + smt::Query(1, n,
				vec[i - 1].sec + 1, vec[i].sec), i};
		} else que[tl++] = {DP[i], i};
		val.insert(que[tl - 1].fir);
	} printf("%d\n", DP[SZ(vec) - 1]);
	return 0;
}

namespace smt {
	int T[kMaxn << 1];

	inline int Id(int l, int r) {
		return l + r | l != r;
	}
	void Build(int l, int r) {
		int cur = Id(l, r);
		if (l == r) return (void)(T[cur] = A[l]);
		int mid = l + r >> 1;
		Build(l, mid); Build(mid + 1, r);
		T[cur] = std::min(T[Id(l, mid)], T[Id(mid + 1, r)]);
	}
	int Query(int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr)
			return T[Id(l, r)];
		int mid = l + r >> 1;
		if (ql > mid)
			return Query(mid + 1, r, ql, qr);
		if (qr <= mid)
			return Query(l, mid, ql, qr);
		return std::min(Query(l, mid, ql, qr),
			Query(mid + 1, r, ql, qr));
	}
}

void Gao() {
	lent = strlen(T);
	static int nxt[kMaxn];
	nxt[0] = nxt[1] = 0;
	for (int i = 1, j; i < lent; ++i) {
		for (j = nxt[i]; j && T[j] != T[i]; j = nxt[j]);
		nxt[i + 1] = T[j] == T[i] ? j + 1 : 0;
	}
	for (int i = 0, j = 0; i < n; ++i) {
		while (j && S[i] != T[j]) j = nxt[j];
		if (S[i] == T[j]) ++j;
		if (j == lent) {
			UMax(mxl[i + 1], i - lent + 2); j = nxt[j];
		}
	}
}
