#include <iostream>
#include <vector>

using namespace std;

long R[3];
vector<int> I;

void dfs(int idx, long v) {
	if (idx < 0) {
		cout << v / 8 << '\n';
		return;
	}
	for (int i = 0; i < 8; i++) {
		R[0] = v + i;
		R[1] = R[0] % 8;
		R[1] ^= 6;
		R[2] = R[0] / (1 << R[1]);
		R[1] ^= R[2];
		R[1] ^= 7;
		R[0] = R[0] / 8;
		if (I[idx] != R[1] % 8) continue;
		dfs(idx - 1, (v + i) * 8);
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int i = 0;
	string S;
	while (getline(cin, S)) {
		if (S == "") break;
		R[i] = stol(S.substr(S.find(": ") + 2));
		i++;
	}
	getline(cin, S);
	S = S.substr(S.find(": ") + 2);
	for (int i = 0; i < S.size(); i++)
		if (S[i] != ',') I.push_back(S[i] - '0');
	dfs(I.size() - 1, 0);
	return 0;
}

// B = A % 8;
// B = B ^ 6;
// C = A / (1 << B);
// B = B ^ C;
// B = B ^ 7;
// A = A / (1 << 3);
// cout << B << '\n';
