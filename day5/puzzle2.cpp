#include <iostream>
#include <vector>

using namespace std;

vector<int> V[101];

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	int answer = 0;
	while (cin >> S) {
		if (S.find(',', 0) == string::npos) {
			int a = stoi(S.substr(0, 2));
			int b = stoi(S.substr(3, 2));
			V[a].push_back(b);
		} else {
			vector<int> T;
			for (int i = 0; i < S.size(); i++) {
				T.push_back(stoi(S.substr(i, 2)));
				i += 2;
			}
			bool flag = true;
			for (int i = 0; i < T.size(); i++)
				for (int j = i + 1; j < T.size(); j++)
					if (find(V[T[j]].begin(), V[T[j]].end(), T[i]) != V[T[j]].end())
						flag = false;
			if (flag) continue;
			vector<int> A;
			while (T.size()) {
				if (T.size() == 1) {
					A.push_back(T[0]);
					T.erase(T.begin());
				} else {
					vector<int> D(T.size());
					for (int i = 0; i < T.size(); i++) {
						for (int j = 0; j < T.size(); j++) {
							if (i == j) continue;
							if (find(V[T[j]].begin(), V[T[j]].end(), T[i]) != V[T[j]].end())
								D[i]++;
						}
					}
					auto it = min_element(D.begin(), D.end());
					int dis = distance(D.begin(), it);
					A.push_back(T[dis]);
					T.erase(T.begin() + dis);
				}
			}
			answer += A[A.size() / 2];
		}
	}
	cout << answer << '\n';

	return 0;
}