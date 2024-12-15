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

bool dfs(int x, int y, int dir) {
	bool ret = false;
	if (A[x][y] == '#')
		return ret;
	else if (A[x][y] == 'O') {
		ret = dfs(x + dx[dir], y + dy[dir], dir);
		if (ret) A[x][y] = 'O';
	}
	else {
		A[x][y] = 'O';
		ret = true;
	}
	return ret;
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
		for (int i = 0; i < S.size(); i++)
			T.push_back(S[i]);
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
		if (dfs(R.first + dx[dir], R.second + dy[dir], dir)) {
			A[R.first][R.second] = '.';
			R.first += dx[dir];
			R.second += dy[dir];
			A[R.first][R.second] = '@';
		}
	}
	long answer = 0;
	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A[i].size(); j++)
			if (A[i][j] == 'O') answer += 100 * i + j;
	cout << answer << '\n';
	return 0;
}