#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Pair {int row, col;};
int arr[100][100];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,1,-1 };
void floodfill(int n, int m, int row,int col) {
	queue<Pair> q;
	q.push({ row,col });
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		arr[now.row][now.col] = 0; //이거하면 visited필요x
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= n || nextCol >= m)continue;
			if (arr[nextRow][nextCol] == 0)continue;
			q.push({ nextRow,nextCol });
		}
	}
}
int main() {
	int n, m; cin >> n >> m;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == 1) {
				floodfill(n, m, i, j);
				cnt++;
			}
		}
	}
	cout << cnt;
	return 0;
}
