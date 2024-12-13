#include <iostream>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;
using lll = tuple<long, long, long>;
using ll = pair<long, long>;

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	long answer = 0;
	long X[2], Y[2], tX, tY;
	long dc[] = {3, 1};
	while (getline(cin, S)) {
		if (S == "") {
			continue;
		}
		else if (S.find("Button A:") != string::npos) {
			X[0] = stol(S.substr(S.find("X") + 1));
			Y[0] = stol(S.substr(S.find("Y") + 1));
		} else if (S.find("Button B:") != string::npos) {
			X[1] = stol(S.substr(S.find("X") + 1));
			Y[1] = stol(S.substr(S.find("Y") + 1));
		} else {
			tX = stol(S.substr(S.find("X=") + 2));
			tY = stol(S.substr(S.find("Y=") + 2));
			map<ll, int> m;
			queue<lll> q;
			m.insert({{0, 0}, 0});
			q.push({0, 0, 0});
			long C = 1e9;
			while (!q.empty()) {
				auto [x, y, c] = q.front(); q.pop();
				if (tX == x && tY == y) {
					C = min(C, c);
					continue;
				}
				if (tX < x || tY < y) continue;
				for (int i = 0; i < 2; i++) {
					long nX = x + X[i];
					long nY = y + Y[i];
					auto it = m.find({nX, nY});
					if (it != m.end() && it->second <= c + dc[i]) continue;
					if (it != m.end())
						it->second = c + dc[i];
					else
						m.insert({{nX, nY}, c + dc[i]});
					q.push({nX, nY, c + dc[i]});
				}
			}
			if (C != 1e9)
				answer += C;
		}
	}
	cout << answer << '\n';
	return 0;
}
