//tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

class EraseToGCD {
private:
	int N, DP[505][1005];
public:
    int countWays( vector <int> S, int goal ) ;
};

inline void add(int & x, int y) {
	(x += y) >= MOD ? x -= MOD : 0;
}

int EraseToGCD::countWays(vector <int> S, int goal) {
	N = (int)S.size();
	memset(DP, 0, sizeof DP);
	DP[0][0] = 1;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= 1000; j++) {
			add(DP[i][std::__gcd(j, S[i - 1])], DP[i - 1][j]);
			add(DP[i][j], DP[i - 1][j]);
		}
	return DP[N][goal];
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
	
	int verify_case(int casenum, const int &expected, const int &received, clock_t elapsed) { 
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
			int S[]                   = {6, 4, 30, 90, 66};
			int goal                  = 2;
			int expected__            = 15;

			clock_t start__           = clock();
			int received__            = EraseToGCD().countWays( vector <int>( S, S + ( sizeof S / sizeof S[0] ) ), goal );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int S[]                   = {8, 8, 8};
			int goal                  = 4;
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = EraseToGCD().countWays( vector <int>( S, S + ( sizeof S / sizeof S[0] ) ), goal );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int S[]                   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			int goal                  = 1;
			int expected__            = 983;

			clock_t start__           = clock();
			int received__            = EraseToGCD().countWays( vector <int>( S, S + ( sizeof S / sizeof S[0] ) ), goal );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int S[]                   = {2, 2, 2, 2, 2};
			int goal                  = 2;
			int expected__            = 31;

			clock_t start__           = clock();
			int received__            = EraseToGCD().countWays( vector <int>( S, S + ( sizeof S / sizeof S[0] ) ), goal );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 4: {
			int S[]                   = ;
			int goal                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EraseToGCD().countWays( vector <int>( S, S + ( sizeof S / sizeof S[0] ) ), goal );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 5: {
			int S[]                   = ;
			int goal                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EraseToGCD().countWays( vector <int>( S, S + ( sizeof S / sizeof S[0] ) ), goal );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			int S[]                   = ;
			int goal                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = EraseToGCD().countWays( vector <int>( S, S + ( sizeof S / sizeof S[0] ) ), goal );
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
