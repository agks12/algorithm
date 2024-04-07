#include<iostream>
using namespace std;

int n, arr[1001][1001], DP[1001][1001], trace[1001][1001];
//최단거리이면 무조건 아래,앞만 가능한데?
//int dr[4] = { -1,1,0,0 };
//int dc[4] = { 0,0,-1,1 };
int dr[2] = { 0,1 };
int dc[2] = { 1,0 };
int dp(int row, int col) {

	if (row == n - 1 && col == n - 1)return 0;
	if (col < 0 || col >= n || row < 0 || row >= n)return 21e8;
	if (DP[row][col] != 0)return DP[row][col];

	int Max = 21e8;

	for (int i = 0; i < 2; i++) {
		int nextrow = row + dr[i];
		int nextcol = col + dc[i];
		int ret = dp(nextrow, nextcol);
		if (ret < Max) {
			trace[row][col] = i;// 지금위치에서 최소 경로로 갈려면 아래인지 위인지 저장
			Max = ret;
		}
	}

	DP[row][col] = Max + arr[row][col];
	return DP[row][col];
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}
	int ans = dp(0, 0); // 자동으로 n-1.n-1의 값을 반환?
	cout << ans<<"\n";

	//경로 추척은 DP배열에서 최소값 따라가면 되는듯
	// 강사풀이는 DP됬던 애들을 다 저장해서 다 출력하는거 같은데 왜돼는거지?
	int x = 0;
	int y = 0;
	while (!(x == n-1 && y == n-1)) {
		cout << x << "," << y << "\n";
		int nowdir = trace[x][y];
		// 이러면 지금 위치에서 아래(1)인지 위(0)인지 알 수 있음 
		//어차피 여기 저장되는거는 0,0부터 시작하는데
		//알아서 DP는 최소값들을 따라감
		// DP배열에서 직접 아래,위 최소값 구분해서 가도 돼는데
		// 이게 더 좋음
		x += dr[nowdir]; // nowdir 0이면 x 즉row1만큼증가
		y += dc[nowdir];// nowdor 1이면 y 즉 col 1만큼 증가
	}
	cout << n - 1 << "," << n - 1;
	return 0;
}
