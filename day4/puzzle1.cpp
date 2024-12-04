#include <iostream>
#include <vector>

using namespace std;

string xmas = "XMAS";
vector<string> A;
int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
int dy[] = {0, 0, 1, -1, -1, -1, 1, 1};

bool dfs(int idx, int x, int y, int dir) {
	if (idx >= 4)
		return true;
	if (0 > x || x >= A.size() || 0 > y || y >= A[0].size())
		return false;
	if (A[x][y] != xmas[idx])
		return false;
	return dfs(idx + 1, x + dx[dir], y + dy[dir], dir);
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (cin >> S)
		A.push_back(S);
	int answer = 0;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			for (int k = 0; k < 8; k++) {
				answer += dfs(0, i, j, k);
			}
		}
	}
	cout << answer << '\n';
	return 0;
}