#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int L[1001], R[1001];

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	for (int i = 0; i < 1000; i++)
		cin >> L[i] >> R[i];
	map<int, int> M;
	int answer = 0;
	for (int i = 0; i < 1000; i++) {
		int cnt = count(R, R + 1000, L[i]);
		if (M.insert({L[i], cnt}).second)
			answer += L[i] * cnt;
	}
	cout << answer << '\n';
	return 0;
}