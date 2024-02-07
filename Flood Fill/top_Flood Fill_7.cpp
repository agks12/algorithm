#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Pair { int row, col; };
int n, m, cnt, arr[151][151];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

void floodFill(int row, int col) {
	queue<Pair> q;
	q.push({row, col});
	arr[row][col] = 0;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextrow = now.row + dr[i];
			int nextcol = now.col + dc[i];
			if (nextrow < 0 || nextcol < 0 || nextrow >= n || nextcol >= m)continue;
			if (arr[nextrow][nextcol] == 0)continue;
			arr[nextrow][nextcol] = 0;
			q.push({ nextrow,nextcol });
		}
	}
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> arr[i][j];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == 0 || arr[i][j]==1)continue;
			cnt++;
			floodFill(i, j);
		}
	}
	cout << cnt;
	return 0;
}
