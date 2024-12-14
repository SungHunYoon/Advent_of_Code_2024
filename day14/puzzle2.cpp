#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using ii = pair<int, int>;

#define WIDE 101
#define TALL 103

vector<int> A[TALL][WIDE];
vector<int> B[TALL][WIDE];
vector<ii> V;
bool VT[TALL][WIDE];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int bfs(int x, int y) {
	queue<ii> q;
	int cnt = 0;
	VT[x][y] = true;
	q.push({x, y});
	while (!q.empty()) {
		auto [x, y] = q.front(); q.pop();
		cnt++;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 > nx || nx >= TALL || 0 > ny || ny >= WIDE) continue;
			if (VT[nx][ny] || !A[nx][ny].size()) continue;
			VT[nx][ny] = true;
			q.push({nx, ny});
		}
	}
	return cnt;
}

void printArray(int idx) {
	cout << "======" << idx << "=====\n";
	for (int i = 0; i < TALL; i++) {
		for (int j = 0; j < WIDE; j++) {
			if (A[i][j].size())
				cout << "*";
			else
				cout << " ";
		}
		cout << '\n';
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (getline(cin, S)) {
		int pos = S.find(" ");
		string p = S.substr(0, pos);
		string s = S.substr(pos + 1);
		pos = s.find(",");
		int x = stoi(s.substr(2, pos - 2));
		int y = stoi(s.substr(pos + 1));
		V.push_back({y, x});
		pos = p.find(",");
		x = stoi(p.substr(2, pos - 2));
		y = stoi(p.substr(pos + 1));
		A[y][x].push_back(V.size() - 1);
	}
	int i = 0;
	for (;;) {
		for (int j = 0; j < TALL; j++) {
			for (int k = 0; k < WIDE; k++) {
				for (int R : A[j][k]) {
					auto [x, y] = V[R];
					int nx = (j + x + TALL) % TALL;
					int ny = (k + y + WIDE) % WIDE;
					B[nx][ny].push_back(R);
				}
			}
		}
		for (int j = 0; j < TALL; j++) {
			for (int k = 0; k < WIDE; k++) {
				A[j][k] = B[j][k];
				B[j][k].clear();
			}
		}
		fill(&VT[0][0], &VT[TALL][0], false);
		for (int j = 0; j < TALL; j++) {
			for (int k = 0; k < WIDE; k++) {
				if (!VT[j][k] && A[j][k].size() && bfs(j, k) >= 50) {
					printArray(i + 1);
					return 0;
				}
			}
		}
		i++;
	}
	return 0;
}