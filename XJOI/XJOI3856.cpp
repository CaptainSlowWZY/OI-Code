// XJOI 3856
#include <iostream>
#include <string>
using namespace std;

string S;

bool find(const string & s, string P) {
	int cur = 0;
	for (int i = 0, len = s.length(); i < len; i++)
		if (s[i] == P[cur]) {
			if (++cur == P.length()) return true;
		}
	return false;
}

int main() {
	cin >> S;
	S += "TA";
	if (find(S, "SANTA")) return (cout << S << endl), 0;
	else {
		for (int len = S.length(), i = len - 1; i >= 0; i--)
			if (S[i] == 'N') return (cout << (S.substr(0, i) + "SA" + S.substr(i, len)) << endl), 0;
		cout << "SAN" + S;
	}
	return 0;
}

// AC!!!
