#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Pair {
	int row, col;
};

int arr[101][101];
int visited[101][101];
int dr[8] = { -2,-3,-3,-2,2,3,3,2 };
int dc[8] = { -3,-2,2,3,3,2,-2,-3 };
queue<Pair> q;

int ff(int H, int W, int stRow, int stCol, int tarRow, int tarCol) {
	int max = 0;
	q.push({ stRow,stCol });
	visited[stRow][stCol] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 8; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= H || nextCol >= W)continue;
			if (visited[nextRow][nextCol] == 1)continue;
			if (arr[nextRow][nextCol] == 1)continue;
			visited[nextRow][nextCol] = 1;
			arr[nextRow][nextCol] = arr[now.row][now.col] + 1;
			if (arr[nextRow][nextCol] > max)max = arr[nextRow][nextCol];
			if (nextRow == tarRow && nextCol == tarCol)return arr[nextRow][nextCol];
			q.push({ nextRow,nextCol });
		}
	}
	return -1;
}

int main() {
	int H, W,stRow,stCol,tarRow,tarCol,noCnt;
	cin >> H >> W >> stRow >> stCol >> tarRow >> tarCol >> noCnt;
	for (int i = 0; i < noCnt; i++) {
		int x, y;
		cin >> x >> y;
		arr[x][y] = 1;
	}
	int ans = ff(H, W, stRow, stCol, tarRow, tarCol);
	cout << ans;
	return 0;
}
