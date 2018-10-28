// XJOI 3853
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef long long LL;

int N, M;
string A[60];

LL fast_pow(LL bs, int ex) {
	LL res = 1;
	for (; ex; bs *= bs, ex >>= 1) if (ex & 1) res *= bs;
	return res;
}

int main() {
	cin >> N >> M;	
	for (int i = 0; i < M; i++) cin >> A[i];
	
	sort(A, A + M);
	string lst = "233";
	LL invld = 0;
	for (int i = 0; i < M; i++) {
		if (A[i].substr(0, lst.length()) == lst) continue;
//		cerr << N - A[i].length() << endl;
		invld += fast_pow(10, N - A[i].length());
		lst = A[i];
	}
	cout << fast_pow(10, N) - invld << endl;
	return 0;
}

// AC!!!
