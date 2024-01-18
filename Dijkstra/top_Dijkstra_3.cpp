#include<iostream>
#include<queue>
using namespace std;

pair<int, int> dir;
struct Node {
	int row = dir.first;
	int col = dir.first;
	int cost;
	bool operator<(Node right)const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		if (row > right.row)return true;
		if (row < right.row)return false;
		if (col > right.col)return true;
		if (col < right.col)return false;
		return false;
	}
};

int arr[101][101];
int visited[101][101];
int dist[101][101];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
priority_queue<Node> pq;

int Dijkstra(int h, int w) {
	for (int i = 0; i <= h; i++) {
		for (int j = 0; j <= w; j++) {
			dist[i][j] = 1e9;
		}
	}
	pq.push({0,0,0});
	dist[0][0] = 0;
	while (!pq.empty()) {
		Node now = pq.top(); pq.pop();
		if (visited[now.row][now.col] == 1)continue;
		visited[now.row][now.col] = 1;
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= h || nextCol >= w)continue;
			if (dist[now.row][now.col] + arr[now.row][now.col] >= dist[nextRow][nextCol])continue;
			dist[nextRow][nextCol] = dist[now.row][now.col] + arr[now.row][now.col];
			pq.push({ nextRow,nextCol,dist[nextRow][nextCol] });
		}
	}
	return dist[h - 1][w - 1] + arr[h - 1][w - 1];
}
int main() {
	int h, w;
	cin >> h >> w;
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			cin >> arr[i][j];

	int ans = Dijkstra(h,w);
	//지금알고리즘상 다음거는 arr[now]거 더하므로 
	//마지막거는 next없어서 자기자신못더함 그래서 일부러 더해줌
	cout << ans;
	return 0;
}
