#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

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
	for (int k = 0; k < 25; k++) {
		for (int i = 0; i < A.size(); i++) {
			if (A[i] == "0") A[i] = "1";
			else if (!(A[i].size() % 2)) {
				string left = to_string(stol(A[i].substr(0, A[i].size() / 2)));
				string right = to_string(stol(A[i].substr(A[i].size() / 2)));
				A[i] = left;
				A.insert(A.begin() + i, right);
				i++;
			} else {
				long num = stol(A[i]) * 2024;
				A[i] = to_string(num);
			}
		}
	}
	cout << A.size() << '\n';
	return 0;
}