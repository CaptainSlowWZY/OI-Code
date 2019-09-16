#include <bits/stdc++.h>

const int N = 2e5 + 10;

using namespace std;

int n,cnts1,cnts2,zz[N],cnt,x1[N],cnt1,x2[N],cnt2;
int ans[N],cnta;
string s1,s2;

template <typename tp>
inline void Read(tp &x) {
	x = 0; char c = getchar(); bool f = 0;
	for (; c < '0' || c > '9'; f |= (c == '-'), c = getchar()) ;
	for (; c >= '0' && c <= '9'; x = (x << 3) + (x << 1) + c - '0', c = getchar()) ;
	if (f) x = -x;
}

int main() {
	Read(n); cin>>s1; cin>>s2;
	for(int i=0;i<n;i++) {
		if (s1[i]=='a') ++cnts1;
	}
	for(int i=0;i<n;i++) {
		if (s2[i]=='a') cnts2++;
	}
	if ((cnts1+cnts2) & 1) {
		puts("-1");
		return 0;
	}
	for (int i=0;i<n;i++) {
		if(s1[i]=='a'&&s2[i]=='b') {
			x1[++cnt1]=i+1;
		} else if(s2[i]=='a'&&s1[i]=='b') {
			x2[++cnt2]=i+1;
		}
	}
	while(cnt1>=2) {
		ans[++cnta]=x1[cnt1--];
		ans[++cnta]=x1[cnt1--];
	}
	while(cnt2>=2) {
		ans[++cnta]=x2[cnt2--];
		ans[++cnta]=x2[cnt2--];
	}
	if(cnt1) {
		ans[++cnta]=x1[cnt1]; ans[++cnta]=x1[cnt1];
		ans[++cnta]=x1[cnt1]; ans[++cnta]=x2[cnt2];
	}
	printf("%d\n", cnta/2);
	for(int i=1;i<=cnta;i+=2) {
		printf("%d %d\n",ans[i],ans[i+1]);
	}
	return 0;
}

