// tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

class GooseTattarrattatDiv1 {
private:
	int fa[30], cnt[30], mx[30];
	void init() {
		memset(cnt, 0, sizeof cnt);
		memset(mx, 0, sizeof mx);
		for (int i = 0; i < 26; i++) fa[i] = i;
	}
	int find(int x) {
		return x ^ fa[x] ? fa[x] = find(fa[x]) : x;
	}
	void merge(int x, int y) {
		x = find(x), y = find(y);
		fa[x] = y;
	}
	void upd_max(int & x, int y) {
		x = max(x, y);
	}
public:
    int getmin( string S ) ;
};

int GooseTattarrattatDiv1::getmin(string S) {
	init();
	for (int i = 0, len = S.length(); i < len; i++) ++cnt[S[i] - 'a'];
	for (int i = 0, len = S.length(); i + i < len; i++)
		if (S[i] ^ S[len - 1 - i]) merge(S[i] - 'a', S[len - 1 - i] - 'a');
	for (int i = 0; i < 26; i++) upd_max(mx[find(i)], cnt[i]);
	for (int i = 0; i < 26; i++)
		if (i ^ fa[i]) cnt[fa[i]] += cnt[i];
	int ans = 0;
	for (int i = 0; i < 26; i++)
		if (i == fa[i]) ans += cnt[i] - mx[i];
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
			string S                  = "geese";
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = GooseTattarrattatDiv1().getmin( S );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string S                  = "tattarrattat";
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = GooseTattarrattatDiv1().getmin( S );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string S                  = "xyyzzzxxx";
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = GooseTattarrattatDiv1().getmin( S );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string S                  = "xrepayuyubctwtykrauccnquqfuqvccuaakylwlcjuyhyammag";
			int expected__            = 11;

			clock_t start__           = clock();
			int received__            = GooseTattarrattatDiv1().getmin( S );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			string S                  = "abaabb";
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = GooseTattarrattatDiv1().getmin( S );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 5: {
			string S                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GooseTattarrattatDiv1().getmin( S );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			string S                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GooseTattarrattatDiv1().getmin( S );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			string S                  = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GooseTattarrattatDiv1().getmin( S );
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
