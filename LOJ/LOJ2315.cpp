// NOIP2017
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <stack>

int L, top;
char comp[40], line[40];
int S[105], used[26];
std::stack<char> ch;

void Jumper(char st[], int & i) {
	for (; st[i] != '\n' && st[i] == ' '; ++i);
}

int main() {
	int t;
	for (scanf("%d", &t); t--; ) {
		scanf("%d%s", &L, comp); getchar();
		S[(top = 1) - 1] = 0; std::fill(used, used + 26, 0);
		for (; !ch.empty(); ch.pop());
		int err = 0, ans = 0, w = 0;
		if (comp[2] == 'n') {
			for (int i = 4; comp[i] && isdigit(comp[i]); ++i)
				w = (w << 3) + (w << 1) + (comp[i] ^ '0');
		} while (L--) {
			fgets(line, 105, stdin);
			int i = 0; Jumper(line, i);
			if (line[i] == 'F') {
				++i, Jumper(line, i);
				if (used[line[i] - 'a']) { err = 1; continue; }
				used[line[i] - 'a'] = 1, ch.push(line[i]);
				++i, Jumper(line, i);
			//	if (line[i] == 'n') { S[top++] = -1; continue; }
				int x = 0, y = 0;
				if (line[i] == 'n') x = -1;
				else {
					for (; line[i] != '\n' && isdigit(line[i]); ++i)
						x = (x << 3) + (x << 1) + (line[i] ^ '0');
				} ++i, Jumper(line, i);
				if (line[i] == 'n')
					S[top] = ~S[top - 1] ?
						S[top - 1] + (~x ? 1 : 0) : -1;
				else {
					for (; line[i] != '\n' && isdigit(line[i]); ++i)
						y = (y << 3) + (y << 1) + (line[i] ^ '0');
					S[top] = ~S[top - 1] && ~x && x <= y ? S[top - 1] : -1;
				} ++top;
			} else {
				if (top > 1) {
					ans = std::max(ans, S[--top]);
					used[ch.top() - 'a'] = 0, ch.pop();
				} else err = 1;
			}
		} puts(err || top > 1 ? "ERR" : (ans == w ? "Yes " : "No"));
	} return 0;
}
