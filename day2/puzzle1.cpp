#include <iostream>
#include <sstream>
#include <vector>

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
		bool flag = true, isAsc = true, isDesc = true;
		int prev = A[0];
		for (int i = 1; i < A.size(); i++) {
			int diff = abs(A[i] - prev);
			if (1 > diff || diff > 3) flag = false;
			if (A[i] > prev) isDesc = false;
			if (A[i] < prev) isAsc = false;
			prev = A[i];
		}
		if (!isAsc && !isDesc) flag = false;
		if (flag) answer++;
	}
	cout << answer << '\n';
	return 0;
}