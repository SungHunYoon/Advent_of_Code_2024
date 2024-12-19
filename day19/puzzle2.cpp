#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> C;
long D[100];

long dfs(string &s, int idx) {
	if (idx >= s.size())
		return 1;
	if (D[idx])
		return D[idx];
	long ret = 0;
	for (int i = 0; i + idx < s.size(); i++) {
		if (find(C.begin(), C.end(), s.substr(idx, i + 1)) != C.end())
			ret += dfs(s, i + idx + 1);
	}
	D[idx] = ret;
	return ret;
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
		fill(D, D + 100, 0);
		answer += dfs(S, 0);
	}
	cout << answer << '\n';
	return 0;
}