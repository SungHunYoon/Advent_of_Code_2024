#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<char>> A;
bool V[4][130][130];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool simulation(int x, int y, int d) {
	if (V[d][x][y]) return true;
	bool ret = false;
	V[d][x][y] = true;
	int nx, ny;
	for (int i = 0; i < 4; i++) {
		int dir = (d + i) % 4;
		nx = x + dx[dir];
		ny = y + dy[dir];
		if (0 > nx || nx >= A.size() || 0 > ny || ny >= A[0].size()) break;
		if (A[nx][ny] == '#') continue;
		ret = simulation(nx, ny, dir);
		break;
	}
	V[d][x][y] = false;
	return ret;
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
	int answer = 0;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			if (A[i][j] == '^' || A[i][j] == '#') continue;
			A[i][j] = '#';
			if (simulation(sX, sY, 0))
				answer++;
			A[i][j] = '.';
		}
	}
	cout << answer << '\n';
	return 0;
}