#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
using ii = pair<int, int>;

vector<vector<int>> A;
vector<vector<bool>> V;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs(int x, int y) {
	for (int i = 0; i < V.size(); i++)
		fill(V[i].begin(), V[i].end(), false);
	int cnt = 0;
	queue<ii> q;
	q.push({x, y});
	V[x][y] = true;
	while (!q.empty()) {
		auto [x, y] = q.front(); q.pop();
		if (A[x][y] == 9) {
			cnt++;
			continue;
		}
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 > nx || nx >= A.size() || 0 > ny || ny >= A[0].size()) continue;
			if (V[nx][ny]) continue;
			if (A[nx][ny] - A[x][y] != 1) continue;
			q.push({nx, ny});
			V[nx][ny] = true;
		}
	}
	return cnt;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (cin >> S) {
		vector<int> T;
		vector<bool> tV(S.size(), false);
		for (int i = 0; i < S.size(); i++)
			T.push_back(S[i] - '0');
		A.push_back(T);
		V.push_back(tV);
	}
	int answer = 0;
	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A[i].size(); j++)
			if (A[i][j] == 0) answer += bfs(i, j);
	cout << answer << '\n';
	return 0;
}