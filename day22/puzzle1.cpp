#include <iostream>
#include <algorithm>

using namespace std;

#define MOD 16777216

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
	__int128_t answer = 0;
	while (getline(cin, S)) {
		__int128_t secret = stol(S);
		for (int i = 0; i < 2000; i++) {
			secret = (secret ^ (secret * 64)) % MOD;
			secret = (secret ^ (secret / 32)) % MOD;
			secret = (secret ^ (secret * 2048)) % MOD;
		}
		answer += secret;
	}
	cout << int128_to_string(answer) << '\n';
	return 0;
}