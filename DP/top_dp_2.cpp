//top down 방식
#include<iostream>
using namespace std;

int arr[160];
int dp[160];
int DP(int now) {
	if (now == 0) {
		return 0;
	}
	if (now < 0) {
		return -1e9;
	}
	if (dp[now] != -1e9)return dp[now]; // 한번 저장(dp핵심) 했으면 끝까지 재귀 필요없이 바로 리턴
	int a = DP(now - 2);
	int b = DP(now - 7);	
	// 이렇게 하면 피보나치처럼 계속들어감
	int m = max(a, b);
	dp[now] = m + arr[now]; // 이렇게 배열에 값저장해야 다음 에서 계산할때 재귀안하고 바로 값가져오는 DP의 핵심인듯
	return dp[now]; //앞에서 구한것들중 제일 큰값 + 내위치값 을 리턴
}
int main() {
	int n; cin >> n;
	for (int i = 1; i <= n; i++)cin>>arr[i];
	for (int i = 0; i < 160; i++)dp[i] = -1e9;//이렇게 해야 방문 한지 안한지 암, 0으로 하면 -구분 못해서 안됨
	int result = -1e9;
	for (int i = n + 1; i <= n + 6; i++) {
		//이렇게 i번 돌린다고 쳐도 dp배열 초기화 안하면 안되지 않나?
		int now = DP(i);
		if (now > result)result = now;
	}
	cout << result;
	return 0;
}

//bottom-up강사
#include <iostream>
using namespace std;

int arr[200];
int dp[200];

int main() {
	int N;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> arr[i];

	//Bottom-Up
	int MIN = -21e8;
	for (int i = 0; i <= N + 5; i++)
		dp[i] = MIN;

	// 일단 2칸씩 가는 칸을 모두 채움 -> 2에서 7칸을 점프해서 N을 5만큼 넘어갈수 있는 공간까지 확인한다
	dp[0] = 0;
	for (int i = 2; i <= N + 5; i++) {
		dp[i] = dp[i - 2] + arr[i];
	}

	// 7까지 점프하는 방법은 0->7 하나
	dp[7] = 7;
	// 이후로부터 특정 칸에 도달하기 위한 값 = 2칸 전에서 점프했거나, 7칸 전에서 점프했거나
	for (int i = 7; i <= N + 5; i++) {
		dp[i] = max(dp[i - 7] + arr[i], dp[i - 2] + arr[i]);
	}

	int ans = -21e8;

	// N~N+5까지의 공간중 최대값을 확인
	for (int i = N; i <= N + 5; i++) {
		if (dp[i] > ans)
			ans = dp[i];
	}
	cout << ans;
}
