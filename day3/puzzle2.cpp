#include <iostream>
#include <vector>

using namespace std;

string s = "mul";
string dont = "don't()";
string doo = "do()";

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string totalS;
	string S;
	int answer = 0;
	while (cin >> S) {
		totalS += S;
	}
	vector<int> D(totalS.size());
	size_t end = 0;
	D[0] = 1;
	while ((end = totalS.find(doo, end)) != string::npos) {
		D[end] = 1;
		end++;
	}
	end = 0;
	while ((end = totalS.find(dont, end)) != string::npos) {
		D[end] = 2;
		end++;
	}
	int prev = 0;
	for (int i = 0; i < D.size(); i++) {
		if (D[i] != 0) prev = D[i];
		else D[i] = prev;
	}
	end = 0;
	while ((end = totalS.find(s, end)) != string::npos) {
		if (D[end] != 1) {
			end += s.length();
			continue;
		}
		int state = 0;
		int fNum = 0;
		int sNum = 0;
		int idx = 4;
		int sIdx = 0;
		while (state < 3 && end + idx < totalS.length()) {
			if (state == 0) {
				if (end + 3 < totalS.length() && totalS[end + 3] == '(')
					state = 1;
				else
					break;
			} else if (state == 1) {
				while (end + idx < totalS.length()) {
					if ('0' <= totalS[end + idx] && totalS[end + idx] <= '9')
						idx++;
					else if (totalS[end + idx] == ',') {
						state = 2;
						fNum = stoi(totalS.substr(end + 4, idx - 4));
						idx++;
						sIdx = idx;
						break;
					} else {
						state = 4;
						break;
					}
				}
			} else if (state == 2) {
				while (end + idx < totalS.length()) {
					if ('0' <= totalS[end + idx] && totalS[end + idx] <= '9')
						idx++;
					else if (totalS[end + idx] == ')') {
						state = 3;
						sNum = stoi(totalS.substr(end + sIdx, idx - sIdx));
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
	cout << answer << '\n';
	return 0;
}