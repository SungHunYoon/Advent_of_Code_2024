#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<char>> A;
vector<vector<char>> B;
bool V[4][130][130];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool simulation(int x, int y, int d) {
	if (V[d][x][y]) return true;
	B[x][y] = 'X';
	V[d][x][y] = true;
	int nx = x + dx[d];
	int ny = y + dy[d];
	if (0 > nx || nx >= B.size() || 0 > ny || ny >= B[0].size())
		return false;
	while (B[nx][ny] == '#') {
		d = (d + 1) % 4;
		nx = x + dx[d];
		ny = y + dy[d];
		if (0 > nx || nx >= B.size() || 0 > ny || ny >= B[0].size())
			return false;
	}
	return simulation(nx, ny, d);
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
			fill(&V[0][0][0], &V[4][0][0], false);
			B = A;
			B[i][j] = '#';
			if (simulation(sX, sY, 0))
				answer++;
		}
	}
	cout << answer << '\n';
	return 0;
}