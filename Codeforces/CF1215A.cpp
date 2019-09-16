#include <bits/stdc++.h>

typedef long long LL;

const LL N = 1e5 + 10;

using namespace std;

int n,m,k1,k2,k,ans;

template <typename tp>
inline void Read(tp &x) {
	x = 0; char c = getchar(); bool f = 0;
	for (; c < '0' || c > '9'; f |= (c == '-'), c = getchar()) ;
	for (; c >= '0' && c <= '9'; x = (x << 3) + (x << 1) + c - '0', c = getchar()) ;
	if (f) x = -x;
}

int main() {
	Read(n); Read(m); Read(k1); Read(k2); Read(k);
	if (k1 > k2) {
		swap(n, m);
		swap(k1, k2);
	}
	printf("%d ",max(0,k-(k1-1)*n-(k2-1)*m));
	for(int i=1;i<=n;i++) {
		if(k>=k1) {
			++ans;
			k -= k1;
		}
	}
	for(int i = 1; i <= m; i++) {
		if(k >= k2) {
			++ans;
			k -= k2;
		}
	}
	printf("%d\n", ans);
	return 0;
}
