//tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

const string kNo = "NO", kYes = "YES";

class FoxAndMountainEasy {
public:
    string possible(int n, int h0, int hn, string history) {
		if (h0 < 0 || hn < 0) return kNo;
		int h00 = h0;
		for (string::iterator ch = history.begin();
				ch != history.end(); ++ch) {
			*ch == 'U' ? ++h0 : --h0;
			--n;
		}
		if (h0 - n > hn || hn > h0 + n ||
			hn - h0 + n & 1) return kNo;
		int u = hn - h0 + n >> 1;
		h00 += u;
		for (string::iterator ch = history.begin();
				ch != history.end(); ++ch) {
			if ((*ch == 'U' ? ++h00 : --h00) < 0) return kNo;
		}
		return kYes;
	}
};

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
	
	int verify_case(int casenum, const string &expected, const string &received, clock_t elapsed) { 
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
			cerr << "    Expected: \"" << expected << "\"" << endl; 
			cerr << "    Received: \"" << received << "\"" << endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case( int casenum ) {
		switch( casenum ) {
		case 0: {
			int n                     = 4;
			int h0                    = 0;
			int hn                    = 4;
			string history            = "UU";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible( n, h0, hn, history );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			int n                     = 4;
			int h0                    = 0;
			int hn                    = 4;
			string history            = "D";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible( n, h0, hn, history );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			int n                     = 4;
			int h0                    = 100000;
			int hn                    = 100000;
			string history            = "DDU";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible( n, h0, hn, history );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			int n                     = 4;
			int h0                    = 0;
			int hn                    = 0;
			string history            = "DDU";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible( n, h0, hn, history );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			int n                     = 20;
			int h0                    = 20;
			int hn                    = 20;
			string history            = "UDUDUDUDUD";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible( n, h0, hn, history );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 5: {
			int n                     = 20;
			int h0                    = 0;
			int hn                    = 0;
			string history            = "UUUUUUUUUU";
			string expected__         = "YES";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible( n, h0, hn, history );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 6: {
			int n                     = 20;
			int h0                    = 0;
			int hn                    = 0;
			string history            = "UUUUUUUUUUU";
			string expected__         = "NO";

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible( n, h0, hn, history );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 7: {
			int n                     = ;
			int h0                    = ;
			int hn                    = ;
			string history            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible( n, h0, hn, history );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 8: {
			int n                     = ;
			int h0                    = ;
			int hn                    = ;
			string history            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible( n, h0, hn, history );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 9: {
			int n                     = ;
			int h0                    = ;
			int hn                    = ;
			string history            = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndMountainEasy().possible( n, h0, hn, history );
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
