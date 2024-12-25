#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> L;
vector<vector<int>> K;
vector<string> T;
int H;

bool checkLock(vector<int> &l, vector<int> &k) {
	for (int i = 0; i < l.size(); i++) {
		if (l[i] + k[i] > H - 2)
			return false;
	}
	return true;
}

void parseString() {
	vector<int> seq(T[0].size());
	for (int i = 1; i < T.size() - 1; i++)
		for (int j = 0; j < T[i].size(); j++)
			if (T[i][j] == '#') seq[j]++;
	if (count(T[0].begin(), T[0].end(), '#') == T[0].size()) {
		for (int i = 0; i < T[0].size(); i++)
			if (T[T.size() - 1][i] == '#') seq[i]++;
		L.push_back(seq);
	} else {
		for (int i = 0; i < T[0].size(); i++)
			if (T[0][i] == '#') seq[i]++;
		K.push_back(seq);
	}
	H = T.size();
	T.clear();
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (getline(cin, S)) {
		if (S != "") {
			T.push_back(S);
			continue;
		}
		parseString();
	}
	if (T.size()) parseString();
	long answer = 0;
	for (int i = 0; i < L.size(); i++)
		for (int j = 0; j < K.size(); j++)
			if (checkLock(L[i], K[j]))
				answer++;
	cout << answer << '\n';
	return 0;
}