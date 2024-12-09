#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	cin >> S;
	S.push_back('0');
	vector<int> V;
	vector<int> C;
	for (int i = 0, idx = 0; i < S.size(); i += 2, idx++) {
		for (int j = 0; j < S[i] - '0'; j++)
			V.push_back(idx);
		for (int j = 0; j < S[i + 1] - '0'; j++)
			V.push_back(-1);
		C.push_back(S[i] - '0');
	}
	for (int i = C.size() - 1; i >= 0; i--) {
		int cnt = 0;
		int dis = distance(V.begin(), find(V.begin(), V.end(), i));
		for (int j = 0; j < V.size() && j < dis; j++) {
			if (V[j] == -1) cnt++;
			else cnt = 0;
			if (C[i] && cnt >= C[i]) {
				for (int k = 0; k < C[i]; k++, dis++)
					swap(V[j - k], V[dis]);
				C[i] = 0;
				break;
			}
		}
	}
	long checksum = 0;
	for (long i = 0; i < V.size(); i++)
		if (V[i] != -1)
			checksum += i * V[i];
	cout << checksum << '\n';
	return 0;
}