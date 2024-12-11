#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

map<string, long> M[75];

long dfs(string s, int idx) {
	if (idx >= 75)
		return 1;
	auto it = M[idx].find(s);
	if (it != M[idx].end())
		return it->second;
	long ret = 0;
	if (s == "0")
		ret += dfs("1", idx + 1);
	else if (!(s.size() % 2)) {
		string left = to_string(stol(s.substr(0, s.size() / 2)));
		string right = to_string(stol(s.substr(s.size() / 2)));
		ret += dfs(left, idx + 1);
		ret += dfs(right, idx + 1);
	}
	else
		ret += dfs(to_string(stol(s) * 2024), idx + 1);
	M[idx][s] = ret;
	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	getline(cin, S);
	stringstream ss;
	ss << S;
	vector<string> A;
	while (!ss.eof()) {
		string num;
		ss >> num;
		A.push_back(num);
	}
	long answer = 0;
	for (int i = 0; i < A.size(); i++) {
		answer += dfs(A[i], 0);
	}
	cout << answer << '\n';
	return 0;
}