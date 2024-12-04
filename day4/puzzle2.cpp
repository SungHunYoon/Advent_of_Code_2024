#include <iostream>
#include <vector>

using namespace std;

string mas = "MAS";
vector<string> A;
string T[4] = {"MMSS", "MSMS", "SMSM", "SSMM"};
int dx[] = {-1, -1, 1, 1};
int dy[] = {-1, 1, -1, 1};

bool check(int x, int y) {
	string C;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 > nx || nx >= A.size() || 0 > ny || ny >= A[0].size())
			return false;
		C.push_back(A[nx][ny]);
	}
	for (int i = 0; i < 4; i++) {
		if (T[i] == C)
			return true;
	}
	return false;
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
			if (A[i][j] != 'A') continue;
			if (check(i, j)) answer++;
		}
	}
	cout << answer << '\n';

	return 0;
}