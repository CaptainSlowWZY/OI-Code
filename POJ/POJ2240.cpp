#include <iostream>
#include <map>
#include <string>
using namespace std;

int n, m, cs;
double DP[35][35];
std::map<string, int> mp;

int main() {
	string n1, n2;
	while (cin >> n && n) {
		mp.clear();
		for (int i = 0; i < n; i++) {
			cin >> n1;
			mp[n1] = i;
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) DP[i][j] = 0;
		}
		cin >> m;
		for (double x; m--; ) {
			cin >> n1 >> x >> n2;
			DP[mp[n1]][mp[n2]] = x;
		}

		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					DP[i][j] = std::max(DP[i][j], DP[i][k] * DP[k][j]);
				}
			}
		}

		int flag = 0;
		for (int i = 0; i < n; i++) {
			if (DP[i][i] > 1) { flag = 1; break; }
		}

		cout << "Case " << ++cs << ": " << (flag ? "Yes\n" : "No\n");
	}

	return 0;
}
