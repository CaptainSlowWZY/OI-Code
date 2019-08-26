#include <algorithm>
#include <functional>
#include <cstdio>

const int kMaxn = 1e4 + 5;
const double eps=1e-7;
double P[kMaxn];
int n;

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%lf", P + i);
		std::sort(P, P + n, std::greater<double>());
		double ans = 0, _s = 0, _p = 1; 
		for (int i = 0; i < n; i++) 
			if ( fabs( P[i] - 1 ) < eps ) ans = std::max(ans,1.0);
			else
			{
				_p *= 1.0 - P[i], _s += 1 / (1.0 - P[i]) - 1;
				ans = std::max(ans, _p * _s);
			} printf("%.10f\n", ans);
	} return 0;
}
