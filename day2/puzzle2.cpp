#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	int answer = 0;
	while (getline(cin, S)) {
		stringstream ss;
		vector<int> A;
		ss << S;
		int N;
		while (ss.peek() != EOF) {
			ss >> N;
			A.push_back(N);
		}
		A.insert(A.begin(), 0);
		vector<int> ASC((int)A.size());
		vector<int> DESC((int)A.size());
		for (int i = 1; i < A.size(); i++) {
			ASC[i] = 1;
			for (int j = 1; j < i; j++) {
				int diff = abs(A[i] - A[j]);
				if (A[i] >= A[j] && !(1 > diff || diff > 3))
					ASC[i] = max(ASC[i], ASC[j] + 1);
			}
		}
		for (int i = 1; i < A.size(); i++) {
			DESC[i] = 1;
			for (int j = 1; j < i; j++) {
				int diff = abs(A[i] - A[j]);
				if (A[i] <= A[j] && !(1 > diff || diff > 3))
					DESC[i] = max(DESC[i], DESC[j] + 1);
			}
		}
		if (*max_element(ASC.begin(), ASC.end()) >= ASC.size() - 2 ||
			*max_element(DESC.begin(), DESC.end()) >= DESC.size() - 2)
			answer++;
	}
	cout << answer << '\n';
	return 0;
}