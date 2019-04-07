//tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

struct Linebas {
	LL bas[62];
	bool extend(LL x);
} B;

class XorAndSum {
public:
    LL maxSum(vector<LL> number) {
		int n = number.size(), tot0 = 0;
		memset(B.bas, 0, sizeof B.bas);
		for (int i = 0; i < n; i++) {
			if (!B.extend(number[i])) ++tot0;
		}
		LL ans, _xor = 0;
		for (int i = 0; i <= 60; i++) _xor ^= B.bas[i];
		ans = _xor * (tot0 + 1);
		int top = 60;
		for (; top >= 0 && !B.bas[top]; --top);
		for (int i = top - 1; i >= 0; i--) {
			if (!B.bas[i]) continue;
			ans += B.bas[i] ^ _xor;
		}
		return ans;
	}
};

bool Linebas::extend(LL x) {
	for (int i = 60; i >= 0 && x; i--) {
		if (x >> i & 1 ^ 1) continue;
		if (bas[i]) {
			x ^= bas[i];
			continue;
		}
		for (int j = 0; j < i; j++) {
			if (x >> j & 1 && bas[j]) x ^= bas[j];
		}
		bas[i] = x;
		for (int j = 60; j > i; j--) {
			if (bas[j] >> i & 1) bas[j] ^= x;
		}
		return true;
	}
	return false;
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
			long number[]             = {1,0};
			long long expected__      = 2LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum( vector<long long>( number, number + ( sizeof number / sizeof number[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			long number[]             = {1,2,3};
			long long expected__      = 8LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum( vector<long long>( number, number + ( sizeof number / sizeof number[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			long number[]             = {0,0,0,0,0,0,0,0,0,0};
			long long expected__      = 0LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum( vector<long long>( number, number + ( sizeof number / sizeof number[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			long number[]             = {2,3,5,7,11,13,17,19};
			long long expected__      = 233LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum( vector<long long>( number, number + ( sizeof number / sizeof number[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			long number[]             = {123456789012345, 0, 0, 0, 0, 0, 0, 0, 0, 0};
			long long expected__      = 1234567890123450LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum( vector<long long>( number, number + ( sizeof number / sizeof number[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 5: {
			long number[]             = {627,674,281,272,289,877,62,122,603,189,615};
			long long expected__      = 10742LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum( vector<long long>( number, number + ( sizeof number / sizeof number[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 6: {
			long number[]             = {557};
			long long expected__      = 557LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum( vector<long long>( number, number + ( sizeof number / sizeof number[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 7: {
			long number[]             = ;
			long long expected__      = LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum( vector<long long>( number, number + ( sizeof number / sizeof number[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 8: {
			long number[]             = ;
			long long expected__      = LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum( vector<long long>( number, number + ( sizeof number / sizeof number[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 9: {
			long number[]             = ;
			long long expected__      = LL;

			clock_t start__           = clock();
			long long received__      = XorAndSum().maxSum( vector<long long>( number, number + ( sizeof number / sizeof number[0] ) ) );
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
