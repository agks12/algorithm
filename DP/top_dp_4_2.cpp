#include<iostream>
using namespace std;

struct Pair { int day, cost; };
int n, DP[101];
Pair arr[101];

int dp(int now) {
	//if (now == 0)return 0;
	if (now > n)return 0;
	if (DP[now] != -21e8)return DP[now];

	int Max = -21e8;
	for (int i = 0; i < arr[now].day; i++) {
		//내 날짜랑 겹치는 애들거만 다 돌려보고 그중에서 최대값 고르는 형식
		// 1일 이면 1일 + 1일값만쿰
		// 다음턴에 2일 + 2일값만큼
		// 다음턴에 3일 + 3일 값만큼
		// now = 1, 1일값은 3이라 3번 돔
		// i==1 -> dp(1 + 3) -> 4일꺼 가능
		// i==2 -> dp(2 + 5) 
		// i==3 -> dp(3 + 1)
		// 내날짜 에 겹치는 애들 모두 계산하려고 i<arr[now].day
		// 아래 now+i 하는 거는 내 알에 애들은 날짜가 +1씩 되기 때문에 
		int ret = dp((now + i) + arr[now + i].day) + arr[now + i].cost;//
		if (ret > Max)Max = ret;
	}

	//지금 일자에는 최대 이만큼 쌓임
	DP[now] = Max;
	return DP[now];
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i].day;
		cin >> arr[i].cost;
		DP[i] = -21e8;
	}
	DP[0] = -21e8;
	int ans = dp(1);
	cout << ans;
	return 0;
}
