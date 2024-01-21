#include<iostream>
using namespace std;

int backtraking(int n,int sum) {
	//10으로 나누었을때 목은 다음계산값이고 나머지는 자리수값
	int nextcal = n / 10;
	sum += n % 10;
	//cout << sum << " ";
	if (nextcal == 0) {
		return sum;
	}
	backtraking(nextcal,sum);
}

int main() {
	int n;
	cin >> n;
	int ans = backtraking(n,0);
	cout << ans;
	return 0;
}
