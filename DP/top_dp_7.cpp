//Bottom-Up 
#include<iostream>
#include<vector>
using namespace std;

int n, m, h;
vector<int> v[51];
long dp[51][1001];
int main() {
	dp[0][0] = 1;// 초기화
	cin >> n >> m >> h;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = 1;// 초기화
		for (int j = 0; j < m; j++) {
			int now; cin >> now;
			if (now == -1)continue;
			v[i].push_back(now);
		}
	}

	for (int i = 1; i <= n; i++) {//사람수
		for (int j = 1; j <= h; j++) { // 높이 수(제한)
			for (int k = 0; k < v[i].size(); k++) { // 벽돌 개수
				int blockSize = v[i][k]; // 지금 꺼낸 벽돌 길이
				if (blockSize > j)continue; // 지금 꺼낸 벽돌 길이가 쌓인 벽돌 보다 킬면 
				// 지금 내가 벽돌 높이 j만큼 쌓을 경우는 내 전사람이 높이 j-내벽돌길이
				// 만큼 쌓은 경우 + 1 됨(초기화 할때 [i][0]인덱스만 1했으므로 처음 j-blockSize가 0일때 
				// +1되고 그 다음부터는 처음 쌓은 벽돌(예 j=3)인덱스 만큼 값이 나올때 추가됨
				// 즉 예를들어dp[i][j0~h]나열하면 1 0 0 0 2 0 3 0 0 0 0 4 . . . ..가면서 벽돌 높이h되면 최종 경우의수 나옴   
				// -> 누적되서 다음 번쨰 벽돌높이 할때는 + 2 되고하는듯
				// 0부터 시작해서 가능한듯 
				dp[i][j] = dp[i][j] + dp[i - 1][j - blockSize];
			}
			dp[i][j] = dp[i][j] + dp[i - 1][j]; // 이건 그냥 dp가져다쓰는건가 top다운에서 dp!=0인경우 반환하는 것처럼
			// 1번 부터 시작해서 이것도 가능한듯 2번은 1번의 경우 가져다 쓰는듯
			// 그래서 답이 n번쨰 애가 답인듯
		}
	}
	cout << dp[n][h];
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
