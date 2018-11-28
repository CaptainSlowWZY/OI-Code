#include <cstdio>
#include <vector>

#define pb push_back

typedef long long LL;

const int LgLL = 59;

struct Linear_Basis {
	LL bs[LgLL + 5];
	std::vector<LL> vb;

	int count() const {
		return (int)vb.size();
	}
	void clear();
	void init();
	void insert(LL x);
	LL query(LL k) const;
} B;

int N, Q;

void solve();

int main() {
	int t;
	for (scanf("%d", &t); t--; ) solve();
	
	return 0;
}

void solve() {
	scanf("%d", &N);
	B.clear();
	for (int i = 0; i < N; i++) {
		LL Ai;
		scanf("%lld", &Ai);
		B.insert(Ai);
	}
	B.init();

	LL tote;
	if (B.count() < N) tote = 1LL << B.count();
	else tote = (1LL << B.count()) - 1;

	static int cs = 0;
	printf("Case #%d:\n", ++cs);
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) {
		LL Ki;
		scanf("%lld", &Ki);
		if (Ki > tote) puts("-1");
		else printf("%lld\n", B.query(B.count() < N ? Ki - 1 : Ki));
	}
}

void Linear_Basis::clear() {
	for (int i = 0; i <= LgLL; i++) bs[i] = 0;
	vb.clear();
}

void Linear_Basis::init() {
	for (int i = 0; i <= LgLL; i++)
		if (bs[i]) vb.pb(bs[i]);
}

void Linear_Basis::insert(LL x) {
	for (int i = LgLL; i >= 0; i--)
		if (x >> i & 1) {
			if (bs[i]) x ^= bs[i];
			else {
				for (int j = i - 1; j >= 0; j--)
					if (bs[j] && x >> j & 1) x ^= bs[j];
				bs[i] = x;
				for (int j = i + 1; j <= LgLL; j++)
					if (bs[j] >> i & 1) bs[j] ^= x;
				break;
			}
		}
}

LL Linear_Basis::query(LL k) const {
	LL ret = 0;
	for (int i = 0, sz = (int)vb.size(); i < sz; i++)
		if (k >> i & 1) ret ^= vb[i];
	return ret;
}
