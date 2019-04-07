//tc is healthy, just do it
#include <bits/stdc++.h>
using namespace std;

class Incubator {
private:
	static const int kMaxn = 52;

	struct Edge {
		int to, next;
	} E[kMaxn * kMaxn << 1];
	int n, tote;
	int vis[kMaxn << 1], last[kMaxn << 1], match[kMaxn << 1];

	void AddEdge(int u, int v) {
		E[++tote] = (Edge){v, last[u]}, last[u] = tote;
	}
	bool Dfs(int u);
public:
    int maxMagicalGirls(vector <string> love) ;
};

bool Incubator::Dfs(int u) {
	for (int e = last[u], v = E[e].to; e;
			v = E[e = E[e].next].to) {
		if (vis[v]) continue;
		vis[v] = 1;
		if (match[v] == -1 || Dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

int Incubator::maxMagicalGirls(vector <string> love) {	
	tote = 0;
	memset(last, 0, sizeof last);

	n = love.size();
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (love[i][j] == 'Y') continue;
				if (love[i][k] == 'Y' && love[k][j] == 'Y') {
					love[i][j] = 'Y';
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (love[i][j] == 'Y') {
				AddEdge(i + 1, n + j + 1);
			}
		}
	}
	
	memset(match, 0xff, sizeof match);
	int ans = n;
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof vis);
		ans -= Dfs(i);
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
			string love[]             = {"NY","NN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls( vector <string>( love, love + ( sizeof love / sizeof love[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string love[]             = {"NYN", "NNY", "NNN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls( vector <string>( love, love + ( sizeof love / sizeof love[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string love[]             = {"NNYNN","NNYNN","NNNYY","NNNNN","NNNNN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls( vector <string>( love, love + ( sizeof love / sizeof love[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string love[]             = {"NNNNN","NYNNN","NYNYN","YNYNN","NNNNN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls( vector <string>( love, love + ( sizeof love / sizeof love[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			string love[]             = {"NNNNN","NNNNN","NNNNN","NNNNN","NNNNN"};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls( vector <string>( love, love + ( sizeof love / sizeof love[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 5: {
			string love[]             = {"NNYNNNNN","NNNYNNNN","NNNNYNNN","NNYNNNNN","NNNNNYYN","NNNYNNNY","NNNNNNNN","NNNNNNNN"};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls( vector <string>( love, love + ( sizeof love / sizeof love[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 6: {
			string love[]             = {"Y"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls( vector <string>( love, love + ( sizeof love / sizeof love[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 7: {
			string love[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls( vector <string>( love, love + ( sizeof love / sizeof love[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 8: {
			string love[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls( vector <string>( love, love + ( sizeof love / sizeof love[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 9: {
			string love[]             = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = Incubator().maxMagicalGirls( vector <string>( love, love + ( sizeof love / sizeof love[0] ) ) );
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
