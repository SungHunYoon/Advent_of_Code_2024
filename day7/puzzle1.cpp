#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool dfs(vector<long> &v, int idx, long val, long val2) {
	if (idx >= v.size()) {
		if (val == val2)
			return true;
		return false;
	}
	if (dfs(v, idx + 1, val + v[idx], val2))
		return true;
	return dfs(v, idx + 1, val * v[idx], val2);
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	long answer = 0;
	while (getline(cin, S)) {
		stringstream ss;
		long num = stol(S);
		ss << S.substr(S.find(": ", 0) + 2);
		vector<long> V;
		while (!ss.eof()) {
			long n;
			ss >> n;
			V.push_back(n);
		}
		if (dfs(V, 1, V[0], num))
			answer += num;
	}
	cout << answer << '\n';
	return 0;
}