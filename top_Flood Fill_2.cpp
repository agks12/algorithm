#include<iostream>
#include<queue>
#include<queue>
using namespace std;

struct Pair {
	int row, col;
};

int visited[101][101];
int arr[101][101];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
queue<Pair> q;

int ff(int n, int m, int row1, int col1, int row2, int col2) {
	int max =-1;
	q.push({ row1,col1 });
	q.push({ row2,col2 });
	visited[row1][col1] = 1;
	visited[row2][col2] = 1;
	arr[row1][col1] = 1;
	arr[row2][col2] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >= m)continue;
			if (visited[nextRow][nextCol] == 1)continue;
			visited[nextRow][nextCol] = 1;
			arr[nextRow][nextCol] = arr[now.row][now.col] + 1;
			if (arr[nextRow][nextCol] > max)max = arr[nextRow][nextCol];
			q.push({ nextRow,nextCol });
		}
	}
	return max;
}

int main() {
	int n, m, row1,col1,row2,col2;
	cin >> n >> m >> row1 >> col1 >> row2 >> col2;
	int ans = ff(n,m,row1, col1, row2, col2);
	cout << ans;
	return 0;
}
