//tc is healthy, just do it
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x7f7f7f7f;

struct Edge {
	int to, capt, next;
};

class Graph {
private:
	static const int MAXE = 1e5 + 10;
	static const int MAXV = 1700;
	
	Edge E[MAXE << 1];
	int tote, totv, last[MAXV], D[MAXV], cur[MAXV];

	bool build() {
		std::queue<int> que;
		memset(D, 0, sizeof D);
		for (D[S] = 1, que.push(S); !que.empty(); ) {
			int u = que.front(); que.pop();
			for (int e = last[u], v = E[e].to; e; v = E[e = E[e].next].to)
				if (!D[v] && E[e].capt > 0) {
					D[v] = D[u] + 1;
					que.push(v);
				}
		}
		return D[T];
	}
	int dinic(int u, int cap) {
		if (u == T) return cap;
		int delta, rem = cap;
		for (int & e = cur[u], v = E[e].to; e; v = E[e = E[e].next].to)
			if (D[v] == D[u] + 1 && E[e].capt > 0) {
				delta = dinic(v, std::min(rem, E[e].capt));
				E[e].capt -= delta, E[e ^ 1].capt += delta;
				rem -= delta;
			}
		return cap - rem;
	}

public:
	int S, T;

	Graph() {}
	void init() {
		tote = 1, S = 1, T = 2, totv = 2;
		memset(last, 0, sizeof last);
	}
	void add_edge(int u, int v, int c) {
		E[++tote] = (Edge){v, c, last[u]}, last[u] = tote;
		E[++tote] = (Edge){u, 0, last[v]}, last[v] = tote;
	}
	int Newv() { return ++totv; }
	int max_flow() {
		int delta, sumf = 0;
		while (build()) {
			for (int i = 1; i <= totv; i++) cur[i] = last[i];
			while (delta = dinic(S, INF)) sumf += delta;
		}
		return sumf;
	}
};

class FoxAndCity {
private:
	Graph G;
	int id[45][45];
	int sqr(int x) { return x * x; }
public:
    int minimalCost( vector <string> linked, vector <int> want ) ;
};

