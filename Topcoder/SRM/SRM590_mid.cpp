//tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int Lg_LL = 63;

class XorCards {
private:
	LL bs[Lg_LL + 5];
	LL fast_pow(LL bs, int ex) {
		LL ret = 1;
		for (; ex; bs *= bs, ex >>= 1)
			if (ex & 1) ret *= bs;
		return ret;
	}
public:
    LL numberOfWays( vector<LL> number, LL limit ) ;
};

LL XorCards::numberOfWays(vector<LL> number, LL limit) {
	int N = number.size();
	// build base
	memset(bs, 0, sizeof bs);
	for (int i = 0; i < N; i++) {
		LL & now = number[i];
		for (int j = Lg_LL; j >= 0; j--)
			if (number[i] >> j & 1) {
				if (bs[j]) now ^= bs[j];
				else {
					for (int k = j - 1; k >= 0; k--)
						if (now >> k & 1 && bs[k]) now ^= bs[k];
					bs[j] = now;
					for (int k = j + 1; k <= Lg_LL; k++)
						if (bs[k] >> j & 1) bs[k] ^= now;
					break;
				}
			}
	}

	vector<LL> B(N);
	for (int i = 0, t = 0; i <= Lg_LL; i++)
		if (bs[i]) B[t++] = bs[i];
	sort(B.begin(), B.end());
//	printf("\nB:\n");
//	for (int i = 0; i < N; i++) printf("%lld%c", B[i], i + 1 == N ? '\n' : ' ');
	LL K = 0, _xor = 0;
	for (int i = N - 1; i >= 0; i--)
		if ((_xor ^ B[i]) <= limit) {
			_xor ^= B[i];
			K += fast_pow(2, i);
		}
//	printf("K=%lld, _xor=%lld\n", K, _xor);
	return K + 1;
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
	
	int verify_case(int casenum, const LL &expected, const LL &received, clock_t elapsed) { 
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
			long number[]             = {1,2};
			LL limit           = 2LL;
			LL expected__      = 3LL;

			clock_t start__           = clock();
			LL received__      = XorCards().numberOfWays( vector<LL>( number, number + ( sizeof number / sizeof number[0] ) ), limit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			long number[]             = {5,5};
			LL limit           = 3LL;
			LL expected__      = 2LL;

			clock_t start__           = clock();
			LL received__      = XorCards().numberOfWays( vector<LL>( number, number + ( sizeof number / sizeof number[0] ) ), limit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			long number[]             = {1,2,3,4,5,6,7};
			LL limit           = 5LL;
			LL expected__      = 96LL;

			clock_t start__           = clock();
			LL received__      = XorCards().numberOfWays( vector<LL>( number, number + ( sizeof number / sizeof number[0] ) ), limit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			long number[]             = {123, 456, 789, 147, 258, 369, 159, 357};
			LL limit           = 500LL;
			LL expected__      = 125LL;

			clock_t start__           = clock();
			LL received__      = XorCards().numberOfWays( vector<LL>( number, number + ( sizeof number / sizeof number[0] ) ), limit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			long number[]             = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
			LL limit           = 1000000000000000LL;
			LL expected__      = 4294967296LL;

			clock_t start__           = clock();
			LL received__      = XorCards().numberOfWays( vector<LL>( number, number + ( sizeof number / sizeof number[0] ) ), limit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 5: {
			long number[]             = {1000000000000000, 999999999999999};
			LL limit           = 65535LL;
			LL expected__      = 2LL;

			clock_t start__           = clock();
			LL received__      = XorCards().numberOfWays( vector<LL>( number, number + ( sizeof number / sizeof number[0] ) ), limit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 6: {
			long number[]             = ;
			LL limit           = LL;
			LL expected__      = LL;

			clock_t start__           = clock();
			LL received__      = XorCards().numberOfWays( vector<LL>( number, number + ( sizeof number / sizeof number[0] ) ), limit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 7: {
			long number[]             = ;
			LL limit           = LL;
			LL expected__      = LL;

			clock_t start__           = clock();
			LL received__      = XorCards().numberOfWays( vector<LL>( number, number + ( sizeof number / sizeof number[0] ) ), limit );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 8: {
			long number[]             = ;
			LL limit           = LL;
			LL expected__      = LL;

			clock_t start__           = clock();
			LL received__      = XorCards().numberOfWays( vector<LL>( number, number + ( sizeof number / sizeof number[0] ) ), limit );
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
