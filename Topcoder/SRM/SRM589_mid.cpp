// tc is healthy, just do it
#pragma GCC diagnostic error "-std=c++11"
#include <bits/stdc++.h>
using namespace std;

#define pb push_back

const int MAXN = 55;

class GearsDiv1 {
private:
	int N, vis[MAXN], match[MAXN];
	vector<int> gr[3], G[MAXN];

	int dfs(int u) {
		vis[u] = 1;
		for (auto v : G[u])
			if (!vis[v]) {
				vis[v] = 1;
				if (match[v] == -1 || dfs(match[v])) {
					match[v] = u;
					return 1;
				}
			}
		return 0;
	}
public:
    int getmin( string color, vector <string> graph ) ;
};

int GearsDiv1::getmin(string color, vector <string> graph) {
	N = color.length();
	for (int i = 0; i < 3; i++) gr[i].clear();

	for (int i = 0; i < N; i++)
		if (color[i] == 'R') gr[0].pb(i);
		else if (color[i] == 'G') gr[1].pb(i);
		else if (color[i] == 'B') gr[2].pb(i);

	int ans = 100;
	for (int i = 0; i < 3; i++)
		for (int j = i + 1; j < 3; j++) {
			memset(match, 0xff, sizeof match);
			for (int k = 0; k < N; k++) G[k].clear();

			for (auto g1 : gr[i])
				for (auto g2 : gr[j])
					if (graph[g1][g2] == 'Y') {
						G[g1].pb(g2);
						G[g2].pb(g1);
					}

			int tot = 0;
			for (auto k : gr[i]) {
				memset(vis, 0, sizeof vis);
				if (dfs(k)) ++tot;
			}

			ans = min(ans, tot);
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
			string color              = "RGB";
			string graph[]            = {"NYY","YNY","YYN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin( color, vector <string>( graph, graph + ( sizeof graph / sizeof graph[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string color              = "RGBR";
			string graph[]            = {"NNNN","NNNN","NNNN","NNNN"};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin( color, vector <string>( graph, graph + ( sizeof graph / sizeof graph[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string color              = "RGBR";
			string graph[]            = {"NYNN","YNYN","NYNY","NNYN"};
			int expected__            = 1;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin( color, vector <string>( graph, graph + ( sizeof graph / sizeof graph[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string color              = "RRRRRGRRBGRRGBBGGGBRRRGBRGRRGG";
			string graph[]            = {"NNNNNYNNNYNNYNNNYNNNNNNNNYNNYY",  "NNNNNNNNYNNNYNYNNYNNNNYNNYNNYY",  "NNNNNYNNNNNNNNNNNNYNNNNNNYNNNY",  "NNNNNNNNNYNNYNNYYYNNNNYNNYNNNN",  "NNNNNNNNNYNNYNNYYYNNNNYNNNNNNN",  "YNYNNNYYYNNYNYYNNNNNYYNYNNYYNN",  "NNNNNYNNNNNNNNNYYYNNNNYNNYNNYY",  "NNNNNYNNNNNNNNNYNNNNNNNNNNNNYN",  "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",  "YNNYYNNNYNNNNYYNNNYNYYNYNNNNNN",  "NNNNNNNNNNNNYNNYNYNNNNYNNNNNNY",  "NNNNNYNNNNNNYNNYYYNNNNNNNNNNYN",  "YYNYYNNNYNYYNYYNNNYNYNNYNNNNNN",  "NNNNNYNNNYNNYNNYYYNNNNYNNYNYYY",  "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",  "NNNYYNYYYNYYNYYNNNYNYNNYYNYYNN",  "YNNYYNYNYNNYNYYNNNYNNNNYYNNYNN",  "NYNYYNYNYNYYNYYNNNNYYNNYYNYNNN",  "NNYNNNNNNYNNYNNYYNNNNNYNNYNNNY",  "NNNNNNNNNNNNNNNNNYNNNNYNNYNNNY",  "NNNNNYNNNYNNYNNYNYNNNNYNNNNNYY",  "NNNNNYNNNYNNNNNNNNNNNNYNNNNNNN",  "NYNYYNYNYNYNNYYNNNYYYYNYYNYNNN",  "NNNNNYNNNYNNYNNYYYNNNNYNNNNNNY",  "NNNNNNNNNNNNNNNYYYNNNNYNNYNNYY",  "YYYYNNYNYNNNNYYNNNYYNNNNYNYYNN",  "NNNNNYNNNNNNNNNYNYNNNNYNNYNNYN",  "NNNNNYNNNNNNNYNYYNNNNNNNNYNNYY",  "YYNNNNYYYNNYNYYNNNNNYNNNYNYYNN",  "YYYNNNYNYNYNNYYNNNYYYNNYYNNYNN"};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin( color, vector <string>( graph, graph + ( sizeof graph / sizeof graph[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

/*      case 4: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin( color, vector <string>( graph, graph + ( sizeof graph / sizeof graph[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 5: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin( color, vector <string>( graph, graph + ( sizeof graph / sizeof graph[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 6: {
			string color              = ;
			string graph[]            = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = GearsDiv1().getmin( color, vector <string>( graph, graph + ( sizeof graph / sizeof graph[0] ) ) );
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
