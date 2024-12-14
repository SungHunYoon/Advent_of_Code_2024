#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ii = pair<int, int>;

#define WIDE 101
#define TALL 103

vector<int> A[TALL][WIDE];
vector<int> B[TALL][WIDE];
vector<ii> V;

long cntArray(int sx, int ex, int sy, int ey) {
	long cnt = 0;
	for (int i = sx; i < ex; i++)
		for (int j = sy; j < ey; j++)
			cnt += A[i][j].size();
	return cnt;
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
	for (int i = 0; i < 100; i++) {
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
	}
	long a = cntArray(0, TALL / 2, 0, WIDE / 2);
	long b = cntArray(0, TALL / 2, WIDE / 2 + 1, WIDE);
	long c = cntArray(TALL / 2 + 1, TALL, 0, WIDE / 2);
	long d = cntArray(TALL / 2 + 1, TALL, WIDE / 2 + 1, WIDE);
	cout << a * b * c * d << '\n';
	return 0;
}