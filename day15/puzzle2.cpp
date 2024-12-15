#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ii = pair<int, int>;

vector<vector<char>> A;
ii R;
char dc[] = {'^', 'v', '<', '>'};
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int findDir(char c) {
	int ret = -1;
	for (int i = 0; i < 4; i++)
		if (c == dc[i])
			ret = i;
	return ret;
}

bool checkSafe(int x, int y, int dir) {
	if (A[x][y] == '#')
		return false;
	else if (A[x][y] == '[' || A[x][y] == ']') {
		if (dir == 0 || dir == 1) {
			int pairY = y;
			if (A[x][y] == '[') pairY++;
			else pairY--;
			return checkSafe(x + dx[dir], y + dy[dir], dir) &&
					checkSafe(x + dx[dir], pairY + dy[dir], dir);
		}
		return checkSafe(x + dx[dir], y + dy[dir], dir);
	}
	else
		return true;
}

void dfs(int x, int y, int dir, char c) {
	if (A[x][y] == '#') return;
	else if (A[x][y] == '[' || A[x][y] == ']') {
		int pairY = y;
		if (dir == 0 || dir == 1) {
			if (A[x][y] == '[') pairY++;
			else pairY--;
		}
		if (checkSafe(x + dx[dir], y + dy[dir], dir) &&
			checkSafe(x + dx[dir], pairY + dy[dir], dir)) {
			dfs(x + dx[dir], y + dy[dir], dir, A[x][y]);
			A[x][y] = c;
			if (dir == 0 || dir == 1) {
				dfs(x + dx[dir], pairY + dy[dir], dir, A[x][pairY]);
				A[x][pairY] = '.';
			}
		}
	}
	else
		A[x][y] = c;
}

void printMap() {
	cout << "==============\n";
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++)
			cout << A[i][j] << ' ';
		cout << '\n';
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (getline(cin, S)) {
		if (S == "") break;
		vector<char> T;
		for (int i = 0; i < S.size(); i++) {
			if (S[i] == '@') {
				T.push_back(S[i]);
				T.push_back('.');
			}
			else if (S[i] == 'O') {
				T.push_back('[');
				T.push_back(']');
			} else {
				T.push_back(S[i]);
				T.push_back(S[i]);
			}
		}
		A.push_back(T);
	}
	string T;
	while (getline(cin, S))
		T += S;
	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A[i].size(); j++)
			if (A[i][j] == '@') R = {i, j};
	for (int i = 0; i < T.size(); i++) {
		int dir = findDir(T[i]);
		dfs(R.first + dx[dir], R.second + dy[dir], dir, A[R.first][R.second]);
		if (A[R.first + dx[dir]][R.second + dy[dir]] == '@') {
			A[R.first][R.second] = '.';
			R.first += dx[dir];
			R.second += dy[dir];
		}
	}
	long answer = 0;
	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A[i].size(); j++)
			if (A[i][j] == '[') answer += 100 * i + j;
	cout << answer << '\n';
	return 0;
}