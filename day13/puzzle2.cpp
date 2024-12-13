#include <iostream>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	long answer = 0;
	long X[2], Y[2], tX, tY;
	while (getline(cin, S)) {
		if (S == "") {
			continue;
		}
		else if (S.find("Button A:") != string::npos) {
			X[0] = stol(S.substr(S.find("X") + 1));
			Y[0] = stol(S.substr(S.find("Y") + 1));
		} else if (S.find("Button B:") != string::npos) {
			X[1] = stol(S.substr(S.find("X") + 1));
			Y[1] = stol(S.substr(S.find("Y") + 1));
		} else {
			tX = stol(S.substr(S.find("X=") + 2)) + 10000000000000L;
			tY = stol(S.substr(S.find("Y=") + 2)) + 10000000000000L;
			long a = (tY * X[1] - Y[1] * tX) / (X[1] * Y[0] - Y[1] * X[0]);
			long b = (tX - X[0] * a) / X[1];
			if (a * X[0] + b * X[1] == tX && a * Y[0] + b * Y[1] == tY)
				answer += a * 3 + b;
		}
	}
	cout << answer << '\n';
	return 0;
}
