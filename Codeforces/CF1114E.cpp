#include <iostream>
#include <algorithm>
#include <vector>

int main() {
	int N;
	std::ios_base::sync_with_stdio(false);
	
	std::cin >> N;

//	find a_n
	int l = -1, r = 1e9, cnt = 0;
	for (int mid, f; r - l > 1; ++cnt) { // (l, r]
		mid = l + r >> 1;
		std::cout << "> " << mid << std::endl;
		std::cout.flush();
		std::cin >> f;
		if (f) l = mid;
		else r = mid;
	}
	int AN = r;

//	find d
	std::vector<int> V;
	for (int i = 1, step = (N - 1) / (std::min(N, 60 - cnt) - 1), ai; i <= N && cnt < 60; ++cnt, i += step) {
		std::cout << "? " << i << std::endl;
		std::cout.flush();
		std::cin >> ai;
		V.push_back(ai);
	}
	std::sort(V.begin(), V.end());
	int pre = -1, d = 0;
	for (auto i : V) {
		if (~pre) d = std::__gcd(d, i - pre);
		pre = i;
	}

	std::cout << "! " << AN - d * (N - 1) << " " << d << std::endl;
	return 0;
}
