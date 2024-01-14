#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Pair {
	int row, col;
};

int arr[101][101];
int visited[101][101];
int dr[8] = { -1,-2,-2,-1,1,2,2,1 };
int dc[8] = { -2,-1,1,2,2,1,-1,-2 };
queue<Pair> q;

int ff(int H, int W, int stRow, int stCol, int TRow, int TCol) {
	q.push({ stRow,stCol });
	visited[stRow][stCol] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 8; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= H || nextCol >= W)continue;
			if (visited[nextRow][nextCol] == 1)continue;
			arr[nextRow][nextCol] = arr[now.row][now.col] + 1;
			if (nextRow == TRow && nextCol == TCol)return arr[nextRow][nextCol];
			visited[nextRow][nextCol] = 1;
			q.push({ nextRow,nextCol });
		}
	}
}

int main() {
	int H, W,stRow,stCol,TRow,TCol;
	cin >> H >> W >>stRow>>stCol>>TRow>>TCol;
	int ans = ff(H, W, stRow, stCol, TRow, TCol);
	cout << ans;
	return 0;
}
