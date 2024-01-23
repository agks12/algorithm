#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct node {
	int row, col, cost;
	bool operator<(node right)const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		if (row > right.row)return true;
		if (row < right.row)return false;
		if (col > right.col)return true;
		if (col < right.col)return false;
		return false;
	}
};
int arr[1001][1001];
int dist[1001][1001];
int visited[1001][1001];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,1,-1 };
priority_queue<node> pq;

int dijkstar(int N, int tx, int ty) {
	int max = 0;
	pq.push({ tx,ty,0 });
	dist[tx][ty] = arr[tx][ty];
	while (!pq.empty()) {
		node now = pq.top(); pq.pop();
		if (visited[now.row][now.col] == 1)continue;
		visited[now.row][now.col] = 1;
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= N || nextCol >= N)continue;
			if (arr[nextRow][nextCol] == -1)continue;
			if (visited[nextRow][nextCol] == 1)continue;
			if (dist[now.row][now.col] + arr[nextRow][nextCol] > dist[nextRow][nextCol])continue;
			dist[nextRow][nextCol] = dist[now.row][now.col] + arr[nextRow][nextCol];
			if (dist[nextRow][nextCol] > max)max = dist[nextRow][nextCol];
			pq.push({ nextRow,nextCol,dist[nextRow][nextCol] });
		}
	}
	return max;
}
int main() {
	int tarX, tarY; cin >> tarX >> tarY;
	int N; cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			dist[i][j] = 1e9;
		}
	}
	int ans = dijkstar(N,tarX,tarY);
	cout << ans;
	return 0;
}
