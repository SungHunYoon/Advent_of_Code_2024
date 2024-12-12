#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ii = pair<int, int>;

vector<vector<char>> A;
vector<vector<bool>> bV;
vector<vector<int>> dV;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y, int dir) {
	if (0 > x || x >= dV.size() || 0 > y || y >= dV[0].size())
		return;
	if (!(dV[x][y] & (1 << dir)))
		return;
	dV[x][y] &= ~(1 << dir);
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		dfs(nx, ny, dir);
	}
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
			if (0 > nx || nx >= A.size() || 0 > ny || ny >= A[0].size()) {
				dV[nx + 1][ny + 1] |= (1 << i);
				continue;
			}
			if (A[x][y] != A[nx][ny]) {
				dV[nx + 1][ny + 1] |= (1 << i);
				continue;
			}
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
		vector<int> tdV(S.size() + 2, 0);
		for (int i = 0; i < S.size(); i++)
			T.push_back(S[i]);
		A.push_back(T);
		bV.push_back(tV);
		dV.push_back(tdV);
	}
	dV.insert(dV.begin(), dV[0]);
	dV.push_back(dV[0]);
	long answer = 0;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			if (!bV[i][j]) {
				long a = bfs(i, j);
				long b = 0;
				for (int k = 0; k < dV.size(); k++) {
					for (int l = 0; l < dV[0].size(); l++) {
						for (int m = 0; m < 4; m++) {
							if ((dV[k][l] & (1 << m))) {
								dfs(k, l, m);
								b++;
							}
						}
					}
				}
				answer += a * b;
			}
		}
	}
	cout << answer << '\n';
	return 0;
}