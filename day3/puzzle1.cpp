#include <iostream>

using namespace std;

string s = "mul";

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	int answer = 0;
	while (cin >> S) {
		size_t end = 0;
		while ((end = S.find(s, end)) != string::npos) {
			int state = 0;
			int fNum = 0;
			int sNum = 0;
			int idx = 4;
			int sIdx = 0;
			while (state < 3 && end + idx < S.length()) {
				if (state == 0) {
					if (end + 3 < S.length() && S[end + 3] == '(')
						state = 1;
					else
						break;
				} else if (state == 1) {
					while (end + idx < S.length()) {
						if ('0' <= S[end + idx] && S[end + idx] <= '9')
							idx++;
						else if (S[end + idx] == ',') {
							state = 2;
							fNum = stoi(S.substr(end + 4, idx - 4));
							idx++;
							sIdx = idx;
							break;
						} else {
							state = 4;
							break;
						}
					}
				} else if (state == 2) {
					while (end + idx < S.length()) {
						if ('0' <= S[end + idx] && S[end + idx] <= '9')
							idx++;
						else if (S[end + idx] == ')') {
							state = 3;
							sNum = stoi(S.substr(end + sIdx, idx - sIdx));
							idx++;
							break;
						} else {
							state = 4;
							break;
						}
					}
				}
			}
			if (state == 3) answer += fNum * sNum;
			end += s.length();
		}
	}
	cout << answer << '\n';
	return 0;
}