#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ii = pair<int, int>;

#define CNT 2

int numKey[4][3] = {
	{'7', '8', '9'},
	{'4', '5', '6'},
	{'1', '2', '3'},
	{0, '0', 'A'}
};

int arrowKey[2][3] = {
	{0, '^', 'A'},
	{'<', 'v', '>'}
};

long matchKeypad(const string &keys, int step);

ii findKey(int step, char key) {
	int maxX = step == 0 ? 4 : 2;
	int maxY = 3;
	for (int i = 0; i < maxX; i++) {
		for (int j = 0; j < maxY; j++) {
			if (step == 0 && numKey[i][j] == key)
				return {i, j};
			else if (step > 0 && arrowKey[i][j] == key)
				return {i, j};
		}
	}
	return {-1, -1};
}

bool isValid(int step, int mov, ii cPos, ii nPos) {
	bool ret = false;
	if (step == 0) {
		if (mov == 0) ret = numKey[nPos.first][cPos.second] != 0;
		else ret = numKey[cPos.first][nPos.second] != 0;
	} else {
		if (mov == 0) ret = arrowKey[nPos.first][cPos.second] != 0;
		else ret = arrowKey[cPos.first][nPos.second] != 0;
	}
	return ret;
}

long dfs(char cKey, char nKey, int step) {
	ii cPos = findKey(step, cKey);
	ii nPos = findKey(step, nKey);
	string xStr = string(abs(nPos.first - cPos.first), nPos.first < cPos.first ? '^' : 'v');
	string yStr = string(abs(nPos.second - cPos.second), nPos.second > cPos.second ? '>' : '<');
	long cost = 1e18;
	if (isValid(step, 0, cPos, nPos))
		cost = min(cost, matchKeypad(xStr + yStr + "A", step + 1));
	if (isValid(step, 1, cPos, nPos))
		cost = min(cost, matchKeypad(yStr + xStr + "A", step + 1));
	return cost;
}

long matchKeypad(const string &keys, int step) {
	if (step > CNT)
		return keys.size();
	long ret = 0;
	char cKey = 'A';
	for (char k : keys) {
		ret += dfs(cKey, k, step);
		cKey = k;
	}
	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	long answer = 0;
	while (getline(cin, S)) {
		int num = stoi(S.substr(0, S.size() - 1));
		answer += num * matchKeypad(S, 0);
	}
	cout << answer << '\n';
	return 0;
}
