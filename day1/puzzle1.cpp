#include <iostream>
#include <algorithm>

using namespace std;

int L[1001], R[1001];

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	for (int i = 0; i < 1000; i++)
		cin >> L[i] >> R[i];
	sort(L, L + 1000);
	sort(R, R + 1000);
	int answer = 0;
	for (int i = 0; i < 1000; i++)
		answer += abs(L[i] - R[i]);
	cout << answer << '\n';
	return 0;
}