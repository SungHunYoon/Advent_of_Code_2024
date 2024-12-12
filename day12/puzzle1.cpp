#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ii = pair<int, int>;

vector<vector<char>> A;
vector<vector<bool>> bV;
vector<vector<bool>> dV;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int dfs(int x, int y, char c) {
	if (0 > x || x >= A.size() || 0 > y || y >= A[0].size())
		return 1;
	if (A[x][y] != c)
		return 1;
	if (dV[x][y])
		return 0;
	dV[x][y] = true;
	int ret = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		ret += dfs(nx, ny, c);
	}
	return ret;
}

int bfs(int x, int y) {
	queue<ii> q;
	bV[x][y] = true;
	q.push({x, y});
	int cnt = 0;
	while (!q.empty()) {
		auto [cx, cy] = q.front(); q.pop();
		cnt++;
		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (0 > nx || nx >= A.size() || 0 > ny || ny >= A[0].size()) continue;
			if (A[x][y] != A[nx][ny]) continue;
			if (bV[nx][ny]) continue;
			bV[nx][ny] = true;
			q.push({nx, ny});
		}
	}
	return cnt;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (cin >> S) {
		vector<char> T;
		vector<bool> tV(S.size(), false);
		for (int i = 0; i < S.size(); i++)
			T.push_back(S[i]);
		A.push_back(T);
		bV.push_back(tV);
		dV.push_back(tV);
	}
	long answer = 0;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			if (!bV[i][j]) {
				long a = bfs(i, j);
				long b = dfs(i, j, A[i][j]);
				answer += a * b;
			}
		}
	}
	cout << answer << '\n';
	return 0;
}