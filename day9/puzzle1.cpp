#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	cin >> S;
	S.push_back('0');
	vector<int> V;
	for (int i = 0, idx = 0; i < S.size(); i += 2, idx++) {
		for (int j = 0; j < S[i] - '0'; j++)
			V.push_back(idx);
		for (int j = 0; j < S[i + 1] - '0'; j++)
			V.push_back(-1);
	}
	int s = 0, e = V.size() - 1;
	while (s <= e) {
		if (V[s] != -1) s++;
		else if (V[e] == -1) e--;
		else {
			V[s] = V[e];
			V[e] = -1;
		}
	}
	long checksum = 0;
	for (long i = 0; i < V.size(); i++)
		if (V[i] != -1)
			checksum += i * V[i];
	cout << checksum << '\n';
	return 0;
}