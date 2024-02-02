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
	if (memo[dy][dx] != 0) return memo[dy][dx];
	if (map[dy][dx] == 0) return -21e8;

	int a = getMaxPoint(dy + 1, dx - 1);
	int b = getMaxPoint(dy + 1, dx);
	int c = getMaxPoint(dy + 1, dx + 1);

	int ret = a;
	if (ret < b) ret = b;
	if (ret < c) ret = c;

	memo[dy][dx] = ret + map[dy][dx];
	return memo[dy][dx];
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
	cout << ret;

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
			dp[i][j] = MIN; 
		}
	}
	dp[0][0] = MAP[0][0]; 
	for (int i = 1; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (MAP[i][j] == 0)
				continue;
			if(j-1 < 0)
				dp[i][j] = max(dp[i - 1][j] + MAP[i][j], dp[i - 1][j + 1] + MAP[i][j]);
			else if (j + 1 >= width)
				dp[i][j] = max(dp[i - 1][j] + MAP[i][j], dp[i - 1][j - 1] + MAP[i][j]);
			else
				dp[i][j] = max(max(dp[i - 1][j] + MAP[i][j], dp[i - 1][j - 1] + MAP[i][j]), dp[i - 1][j + 1] + MAP[i][j]);
		}
	}

	int ans = -21e8; 
	for (int i = 0; i < width; i++) {
		ans = max(ans, dp[height - 1][i]);
	}
	cout << ans;
}
