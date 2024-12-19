#include <iostream>
#include <vector>

using namespace std;

vector<string> C;

bool dfs(string &s, int idx) {
	if (idx >= s.size())
		return true;
	for (int i = 0; i + idx < s.size(); i++) {
		if (find(C.begin(), C.end(), s.substr(idx, i + 1)) != C.end()) {
			if (dfs(s, i + idx + 1))
				return true;
		}
	}
	return false;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	getline(cin, S);
	size_t end = 0;
	size_t lastEnd = 0;
	while ((end = S.find(", ", end)) != string::npos) {
		C.push_back(S.substr(lastEnd, end - lastEnd));
		end += 2;
		lastEnd = end;
	}
	C.push_back(S.substr(lastEnd));
	long answer = 0;
	while (getline(cin, S)) {
		if (S == "") continue;
		answer += dfs(S, 0);
	}
	cout << answer << '\n';
	return 0;
}