//tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

const string IMP = "Impossible", PSB = "Possible";

class FoxAndChess {
public:
    string ableToMove( string begin, string target ) ;
};

string FoxAndChess::ableToMove(string begin, string target) {
	int i, j, len = begin.length();	
	for (i = j = 0; i < len && j < len; ++i, ++j) {
		for (; i < len && begin[i] == '.'; i++);
		for (; j < len && target[j] == '.'; j++);
		if (i == len || j == len) break;
		if (begin[i] ^ target[j] || begin[i] == 'L' && j > i || begin[i] == 'R' && j < i) return IMP;
	}
	for (; i < len && begin[i] == '.'; i++);
	for (; j < len && target[j] == '.'; j++);
	if (i < len || j < len) return IMP;
	return PSB;
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
			string begin              = "R...";
			string target             = "..R.";
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = FoxAndChess().ableToMove( begin, target );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string begin              = "..R.";
			string target             = "R...";
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = FoxAndChess().ableToMove( begin, target );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string begin              = ".L.R.R.";
			string target             = "L...R.R";
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = FoxAndChess().ableToMove( begin, target );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string begin              = ".L.R.";
			string target             = ".R.L.";
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = FoxAndChess().ableToMove( begin, target );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			string begin              = "LRLLRLRLLRLLRLRLRL";
			string target             = "LRLLRLRLLRLLRLRLRL";
			string expected__         = "Possible";

			clock_t start__           = clock();
			string received__         = FoxAndChess().ableToMove( begin, target );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 5: {
			string begin              = "L";
			string target             = ".";
			string expected__         = "Impossible";

			clock_t start__           = clock();
			string received__         = FoxAndChess().ableToMove( begin, target );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 6: {
			string begin              = ;
			string target             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndChess().ableToMove( begin, target );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			string begin              = ;
			string target             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndChess().ableToMove( begin, target );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 8: {
			string begin              = ;
			string target             = ;
			string expected__         = ;

			clock_t start__           = clock();
			string received__         = FoxAndChess().ableToMove( begin, target );
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
