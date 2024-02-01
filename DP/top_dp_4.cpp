//C++ (Top-Down)
#include <iostream>
using namespace std;

int n;
int times[200];
int money[200];
int memo[200];

int getMaxMoney(int base)
{
	if (base >= n) return 0;
	if (memo[base] != 0) return memo[base];

	int max = 0;
	for (int i = 0; i < times[base]; i++) {
		int now = base + i;
		int ret = getMaxMoney(now + times[now]) + money[now];
		if (ret > max) max = ret;
	}

	memo[base] = max;
	return memo[base];
}

int main()
{
	//freopen("text.txt", "r", stdin);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> times[i] >> money[i];
	}

	int ret = getMaxMoney(0);
	cout << ret << endl;

	return 0;
}
 

//C++ (Bottom-Up)
#include<iostream>
using namespace std;

struct Pair { int day, cost; };
int N;
Pair arr[101];
int dp[101];
int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin>>arr[i].day>>arr[i].cost;
		dp[i] = arr[i].cost;
	}

	for (int i = 1; i <= N; i++) {
		//cout << "nowday = " << i << " ";
		
		//아래 j = i + arr[i].day 이렇게 설정하면 
		// 지금이 1일이고 1일날 3일 소요라 하면 2,3일까지는 지나쳐가므로
		// 그런 경우 어차피 볼필요 없어서 j = i + arr[i].day 시작함
		for (int j = i + arr[i].day; j <= N; j++) {
			//cout << "j값" << j << " ";
			//cout << "지금날짜 최대값" << dp[j]<<" ";
			
			// 이거가 핵심끝인데 
			// 지금 날 로부터 소요시간다 써서 도착할 수 있는 모든날
			// 예로 들어 지금이 첫 날이고 3일 소요된다면 4,5,일이 갈 수 있는데
			// 4,5 일 각각(j=4,j=5)에 대해 구해진 dp[4],dp[5] 값이랑 지금 구한값
			// dp[i](지금 날) + arr[j].cost(도착날) 중에서 큰거 사용하면 최대로 갱신가능
			dp[j] = max(dp[j], dp[i] + arr[j].cost);

			//cout << "지금날짜 최대값적용" << dp[j];

		}
		cout << "\n";
	}
	cout << dp[N];

	return 0;
}
