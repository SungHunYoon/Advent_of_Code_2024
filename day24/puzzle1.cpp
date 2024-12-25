#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<string, long> M;
vector<string> A;
string T[] = {" OR ", " XOR ", " AND "};

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	while (getline(cin, S)) {
		if (S == "") break;
		int pos = S.find(": ");
		M[S.substr(0, pos)] = stoi(S.substr(pos + 2));
	}
	while (getline(cin, S))
		A.push_back(S);
	while (A.size()) {
		for (auto it = A.begin(); it != A.end(); it++) {
			string s1, s2;
			int i;
			for (i = 0; i < 3; i++) {
				size_t pos = it->find(T[i]);
				if (pos != string::npos) {
					s1 = it->substr(0, 3);
					s2 = it->substr(pos + T[i].size(), 3);
					break;
				}
			}
			if (M.find(s1) != M.end() && M.find(s2) != M.end()) {
				string rst = it->substr(it->size() - 3);
				if (i == 0) M[rst] = M[s1] | M[s2];
				else if (i == 1) M[rst] = M[s1] ^ M[s2];
				else M[rst] = M[s1] & M[s2];
				it = A.erase(it) - 1;
			}
		}
	}
	long answer = 0;
	long idx = 0;
	for (auto [k, v] : M) {
		if (k[0] == 'z')
			answer += (v << idx++);
	}
	cout << answer << '\n';
	return 0;
}