int FoxAndCity::minimalCost(vector <string> linked, vector <int> want) {	
	int N = (int)linked.size();
	G.init();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) id[i][j] = G.Newv();	// id[i][j] - dist[i] <= j	
		G.add_edge(G.S, id[i][0], i ? INF : 0);
		for (int j = 1; j < N; j++)
			if (!i) G.add_edge(id[i][j - 1], id[i][j], INF);
			else G.add_edge(id[i][j - 1], id[i][j], sqr(j - want[i]));
		G.add_edge(id[i][N - 1], G.T, INF);
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) 
			if (linked[i][j] == 'Y')
				for (int k = 1; k < N; k++) G.add_edge(id[i][k], id[j][k - 1], INF);
	return G.max_flow();
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
			string linked[]           = {"NYN",  "YNY",  "NYN"};
			int want[]                = {0, 1, 1};
			int expected__            = 0;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost( vector <string>( linked, linked + ( sizeof linked / sizeof linked[0] ) ), vector <int>( want, want + ( sizeof want / sizeof want[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 1: {
			string linked[]           = {"NYNN",  "YNYN",  "NYNY",  "NNYN"};
			int want[]                = {0, 3, 3, 3};
			int expected__            = 5;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost( vector <string>( linked, linked + ( sizeof linked / sizeof linked[0] ) ), vector <int>( want, want + ( sizeof want / sizeof want[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 2: {
			string linked[]           = {"NYNNNY",  "YNYNNN",  "NYNYNN",  "NNYNYN",  "NNNYNY",  "YNNNYN"};
			int want[]                = {0, 2, 2, 2, 2, 2};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost( vector <string>( linked, linked + ( sizeof linked / sizeof linked[0] ) ), vector <int>( want, want + ( sizeof want / sizeof want[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 3: {
			string linked[]           = {"NYY","YNN","YNN"};
			int want[]                = {0,0,0};
			int expected__            = 2;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost( vector <string>( linked, linked + ( sizeof linked / sizeof linked[0] ) ), vector <int>( want, want + ( sizeof want / sizeof want[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 4: {
			string linked[]           = {"NYNNNN",  "YNYNNN",  "NYNYYY",  "NNYNYY",  "NNYYNY",  "NNYYYN"} ;
			int want[]                = {0, 1, 2, 3, 0, 3};
			int expected__            = 3;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost( vector <string>( linked, linked + ( sizeof linked / sizeof linked[0] ) ), vector <int>( want, want + ( sizeof want / sizeof want[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 5: {
			string linked[]           = {"NYNNNN",  "YNYNNN",  "NYNYYY",  "NNYNYY",  "NNYYNY",  "NNYYYN"};
			int want[]                = {0, 1, 2, 4, 0, 4};
			int expected__            = 6;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost( vector <string>( linked, linked + ( sizeof linked / sizeof linked[0] ) ), vector <int>( want, want + ( sizeof want / sizeof want[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
		case 6: {
			string linked[]           = {"NYNYYYYYYYY","YNYNNYYNYYY","NYNNNYYNYYN","YNNNYYYYYYY","YNNYNYYYNYY","YYYYYNNYYNY","YYYYYNNNYYY","YNNYYYNNNYY","YYYYNYYNNNY","YYYYYNYYNNY","YYNYYYYYYYN"};
			int want[]                = {0,1,2,0,0,5,1,3,0,2,3};
			int expected__            = 28;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost( vector <string>( linked, linked + ( sizeof linked / sizeof linked[0] ) ), vector <int>( want, want + ( sizeof want / sizeof want[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}

		// custom cases

      case 7: {
			string linked[]           = {"NNYNYYYYYYYYYYYYYYNYYYYYYYYYYYYNYYYYYNYY", "NNYYYYYYYNYYYYYYNYYYYYYYYYYYYYYYYYNYYNNY", "YYNYYYYYYYYYYYYYYNYYYYYNYYYYYYYNYYYNYYYN", "NYYNYNNYYYYYYYYYNYYYYNYYNYYYYYNNYYYYYYYY", "YYYYNYNYYYNNYNNYYYYYYYYYYYNNNYYNYNYYNYYN", "YYYNYNNYYNYYYNYNNYYYYYNYYYNYYYYYYYYYYYYY", "YYYNNNNYYYYYYYNNYYYYYYYNYYYYYNNYYYYNYYYY", "YYYYYYYNYYYNYNNYNYYNYYYYYYYYYYYYYYYYYYYY", "YYYYYYYYNYYYYYYYYYYYYYYYYNYYNYNYYYYYYYYY", "YNYYYNYYYNNYYYNYNYYYYYNYYYYYYYYYYYYYYYYY", "YYYYNYYYYNNYYYYNYNYNYYYYYYYYYYYYYYYNYYNN", "YYYYNYYNYYYNNYYYYYYNYYYYNYYYYYNYYYYYYNNY", "YYYYYYYYYYYNNYYYYYNYNYYYYYYYYYYYYYYYYYNY", "YYYYNNYNYYYYYNYYYYNYYYYYNYNYYYYYNYYYNYYY", "YYYYNYNNYNYYYYNYNYYYYYYYYYYYYYYYYYNYYYNN", "YYYYYNNYYYNYYYYNYYYYYYYNYYYNYYYYYYYYYYYY", "YNYNYNYNYNYYYYNYNYYYNYYYYYYYYNYYYYYYYNYY", "YYNYYYYYYYNYYYYYYNYYYYYNYYYYYYYYYYYYNYYY", "NYYYYYYYYYYYNNYYYYNYYNNYNYYNYYYYYYNYYYYY", "YYYYYYYNYYNNYYYYYYYNYYYNNYYYYYYYYYYYYYYY", "YYYYYYYYYYYYNYYYNYYYNYYNYYYYYYYYYYNYYYYY", "YYYNYYYYYYYYYYYYYYNYYNYYYYNNYYYYNYNYYYYN", "YYYYYNYYYNYYYYYYYYNYYYNNYYYYYYYYYYYYYYYN", "YYNYYYNYYYYYYYYNYNYNNYNNYYYYNYYYNYYYYYYN", "YYYNYYYYYYYNYNYYYYNNYYYYNYYYYYYYYYYYYYYN", "YYYYYYYYNYYYYYYYYYYYYYYYYNYYYNYYYYYYYYNY", "YYYYNNYYYYYYYNYYYYYYYNYYYYNNYYYNYYNNYNNN", "YYYYNYYYYYYYYYYNYYNYYNYYYYNNYYYYYYYNYYYY", "YYYYNYYYNYYYYYYYYYYYYYYNYYYYNNYYYYYYYYYN", "YYYYYYNYYYYYYYYYNYYYYYYYYNYYNNYYYYYYYYYY", "YYYNYYNYNYYNYYYYYYYYYYYYYYYYYYNYYYYYNNYY", "NYNNNYYYYYYYYYYYYYYYYYYYYYNYYYYNYYYYYNYY", "YYYYYYYYYYYYYNYYYYYYYNYNYYYYYYYYNYYYYYYN", "YYYYNYYYYYYYYYYYYYYYYYYYYYYYYYYYYNYNYYYY", "YNYYYYYYYYYYYYNYYYNYNNYYYYNYYYYYYYNYYYNY", "YYNYYYNYYYNYYYYYYYYYYYYYYYNNYYYYYNYNYYYY", "YYYYNYYYYYYYYNYYYNYYYYYYYYYYYYNYYYYYNYNY", "NNYYYYYYYYYNYYYYNYYYYYYYYYNYYYNNYYYYYNYY", "YNYYYYYYYYNNNYNYYYYYYYYYYNNYYYYYYYNYNYNY", "YYNYNYYYYYNYYYNYYYYYYNNNNYNYNYYYNYYYYYYN"};

			int want[]                = {0, 23, 17, 2, 1, 30, 5, 8, 13, 6, 17, 26, 21, 20, 19, 15, 2, 31, 23, 19, 7, 2, 29, 21, 2, 15, 29, 0, 3, 6, 8, 13, 16, 6, 17, 22, 8, 3, 13, 13};
			int expected__            = 9287;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost( vector <string>( linked, linked + ( sizeof linked / sizeof linked[0] ) ), vector <int>( want, want + ( sizeof want / sizeof want[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}
/*      case 8: {
			string linked[]           = ;
			int want[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost( vector <string>( linked, linked + ( sizeof linked / sizeof linked[0] ) ), vector <int>( want, want + ( sizeof want / sizeof want[0] ) ) );
			return verify_case( casenum, expected__, received__, clock()-start__ );
		}*/
/*      case 9: {
			string linked[]           = ;
			int want[]                = ;
			int expected__            = ;

			clock_t start__           = clock();
			int received__            = FoxAndCity().minimalCost( vector <string>( linked, linked + ( sizeof linked / sizeof linked[0] ) ), vector <int>( want, want + ( sizeof want / sizeof want[0] ) ) );
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
