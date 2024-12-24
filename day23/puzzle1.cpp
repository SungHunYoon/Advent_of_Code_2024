#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

vector<int> C;
map<string, vector<string>> M;

int dfs(int idx, vector<string> &A, vector<string> &s) {
	if (s.size() >= 3) {
		vector<string> &a = M[s[0]];
		vector<string> &b = M[s[1]];
		vector<string> &c = M[s[2]];
		if (find(a.begin(), a.end(), s[1]) != a.end() &&
			find(a.begin(), a.end(), s[2]) != a.end() &&
			find(b.begin(), b.end(), s[0]) != b.end() &&
			find(b.begin(), b.end(), s[2]) != b.end() &&
			find(c.begin(), c.end(), s[0]) != c.end() &&
			find(c.begin(), c.end(), s[1]) != c.end()) {
				return s[0][0] == 't' || s[1][0] == 't' || s[2][0] == 't'; 
		}
		return 0;
	}
	if (idx >= A.size())
		return 0;
	int ret = 0;
	ret += dfs(idx + 1, A, s);
	s.push_back(A[idx]);
	ret += dfs(idx + 1, A, s);
	s.pop_back();
	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	set<string> L;
	while (getline(cin, S)) {
		int pos = S.find("-");
		string a = S.substr(0, pos);
		string b = S.substr(pos + 1);
		L.insert(a);
		L.insert(b);
		M[a].push_back(b);
		M[b].push_back(a);
	}
	vector<string> A(L.begin(), L.end());
	vector<string> T;
	cout << dfs(0, A, T) << '\n';
	return 0;
}