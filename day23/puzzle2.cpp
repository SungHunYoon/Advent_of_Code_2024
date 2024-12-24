#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

map<string, vector<string>> M;
set<set<string>> B;

bool checkInterConnect(vector<string> &s, int len) {
	vector<string> *arr1;
	vector<string> *arr2 = &M[s.back()];
	for (int i = 0; i < len - 1; i++) {
		arr1 = &M[s[i]];
		if (find(arr1->begin(), arr1->end(), s.back()) == arr1->end() ||
			find(arr2->begin(), arr2->end(), s[i]) == arr2->end())
			return false;
	}
	return true;
}

void dfs(int idx, vector<string> &A, vector<string> &s, int len) {
	if (s.size() >= len) {
		if (!checkInterConnect(s, s.size()))
			return;
		B.insert(set<string>(s.begin(), s.end()));
		return;
	}
	if (idx >= A.size())
		return;
	dfs(idx + 1, A, s, len);
	s.push_back(A[idx]);
	dfs(idx + 1, A, s, len);
	s.pop_back();
	return;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (getline(cin, S)) {
		int pos = S.find("-");
		string a = S.substr(0, pos);
		string b = S.substr(pos + 1);
		M[a].push_back(b);
		M[b].push_back(a);
	}
	vector<string> A;
	for (auto [k, v] : M)
		A.push_back(k);
	vector<string> T;
	dfs(0, A, T, 2);
	while (B.size() > 1) {
		set<set<string>> C;
		for (auto [k, v] : M) {
			for (auto it = B.begin(); it != B.end(); it++) {
				set<string> v(it->begin(), it->end());
				vector<string> t(v.begin(), v.end());
				if (!v.insert(k).second) continue;
				t.push_back(k);
				if (!checkInterConnect(t, t.size())) continue;
				C.insert(v);
			}
		}
		B = C;
	}
	string answer;
	for (auto v : B)
		for (auto s : v)
			answer += s + ",";
	answer.pop_back();
	cout << answer << '\n';
	return 0;
}