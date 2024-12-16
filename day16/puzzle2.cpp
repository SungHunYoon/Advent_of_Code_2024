#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;
using iii = tuple<int, int, int, int>;
using ii = pair<int, int>;

vector<vector<char>> A;
vector<vector<int>> V;
vector<vector<bool>> TraceV;
ii E;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int findDir(int px, int py, int x, int y) {
	int dX = x - px;
	int dY = y - py;
	int ret = -1;
	for (int i = 0; i < 4; i++) {
		if (dX == dx[i] && dY == dy[i])
			ret = i;
	}
	return ret;
}

int dfs(int x, int y, int pv, int pdir) {
	if (pv < V[x][y]) return 0;
	int ret = 1;
	TraceV[x][y] = true;
	for (int i = 0; i < 4; i++) {
		int px = x + dx[i];
		int py = y + dy[i];
		if (!TraceV[px][py]) {
			int d = findDir(px, py, x, y);
			int v = pv;
			if (pdir != -1) {
				v--;
				if (d != pdir) v -= 1000;
			}
			ret += dfs(px, py, v, d);
		}
	}
	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	queue<iii> q;
	while (getline(cin, S)) {
		vector<char> T;
		vector<int> tV(S.size(), 1e9);
		vector<bool> ttV(S.size(), false);
		for (int i = 0; i < S.size(); i++)
			T.push_back(S[i]);
		A.push_back(T);
		V.push_back(tV);
		TraceV.push_back(ttV);
	}
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			if (A[i][j] == 'S') {
				V[i][j] = 0;
				q.push({i, j, 0, 3});
			} else if (A[i][j] == 'E')
				E = {i, j};
		}
	}
	int answer = 1e9;
	while (!q.empty()) {
		auto [x, y, s, d] = q.front(); q.pop();
		if (A[x][y] == 'E') {
			answer = min(answer, s);
			continue;
		}
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			int ns = (d != i) ? 1001 : 1;
			if (A[nx][ny] == '#') continue;
			if (s + ns > V[nx][ny]) continue;
			V[nx][ny] = s + ns;
			q.push({nx, ny, V[nx][ny], i});
		}
	}
	cout << dfs(E.first, E.second, answer, -1) << '\n';
	return 0;
}