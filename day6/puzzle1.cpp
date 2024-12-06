#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<char>> A;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void simulation(int x, int y, int d) {
	A[x][y] = 'X';
	int nx = x + dx[d];
	int ny = y + dy[d];
	if (0 > nx || nx >= A.size() || 0 > ny || ny >= A[0].size())
		return;
	while (A[nx][ny] == '#') {
		d = (d + 1) % 4;
		nx = x + dx[d];
		ny = y + dy[d];
		if (0 > nx || nx >= A.size() || 0 > ny || ny >= A[0].size())
			return;
	}
	simulation(nx, ny, d);
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (cin >> S) {
		vector<char> T;
		for (int i = 0; i < S.size(); i++)
			T.push_back(S[i]);
		A.push_back(T);
	}
	int sX, sY;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			if (A[i][j] == '^') {
				sX = i;
				sY = j;
			}
		}
	}
	simulation(sX, sY, 0);
	int answer = 0;
	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A[i].size(); j++)
			if (A[i][j] == 'X')
				answer++;
	cout << answer << '\n';
	return 0;
}