//tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long long LL;
typedef std::pair<LL, LL> Vector;

inline void operator+=(Vector & a, const Vector & b) {
	a.x += b.x, a.y += b.y;
}
inline bool cmp(const Vector & v1, const Vector & v2) {
	return v1.y > v2.y;
}

class UnreliableRover {
public:
    long long getArea( string direction, vector <int> minSteps, vector <int> maxSteps ) ;
};

long long UnreliableRover::getArea(string direction, vector <int> minSteps, vector <int> maxSteps) {
	Vector mx1(0, 0), mx2(0, 0);
	std::vector<int> uns;

	for (int i = 0, n = (int)direction.size(); i < n; i++) {	
		if (direction[i] == '?') {
			uns.push_back(maxSteps[i]);
			continue;
		}
		Vector fdir, sdir;
		switch (direction[i]) {
			case 'N' :	fdir = Vector(0, maxSteps[i]), sdir = Vector(0, minSteps[i]);
						break;
			case 'S' :	fdir = Vector(0, -minSteps[i]), sdir = Vector(0, -maxSteps[i]);
						break;
			case 'E' :	fdir = Vector(maxSteps[i], 0), sdir = Vector(minSteps[i], 0);
						break;
			case 'W' :	fdir = Vector(-minSteps[i], 0), sdir = Vector(-maxSteps[i], 0);
						break;
		}
		mx1 += fdir;
		mx2 += sdir;
	}

	LL tots = 0, ans;
	int sz = (int)uns.size();
	for (int i = 0; i < sz; i++) tots += uns[i];
	ans = (mx1.x - mx2.x + 1) * (mx1.y - mx2.y + 1) + (mx1.x - mx2.x + 1) * 2LL * tots + (mx1.y - mx2.y + 1) * 2LL * tots;
//	printf("ans0 = %lld\n", ans);
	
	if (sz) {
		std::vector<Vector> V;
		for (int mask = (1 << sz) - 1; mask >= 0; --mask) {
			Vector tmp(0, 0);
			for (int i = 0; i < sz; i++)
				if (mask >> i & 1) tmp += Vector(0, uns[i]);
				else tmp += Vector(uns[i], 0);
			V.push_back(tmp);
		}
		std::sort(V.begin(), V.end(), cmp);
//		for (int i = 0; i < (int)V.size(); i++) printf(" V[%d] = (%lld, %lld)\n", i, V[i].x, V[i].y);
		LL more = 0, lastx = V[0].x;
		for (int i = 0, n = (int)V.size(); i < n; i++) {
			if (V[i].x <= lastx) continue;
			more += (V[i].x - lastx) * V[i].y;
			lastx = V[i].x;
		}
		ans += 4LL * more;
	}
	return ans;
}

// BEGIN CUT HERE
namespace moj_harness {
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if ( casenum != -1 ) {
			if ( run_test_case( casenum ) == -1 && !quiet )
				cerr << "Illegal input! Test case " << casenum << " does not exist." << endl;
			return;
		}
		
		int correct = 0, total = 0;
		for ( int i=0;; ++i ) {
			int x = run_test_case(i);
			if ( x == -1 ) {
				if ( i >= 100 ) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if ( total == 0 ) {
			cerr << "No test cases run." << endl;
		} else if ( correct < total ) {
			cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << endl;
		} else {
			cerr << "All " << total << " tests passed!" << endl;
		}
	}
	
	int verify_case(int casenum, const long long &expected, const long long &received, clock_t elapsed) { 
		cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if ( expected == received ) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		cerr << verdict;
		if (!info.empty()) {
			cerr << " (";
			for (int i=0; i<(int)info.size(); ++i) {
				if (i > 0) cerr << ", ";
				cerr << info[i];
			}
			cerr << ")";
		}
		cerr << endl;
		
		if (verdict == "FAILED") {
			cerr << "    Expected: " << expected << endl; 
			cerr << "    Received: " << received << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case( int casenum ) {
		switch( casenum ) {
		case 0: {
			string direction          = "N";
			int minSteps[]            = {3};
			int maxSteps[]            = {5};
			long long expected__      = 3LL;

			clock_t start__           = clock();
			long long received__      = UnreliableRover().getArea( direction, vector <int>( minSteps, minSteps + ( sizeof minSteps / sizeof minSteps[0] ) ), vector <int>( maxSteps, maxSteps + ( sizeof maxSteps / sizeof maxSteps[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string direction          = "NE";
			int minSteps[]            = {3,3};
			int maxSteps[]            = {5,5};
			long long expected__      = 9LL;

			clock_t start__           = clock();
			long long received__      = UnreliableRover().getArea( direction, vector <int>( minSteps, minSteps + ( sizeof minSteps / sizeof minSteps[0] ) ), vector <int>( maxSteps, maxSteps + ( sizeof maxSteps / sizeof maxSteps[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string direction          = "?";
			int minSteps[]            = {0};
			int maxSteps[]            = {2};
			long long expected__      = 9LL;

			clock_t start__           = clock();
			long long received__      = UnreliableRover().getArea( direction, vector <int>( minSteps, minSteps + ( sizeof minSteps / sizeof minSteps[0] ) ), vector <int>( maxSteps, maxSteps + ( sizeof maxSteps / sizeof maxSteps[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string direction          = "??N?";
			int minSteps[]            = {0, 0, 0, 0};
			int maxSteps[]            = {0, 0, 0, 0};
			long long expected__      = 1LL;

			clock_t start__           = clock();
			long long received__      = UnreliableRover().getArea( direction, vector <int>( minSteps, minSteps + ( sizeof minSteps / sizeof minSteps[0] ) ), vector <int>( maxSteps, maxSteps + ( sizeof maxSteps / sizeof maxSteps[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			string direction          = "??E?";
			int minSteps[]            = {0, 0, 3, 0};
			int maxSteps[]            = {2, 3, 4, 2};
			long long expected__      = 120LL;

			clock_t start__           = clock();
			long long received__      = UnreliableRover().getArea( direction, vector <int>( minSteps, minSteps + ( sizeof minSteps / sizeof minSteps[0] ) ), vector <int>( maxSteps, maxSteps + ( sizeof maxSteps / sizeof maxSteps[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 5: {
			string direction          = ;
			int minSteps[]            = ;
			int maxSteps[]            = ;
			long long expected__      = LL;

			clock_t start__           = clock();
			long long received__      = UnreliableRover().getArea( direction, vector <int>( minSteps, minSteps + ( sizeof minSteps / sizeof minSteps[0] ) ), vector <int>( maxSteps, maxSteps + ( sizeof maxSteps / sizeof maxSteps[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			string direction          = ;
			int minSteps[]            = ;
			int maxSteps[]            = ;
			long long expected__      = LL;

			clock_t start__           = clock();
			long long received__      = UnreliableRover().getArea( direction, vector <int>( minSteps, minSteps + ( sizeof minSteps / sizeof minSteps[0] ) ), vector <int>( maxSteps, maxSteps + ( sizeof maxSteps / sizeof maxSteps[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			string direction          = ;
			int minSteps[]            = ;
			int maxSteps[]            = ;
			long long expected__      = LL;

			clock_t start__           = clock();
			long long received__      = UnreliableRover().getArea( direction, vector <int>( minSteps, minSteps + ( sizeof minSteps / sizeof minSteps[0] ) ), vector <int>( maxSteps, maxSteps + ( sizeof maxSteps / sizeof maxSteps[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
		default:
			return -1;
		}
	}
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(atoi(argv[i]));
	}
}
// END CUT HERE
