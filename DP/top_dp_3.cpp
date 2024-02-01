//그냥 dfs인데 높은수부터 해서 빠르게 찾음
#include<iostream>
#include<algorithm>
using namespace std;
int tar,n;
int flag = 0;
int ans;
int m(int level,int now) {
	if (tar == 0) {
		ans = level;
		flag = 1;
		return -1;
	}
	if (tar < 0) {
		return -1;
	}
	for (int i = n-1; i >=0; i--) {
		tar -= arr[i];
		m(level + 1, i);
		tar += arr[i];
		if (flag == 1)return ans;
	}
}
int main() {
	cin >> tar >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + n);
	int ans2 = m(0,n-1);
	if (ans2 == -1)cout << "impossible";
	else cout << ans;
	//for (int i = 0; i <= 100; i++)dp[i] = 1e9;
	//topDown(tar,0);
	return 0;
}

//(Top-Down)
#include <iostream>
using namespace std;

int memo[10000];
int dong[10000];
int dn;

int getMinCnt(int t)
{
	if (t == 0) {
		return 0;
	}
	if (t < 0) return 21e8;
	if (memo[t] != 0) return memo[t];

	int min = 21e8;
	for (int i = 0; i < dn; i++) {
		int ret = getMinCnt(t - dong[i]);
		if (ret < min) min = ret;
	}

	memo[t] = min + 1;
	return min + 1;
}

int main()
{
	//freopen("text.txt", "r", stdin);

	int t, n;
	cin >> t >> dn;
	for (int i = 0; i < dn; i++) cin >> dong[i];

	int ret = getMinCnt(t);
	
	if (ret >= 21e8) {
		cout << "impossible";
		return 0;
	}

	cout << ret;	
	return 0;
}


//(Bottom-Up)
#include<iostream>
using namespace std;

// index : 특정 거스름돈 액수
// value : 그 거스름돈을 돌려주기 위한 최소 동전 개수
int dp[3001];
int target; // 만들어야 하는 거스름돈 
int N;
int coins[100];

int main() {
    cin >> target >> N;
    for (int i = 0; i < N; i++)
        cin >> coins[i];
    // cout << func(target);

    // Bottom-Up
    // #0. 최소값
    for (int i = 0; i <= target; i++)
        dp[i] = 21e8;
    // #1. 찾을 수 있는 가장 작은 문제에 대한 해답 
    dp[0] = 0;

    // 모든 코인에 대해서 테이블을 채운다
    for (int i = 0; i < N; i++) {
        int now = coins[i];
        for (int j = now; j <= target; j++) {
            // now == 10인 경우 10의 배수 인덱스 마다 1씩증가함
            // dp[10] =1, dp[20] = 2, dp[30] =3; .. dp[150] = 15; 즉 10원15개가답
            // 근데 다음now인 50인 경우 dp[50] = dp[0]+1 이라서 5->1로 바뀌고 dp[150] = 3으로 바뀜
            //그럼 70 + 70 + 1이 경우는?  먼가 10인 경우거를 리뉴얼함
            if (dp[j - now] + 1 < dp[j])
                int s = 0;
                dp[j] = dp[j - now] + 1;
        }
    }
    if (dp[target] >= 21e8)
        cout << "impossible";
    else
        cout << dp[target];
}
