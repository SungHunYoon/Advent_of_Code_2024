#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;
using ii = pair<int, int>;

vector<vector<char>> A;
vector<vector<int>> D;
vector<vector<bool>> V;
ii s, e;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int cbfs(int x, int y, int value) {
	int ret = 0;
	for (int i = 0; i < A.size(); i++)
		fill(V[i].begin(), V[i].end(), false);
	queue<ii> q;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 > nx || nx >= A.size() || 0 > ny || ny >= A[0].size()) continue;
		V[nx][ny] = true;
		q.push({nx, ny});
	}
	int cnt = 1;
	while (!q.empty()) {
		int len = q.size();
		for (int i = 0; i < len; i++) {
			auto [cx, cy] = q.front(); q.pop();
			if (A[cx][cy] != '#') {
				if (value - (D[cx][cy] + cnt) >= 100)
					ret++;
			}
			for (int j = 0; j < 4; j++) {
				int nx = cx + dx[j];
				int ny = cy + dy[j];
				if (0 > nx || nx >= A.size() || 0 > ny || ny >= A[0].size()) continue;
				if (V[nx][ny]) continue;
				V[nx][ny] = true;
				q.push({nx, ny});
			}
		}
		if (cnt++ >= 20)
			break;
	}
	return ret;
}

int trace() {
	int ret = 0;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			if (A[i][j] != '#')
				ret += cbfs(i, j, D[i][j]);
		}
	}
	return ret;
}

void bfs(int x, int y) {
	queue<ii> q;
	D[x][y] = 0;
	q.push({x, y});
	while (!q.empty()) {
		auto [cx, cy] = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			int nd = D[cx][cy] + 1;
			if (0 > nx || nx >= A.size() || 0 > ny || ny >= A[i].size()) continue;
			if (A[nx][ny] == '#') continue;
			if (D[nx][ny] <= nd) continue;
			D[nx][ny] = nd;
			q.push({nx, ny});
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (getline(cin, S)) {
		vector<char> T;
		vector<int> tD(S.size(), 1e9);
		vector<bool> tV(S.size(), false);
		for (int i = 0; i < S.size(); i++)
			T.push_back(S[i]);
		A.push_back(T);
		D.push_back(tD);
		V.push_back(tV);
	}
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			if (A[i][j] == 'S') s = {i, j};
			else if (A[i][j] == 'E') e = {i, j};
		}
	}
	bfs(s.first, s.second);
	cout << trace() << '\n';
	return 0;
}