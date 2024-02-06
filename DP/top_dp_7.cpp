//Bottom-Up 
#include<iostream>
#include<vector>

using namespace std;
int N, M, H;
vector<int>v[51];
long memo[51][1001];


int main() {
	//freopen("10.in", "r", stdin);
	//freopen("10.out", "w", stdout);
	cin >> N >> M >> H;
	for (int i = 1; i < N+1; i++) {
		for (int j = 0; j < M; j++) {
			int now;
			cin >> now;
			if (now != -1) {
				v[i].push_back(now);
			}
		}
	}
	for (int i = 0; i <= N; i++)memo[i][0] = 1;
	for (int i = 1; i < N+1; i++) {
		for (int j = 1; j < H + 1; j++) {
			for (int k = 0; k < v[i].size(); k++) {
				int block = v[i][k];
				if (j - block >= 0) {
					memo[i][j] = memo[i][j] + memo[i - 1][j - block];
				}
				
			}
			memo[i][j] = memo[i][j] + memo[i - 1][j];
		}
	}

	cout << memo[N][H];
	return 0;
}
 

//Top-Down
#include<iostream>
#include<vector>
using namespace std;

int n, m, h;
int arr[51][11];
long dp[50][1001];//수 21억넘어가서 long형

long func(int idx, int height) {
	if (height == 0) return 1;
	if (height < 0 || idx >= n) return 0;
	if (dp[idx][height] != 0) return dp[idx][height];

	// 나둘 수도 있고 안 나둘 수도 있음
	// 전체 경우 하려면 x인경우,1번벽돌나두는경우,2번벽돌나두는경우,3번벽돌나두는경우...
	// 이렇게 되는데 n번벽돌 두는거는 for루프로 한번에 할 수 있는데
	// x인경우는 for로 못해서 그냥 밖에 하나 나두는 거
	//   1번경우   2번경우
	// 1 - x    ,  2길이
	// 2 - 3길이,  2길이
	// 3 - 2길이,    x
	// .. 이렇게 1번경우 끝까지 가서 리턴되면 cnt에 1번이 x인경우 나올수 있는 경우의 수 모두 누적
	//    즉 1번이 x일때 n번이 계속 하위경우로 나눠지는데 이때 idx일때 높이height를 저장해놓으면 
	//   이걸 활용(if (dp[idx][height] != 0) return dp[idx][height];)해서 시간 줄임
	//    위 과정을 1번 기준 m번 하면 최종 결과 dp[idx][height] = dp[0][h]
	long cnt = 0;
	cnt += func(idx + 1, height);

	for (int i = 0; i < m; i++) {
		if (arr[idx][i] == -1)continue;
		cnt += func(idx + 1, height - arr[idx][i]);
	}

	//   이걸 활용(if (dp[idx][height] != 0) return dp[idx][height];)해서 시간 줄임
	// 계산 돌다가 현재 사람이 이정도 높이 벽돌 받은 경우는 이 개수만큼 있음
	dp[idx][height] = cnt;
	return dp[idx][height];
}

int main() {
	cin >> n >> m >> h;//50 -10 -1000 최대값
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> arr[i][j];
	cout<<func(0, h);
	return 0;
}
