#include <iostream>
#include <vector>

using namespace std;

long R[3];
long C[8];
vector<int> I;
int idx;
void (*func[8])();
string answer;

void updateReg() {
	C[4] = R[0];
	C[5] = R[1];
	C[6] = R[2];
}

void initCombo() {
	for (int i = 0; i < 4; i++)
		C[i] = i;
	updateReg();
}

void adv(void) {
	R[0] = R[0] / (1 << C[I[++idx]]);
	++idx;
}

void bdv(void) {
	R[1] = R[0] / (1 << C[I[++idx]]);
	++idx;
}

void cdv(void) {
	R[2] = R[0] / (1 << C[I[++idx]]);
	++idx;
}

void bxl(void) {
	R[1] = R[1] ^ I[++idx];
	++idx;
}

void bst(void) {
	R[1] = C[I[++idx]] % 8;
	++idx;
}

void jnz(void) {
	if (R[0] == 0) {
		idx += 2;
		return;
	}
	idx = I[idx + 1];
}

void bxc(void) {
	idx += 2;
	R[1] = R[1] ^ R[2];
}

void out(void) {
	answer += to_string(C[I[++idx]] % 8) + ',';
	idx++;
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
	initCombo();
	func[0] = adv; func[1] = bxl; func[2] = bst;
	func[3] = jnz; func[4] = bxc; func[5] = out;
	func[6] = bdv; func[7] = cdv;
	while (idx < I.size()) {
		func[I[idx]]();
		updateReg();
	}
	if (answer.size()) answer.pop_back();
	cout << answer << '\n';
	return 0;
}