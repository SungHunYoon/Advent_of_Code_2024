#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> A;
vector<vector<int>> V;

void checkPair(int x, int y) {
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A[i].size(); j++) {
			if (i == x && j == y) continue;
			if (A[x][y] != A[i][j]) continue;
			int nx = x + (x - i);
			int ny = y + (y - j);
			if (0 > nx || nx >= A.size() || 0 > ny || ny >= A[i].size()) continue;
			V[nx][ny] = 1;
		}
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (cin >> S) {
		vector<char> T;
		for (int i = 0; i < S.size(); i++)
			T.push_back(S[i]);
		A.push_back(T);
		vector<int> vT(T.size(), 0);
		V.push_back(vT);
	}
	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A[i].size(); j++)
			if (A[i][j] != '.')
				checkPair(i, j);
	int answer = 0;
	for (int i = 0; i < V.size(); i++)
		for (int j = 0; j < V[i].size(); j++)
			if (V[i][j])
				answer++;
	cout << answer << '\n';
	return 0;
}