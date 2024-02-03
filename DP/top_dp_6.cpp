#include<iostream>
using namespace std;

int n;
int arr[1001][1001];
int DP[1001][1001];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

int dp(int nowrow, int nowcol) {
	
	if (nowrow == n - 1 && nowcol == n - 1)return arr[n-1][n-1];
	if (nowrow < 0 || nowcol < 0 || nowrow >= n || nowcol >= n)return 1e9;
	if (DP[nowrow][nowcol] != 0)return DP[nowrow][nowcol];

	int b = dp(nowrow + dr[1], nowcol + dc[1]);
	int d = dp(nowrow + dr[3], nowcol + dc[3]);
	int ret = min(b, d);
	
	DP[nowrow][nowcol] = ret + arr[nowrow][nowcol];
	return DP[nowrow][nowcol];
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	dp(0, 0);

	int nowrow = 0;
	int nowcol = 0;
	for (int i = 0; i <= n; i++) {
		DP[n][i] = 1e9;
		DP[i][n] = 1e9;
	}

	cout << DP[0][0] << "\n0,0\n";
	for (int i = 0; i < (2 * n - 2); i++) {
		int a = DP[nowrow + 1][nowcol];
		int b = DP[nowrow][nowcol+1];
		if (a < b) {
			nowrow += 1;
			cout << nowrow << "," << nowcol << "\n";
		}
		else{
			nowcol += 1;
			cout << nowrow << "," << nowcol << "\n";
		}
	}

	int k = 0;
	return 0;
}


//C++ (Top-Down)
#include<iostream>
using namespace std;

int h, w;
int map[50][50];
int memo[50][50];
int from[50][50];

enum {
	DOWN = 1,
	RIGHT
};

int getMinPoint(int dy, int dx)
{
	if (dy >= h || dx >= w) return 21e8;
	if (dy == h - 1 && dx == w - 1) return 0;
	if (memo[dy][dx] != 0) return memo[dy][dx];

	int a = getMinPoint(dy + 1, dx);
	int b = getMinPoint(dy, dx + 1);

	int mini = a;
	from[dy][dx] = DOWN;
	if (mini > b) {
		mini = b;
		from[dy][dx] = RIGHT;
	}

	memo[dy][dx] = mini + map[dy][dx];
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

	int ret = getMinPoint(0, 0);
	cout << ret << "\n";

	int y = 0;
	int x = 0;
	while (1) {
		cout << y << "," << x << endl;
		if (y == h - 1 && x == w - 1) break;
		if (from[y][x] == DOWN) y++;
		else x++;		
	}

	return 0;
}
 

//C++ (Bottom-Up)
#include <iostream>
#include <stack>
using namespace std;

struct Node {
	int y;
	int x; 
};

int MAP[1000][1000];
int dp[1000][1000]; 
int N;
int d[1000][1000]; 

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
			dp[i][j] = 21e8;
			d[i][j] = -1;
		}
	}
	dp[0][0] = 0; 
	// right, down
	int dir[][2] = {{0, 1}, {1, 0} }; 
	int xdir[] = { 1, 0 }; 

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == 0 && j == 0)
				continue;
			if (i - 1 < 0) 
				dp[i][j] = dp[i][j - 1] + MAP[i][j];
			else if (j - 1 < 0) 
				dp[i][j] = dp[i - 1][j] + MAP[i][j];
			else 
				dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + MAP[i][j]; 
		}
	}
	
	cout << dp[N - 1][N - 1] << '\n';

	stack<Node>s; 

	int y = N - 1;
	int x = N - 1; 

	while (!(y == 0 && x == 0)) {
		s.push({ y, x });
		int ny1 = y - 1;
		int nx1 = x; 
		int ny2 = y;
		int nx2 = x - 1;

		if (ny1 < 0 || ny1 >= 0 && nx2 >= 0 && dp[ny1][nx1] > dp[ny2][nx2])
		{
			y = ny2;
			x = nx2; 
		}
		else if (nx2 < 0 || ny1 >= 0 && nx2 >= 0 && dp[ny1][nx1] <= dp[ny2][nx2])
		{
			y = ny1;
			x = nx1;
		}
	}
	s.push({ 0, 0 });

	while (!s.empty()) {
		Node now = s.top();
		cout << now.y << "," << now.x << '\n';
		s.pop();
	}
}
