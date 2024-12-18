#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using ii = pair<int, int>;

#define W 71
#define H 71

vector<ii> B;
int A[W][H];
bool V[W][H];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs() {
	fill(&V[0][0], &V[W][0], false);
	queue<ii> q;
	V[0][0] = true;
	q.push({0, 0});
	int cnt = 0;
	while (!q.empty()) {
		int len = q.size();
		for (int i = 0; i < len; i++) {
			auto [x, y] = q.front(); q.pop();
			if (x == H - 1 && y == W - 1)
				return cnt;
			for (int j = 0; j < 4; j++) {
				int nx = x + dx[j];
				int ny = y + dy[j];
				if (0 > nx || nx >= H || 0 > ny || ny >= W) continue;
				if (A[nx][ny] || V[nx][ny]) continue;
				V[nx][ny] = true;
				q.push({nx, ny});
			}
		}
		cnt++;
	}
	return 0;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (getline(cin, S)) {
		int x = stoi(S);
		int y = stoi(S.substr(S.find(",") + 1));
		A[x][y] = 1;
		B.push_back({x, y});
	}
	int x, y;
	for (int i = B.size(); i > 0; i--) {
		int cnt = bfs();
		if (cnt) break;
		x = B[i].first;
		y = B[i].second;
		A[x][y] = 0;
	}
	cout << x << "," << y << '\n';
	return 0;
}