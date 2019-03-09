#include <iostream>
using std::cin;
using std::cout;

int ReadLine() {
	int k;
	cin >> k;
	for (int i = 0, n; i < k; i++) cin >> n;
	return k;
}

int main() {
	std::ios_base::sync_with_stdio(false);

	for (; ; ) {
		cout << "next 0 1\n";
		cout.flush();
		ReadLine();
		cout << "next 0\n";
		cout.flush();
		if (ReadLine() == 2) break;
	}
	for (; ; ) {
		cout << "next 0 1 2 3 4 5 6 7 8 9\n";
		cout.flush();
		if (ReadLine() == 1) break;
	}
	cout << "done\n";
	cout.flush();
	return 0;
}
