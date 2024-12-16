#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;
using iii = tuple<int, int, int, int>;

vector<vector<char>> A;
vector<vector<int>> V;
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	queue<iii> q;
	while (getline(cin, S)) {
		vector<char> T;
		vector<int> tV(S.size(), 1e9);
		for (int i = 0; i < S.size(); i++)
			T.push_back(S[i]);
		A.push_back(T);
		V.push_back(tV);
	}
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			if (A[i][j] == 'S') {
				V[i][j] = 0;
				q.push({i, j, 0, 3});
			}
		}
	}
	int answer = 1e9;
	while (!q.empty()) {
		auto [x, y, s, d] = q.front(); q.pop();
		if (A[x][y] == 'E')
			answer = min(answer, s);
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			int ns = (d != i) ? 1001 : 1;
			if (A[nx][ny] == '#') continue;
			if (s + ns >= V[nx][ny]) continue;
			V[nx][ny] = s + ns;
			q.push({nx, ny, V[nx][ny], i});
		}
	}
	cout << answer << '\n';
	return 0;
}