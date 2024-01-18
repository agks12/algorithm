#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Pair {
	int row, col;
};
int arr[101][101];
int visited[101][101];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
queue<Pair> q;

Pair ff(int W,int H,int stCol, int stRow) {
	int max = arr[stRow][stCol];
	int cnt = 1;
	q.push({ stRow,stCol });
	visited[stRow][stCol] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= H || nextCol >= W)continue;
			if (arr[nextRow][nextCol] == 0)continue;
			if (visited[nextRow][nextCol] == 1)continue;
			arr[nextRow][nextCol] = arr[now.row][now.col] + 1;
			visited[nextRow][nextCol] = 1;
			cnt++;
			if (arr[nextRow][nextCol] > max)max = arr[nextRow][nextCol];
			q.push({ nextRow,nextCol });
		}
	}
	return { max,cnt };
}

int main() {
	int W, H, stRow, stCol;
	int allCnt=0;
	cin >> W >> H;
	for (int i = 0; i < H; i++) {
		char a[101];
		cin >> a;
		for (int j = 0; j < W; j++) {
			if (a[j] == '0')continue;
			arr[i][j] = 1;
			allCnt++;
		}
	}
	cin >> stRow >> stCol;
	arr[stCol-1][stRow-1] = 3;

	Pair ans = ff(W,H,stRow-1,stCol-1);

	cout << ans.row <<"\n" << allCnt-ans.col;

	return 0;
}
