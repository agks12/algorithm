#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Pair { int row, col; };
int n, m; 
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
char arr[21][21];
int visited[21][21];
Pair st;
int floodfill() {
	int d_dis = 0;
	int s_dis = 0;
	queue<Pair> q;
	q.push(st);
	visited[st.row][st.col] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nextrow = now.row + dr[i];
			int nextcol = now.col + dc[i];
			if (nextrow < 0 || nextcol < 0 || nextrow >= n || nextcol >= m)continue;
			if (visited[nextrow][nextcol] >= 1)continue;
			if (arr[nextrow][nextcol] == 'x')continue;
			if (arr[nextrow][nextcol] == 'D')d_dis = visited[now.row][now.col];
			if (arr[nextrow][nextcol] == 'S')s_dis = visited[now.row][now.col];
			visited[nextrow][nextcol] = visited[now.row][now.col]+1;
			q.push({ nextrow,nextcol });
		}
	}
	return d_dis + s_dis;
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 'C') {
				st.row = i; st.col = j;
			}
		}
	}
	cout << floodfill();
	return 0;
}
