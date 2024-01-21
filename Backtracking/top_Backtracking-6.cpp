#include<iostream>
using namespace std;

int DAT[14];
int DATadd[30];// / 방향대각선
int DATsus[30];// \ 방향대각선
int cnt = 0;
void back(int n,int row) {
	if (row == n) {
		cnt++;
		return;
	}
	for (int col = 0; col < n; col++) {
		//level 이 i역활
		if (DAT[col] == 1)continue;
		if (DATadd[col + row] == 1)continue;
		if(DATsus[col - row+n] == 1)continue;
		DAT[col] = 1;
		DATadd[col + row] = 1;// / 방향대각선 gpt 가알려준 방향은 이거지만 \ 가 원리상 맞는듯
		DATsus[col - row+n] = 1;// \ 방향대각선  원래 합이랑 차가 같아야 맞지만 차는 음수(-)될수도 있으므로 안되게 +N해줌
		back(n, row + 1);
		DAT[col] = 0;
		DATadd[col + row] = 0;
		DATsus[col - row+n] = 0;
	}
}
int main() {
	int n; cin >> n;
	back(n, 0);
	cout << cnt;
	return 0;
}
