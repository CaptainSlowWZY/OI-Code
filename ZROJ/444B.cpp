#include <cstdio>
#include <set>
#include <vector>

#define SZ(_) (int)_.size()

typedef std::set<int> Si;

const int kMaxn = 2e5 + 5;

int n, m;
int A[kMaxn], B[kMaxn];
std::vector<int> pos[kMaxn];
Si clp;

inline int Prv(Si & s, Si::iterator it) {
	if (it == s.begin()) it = s.end();
	return *(--it);
}
inline int Nxt(Si & s, Si::iterator it) {
	if (it == s.end()) it = s.begin();
	if (++it == s.end()) it = s.begin();
	return *it;
}
inline int Prv(int p) {
	return p == 1 ? n : p - 1;
}
inline int Nxt(int p) {
	return p < n ? p + 1 : 1;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", A + i);
		B[i] = A[i] != 1, pos[A[i]].push_back(i);
		clp.insert(i - 1);
	}
	if (pos[1].empty()) printf("-1 ");
	else printf("%d ", n - SZ(pos[1]));
	int tot = 0;
	for (int i = 2; i <= m; ++i) {
//		printf(" clap at k = %d\n", i);
		for (auto j : pos[i - 1]) {	
			auto it = clp.find(j - 1);
			if (B[Prv(j)] == 1) {
				int prv = Prv(clp, it);
				if (prv > j) prv -= n;
//				printf("	!!j = %d, prv %d\n", j, prv);
				tot -= *it - prv >> 1;
				tot += *it - prv + 1 >> 1;
//				printf("		break down %d\n", *it);
//				printf("		tot = %d\n", tot);
				clp.erase(it);
			}
			it = clp.find(j % n);
			if (SZ(clp) == 1) clp.erase(it);
			else if (it != clp.end() && B[Nxt(j)] == 1) {
				int prv = Prv(clp, it), nxt = Nxt(clp, it);
				if (prv > *it) prv -= n;
				if (nxt < *it) nxt += n;
//				printf("	j = %d, prv %d, nxt %d\n", j, prv, nxt);
				tot -= *it - prv >> 1;
			//	sb dls
			//	sbsb dls
				tot -= nxt - *it >> 1;
				tot += nxt - prv >> 1;
//				printf("		break down2 %d\n", *it);
//				printf("		tot %d\n", tot);
				clp.erase(it);
			} B[j] = -1;
		}
		for (auto j : pos[i]) {	
			auto it = clp.lower_bound(j);
			if (it == clp.end()) it = clp.begin();
			int nxt = *it, prv;
			it = clp.upper_bound(j - 1);
			if (it == clp.begin()) it = clp.end();
			prv = *(--it);
			if (prv > j) prv -= n;
			if (nxt < j) nxt += n;
//			printf("	!j = %d, prv %d, nxt %d\n", j, prv, nxt);
			if (nxt - prv > 1) {
				tot -= nxt - prv >> 1;
				tot += nxt - j >> 1;
				tot += j - 1 - prv >> 1;
//				printf("		tot = %d\n", tot);
				clp.insert(j - 1);
				clp.insert(j % n);
			}
			B[j] = 0;
		}
//		printf("-----");
//		for (auto j : clp) printf("%d ", j); puts("");
//		printf("  tot = %d\n", tot);
		if (pos[i].empty()) printf("-1 ");
		else printf("%d ", tot + n - SZ(pos[i]));
	} puts(""); return 0;
}
