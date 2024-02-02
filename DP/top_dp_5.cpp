//내풀이 거의DP아님
#include<iostream>
#include<queue>
using namespace std;

struct node { int row,col; };
int h, w;
int arr[1001][1001];
int DP[1001][1001];
int visited[1001][1001];
int dc[3] = { -1,0,1 };

void dp(int row, int col) {
	int Maxim = -21e8;
	queue<node> q;
	q.push({ row,col });
	while (!q.empty()) {
		int Max = -21e8;
		node now = q.front(); q.pop();
		for (int i = 0; i < 3; i++) {
			int nextrow = now.row + 1;
			int nextcol = now.col + dc[i];
			if (nextrow < 0 || nextcol < 0 || nextrow >= h || nextcol >= w)continue;
			if (arr[nextrow][nextcol] == 0)continue;
			int nowsum = DP[now.row][now.col] + arr[nextrow][nextcol];
			if (DP[nextrow][nextcol] < nowsum)DP[nextrow][nextcol] = nowsum;
			if (nowsum > Max) Max = nowsum;
			if (visited[nextrow][nextcol] == 1)continue;
			visited[nextrow][nextcol] = 1;
			q.push({ nextrow,nextcol });
		}
	}
}
int main() {
	cin >> h >> w;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> arr[i][j];
			DP[i][j] = -21e8;
		}
	}
	DP[0][0] = arr[0][0];
	dp(0, 0);
	int ans = -21e8;
	for (int i = 0; i < w; i++) if (DP[h - 1][i] > ans)ans = DP[h - 1][i];
	cout << ans;
	return 0;
}

//
//강사풀이
//C++ (Top-Down)
#include<iostream>
using namespace std;

int h, w;
int map[100][100];
int memo[100][100];


int getMaxPoint(int dy, int dx)
{
	if (dx < 0 || dx >= w) return -21e8;
	if (dy == h) return 0;
	if (memo[dy][dx] != 0) return memo[dy][dx]; //나는 이거 크기 비교 했는데 이렇게 하면 바로 가능
	if (map[dy][dx] == 0) return -21e8; // 벽인 경우

	//이렇게 하면 내방식에서 큐에 넣을때 visited사용할 필요 없이 할 수 있음 - 기능(시간)은 거의 비숫함 
	int a = getMaxPoint(dy + 1, dx - 1);
	int b = getMaxPoint(dy + 1, dx);
	int c = getMaxPoint(dy + 1, dx + 1);

	int ret = a;
	if (ret < b) ret = b;
	if (ret < c) ret = c;

	//지금위치의 최대값(DP값) = 아래로 갈수 있는 모든 곳중 가장 큰값 + 지금 위치값
	memo[dy][dx] = ret + map[dy][dx];
	return memo[dy][dx]; //이게 답
}

int main()
{
	//freopen("text.txt", "r", stdin);
	
	cin >> h >> w;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			cin >> map[y][x];
		}
	}

	int ret = getMaxPoint(0, 0);
	cout << ret; // 마지막줄에서 최대구한느거 왜안함 왜냐하면 0,0넣었을때 리턴되는건 0,0의 값, 즉 1개만 리턴됨 그것도 제일큰

	return 0;
}
 

//C++ (Bottom-Up)
#include <iostream>
using namespace std;

int MAP[1000][1000];
int dp[1000][1000]; 
int height, width; 
int MIN = -21e8; 

int main() {
	cin >> height >> width;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cin >> MAP[i][j];
			dp[i][j] = MIN; //max값구할때 0이면 -인거 구분못하므로 초기화
		}
	}
	dp[0][0] = MAP[0][0]; 
	for (int i = 1; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (MAP[i][j] == 0) // 벽인 경우 
				continue;
			// 이건 내방식처럼 내 DP값을 전(next)값부터 채우는 형식(next값을 전값으로채우는)  
			if(j-1 < 0) 
				dp[i][j] = max(dp[i - 1][j] + MAP[i][j], dp[i - 1][j + 1] + MAP[i][j]);
			else if (j + 1 >= width)
				dp[i][j] = max(dp[i - 1][j] + MAP[i][j], dp[i - 1][j - 1] + MAP[i][j]);
			//위 2경우는 왼쪽 벽, 오른쪽 벽이므로 경우의 수가 (아래,아래오른쪽),(아래,아래왼쪽) 인 경우이므로 따로 구분함
			// 위 처럼 하면 arr[i][j] < 0 ,arr[i][j](nextcol) > n 은 경우를 방지할 수 있음
			// row는 정해져 있는 특별한 경우라서 고려하지 않음 
				
			// 아래는 벽이 아닌 중간지점들이라 (아래왼쪽,아래,아래오른쪽)3가지 경우 고려함
			else
				dp[i][j] = max(max(dp[i - 1][j] + MAP[i][j], dp[i - 1][j - 1] + MAP[i][j]), dp[i - 1][j + 1] + MAP[i][j]);
		}
	}
	//이건 재귀가 아니므로 내 코드 처럼 마지막거 일일이 검사해서 최대값 찾음
	int ans = -21e8; 
	for (int i = 0; i < width; i++) {
		ans = max(ans, dp[height - 1][i]);
	}
	cout << ans;
}
