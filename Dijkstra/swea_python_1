#include<iostream>
#include<vector>
#include<queue>
using namespace std;


struct Pair{ 
	int row, col, cost;
	bool operator<(Pair right) const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		return false;
	}
};
int tc, n, arr[14][14], visited[14][14], dist[14][14];
int dr[2] = { 1,0 };
int dc[2] = { 0,1 };
static void input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			visited[i][j] = 0;
			dist[i][j] = 21e8;
		}
	}
}
static int djk() {
	priority_queue<Pair> pq;
	pq.push({ 0,0,0 });
	dist[0][0] = arr[0][0];
	while (!pq.empty()) {
		Pair now = pq.top(); pq.pop();
		if (visited[now.row][now.col] == 1)continue;
		visited[now.row][now.col] = 1;
		for (int i = 0; i < 2; i++) {
			int nextrow = now.row + dr[i];
			int nextcol = now.col + dc[i];
			if (nextrow < 0 || nextcol < 0 || nextrow >= n || nextcol >= n)continue;
			if (dist[nextrow][nextcol] < dist[now.row][now.col] + arr[nextrow][nextcol])continue;
			dist[nextrow][nextcol] = dist[now.row][now.col] + arr[nextrow][nextcol];
			pq.push({ nextrow,nextcol,dist[nextrow][nextcol] });
		}
	}
	return dist[n - 1][n - 1];
}
int main() {
	cin >> tc;
	for (int i = 1; i <= tc; i++) {
		input();
		int ans = djk();
		cout <<"#"<<i<<" "<< ans<<"\n";
	}
	return 0;
}
