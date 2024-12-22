#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

#define MOD 16777216

vector<__int128_t> T[2000];
vector<__int128_t> D[2000];
map<vector<__int128_t>, __int128_t> M;

string int128_to_string(__int128_t value) {
	if (value == 0) return "0";

	std::string result;
	while (value > 0) {
		result.push_back('0' + (value % 10));
		value /= 10;
	}
	reverse(result.begin(), result.end());
	return result;
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	int idx = 0;
	while (getline(cin, S)) {
		__int128_t secret = stol(S);
		T[idx].push_back(secret % 10);
		D[idx].push_back(0);
		for (int i = 1; i <= 2000; i++) {
			secret = (secret ^ (secret * 64)) % MOD;
			secret = (secret ^ (secret / 32)) % MOD;
			secret = (secret ^ (secret * 2048)) % MOD;
			T[idx].push_back(secret % 10);
			D[idx].push_back(T[idx][i] - T[idx][i - 1]);
		}
		idx++;
	}
	for (int i = 0; i < idx; i++){
		set<vector<__int128_t>> subarray;
		for (int j = 1; j <= D[i].size() - 4; j++) {
			vector<__int128_t> sub(D[i].begin() + j, D[i].begin() + j + 4);
			if (subarray.insert(sub).second) {
				M[sub] += T[i][j + 3];
			}
		}
	}
	__int128_t answer = 0;
	for (auto [v, b] : M) {
		answer = max(answer, b);
	}
	cout << int128_to_string(answer) << '\n';
	return 0;
}