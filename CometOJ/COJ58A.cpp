#include <iostream>
#include <string>

using namespace std;

string st, st1;
int n;

int main() {
	cin >> n;
	cin >> st;
	for (int i = 1; i < n; i++) {
		cin >> st1;
		if (st1 < st) st = st1;
	}
	cout << st << endl;
	return 0;
}
