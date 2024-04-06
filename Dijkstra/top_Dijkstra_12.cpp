#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int n, m, arr[1001][1001], dist[1001][1001],visited[1001][1001];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
struct Pair { 
	int row, col,cost;
	bool operator<(Pair right)const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		return false;
	}
};

int djk() {
	priority_queue<Pair> q;
	q.push({0, 0, arr[0][0]}); // 우선순위 정렬하기 위해 필요한 arr변수
	
	dist[0][0] = arr[0][0];
	while (!q.empty()) {
		Pair now = q.top(); q.pop();
		if (visited[now.row][now.col] == 1)continue;
		visited[now.row][now.col] = 1;
		for (int i = 0; i < 4; i++) {
			int nextrow = now.row + dr[i];
			int nextcol = now.col + dc[i];
			if (nextrow<0 || nextcol<0 || nextrow>n || nextcol>m)continue;
			if (arr[nextrow][nextcol] == -1)continue;
			
			if (dist[now.row][now.col] + arr[nextrow][nextcol] > dist[nextrow][nextcol])continue;
			dist[nextrow][nextcol] = dist[now.row][now.col] + arr[nextrow][nextcol];
			q.push({ nextrow ,nextcol,dist[nextrow][nextcol] });
		}
	}
	return dist[n - 1][m - 1];
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			dist[i][j] = 21e8;
			cin >> arr[i][j];
		}
	}

	int ans = djk();
	if (ans == 21e8)cout<< -1;
	else cout<< ans;

	return 0;
}
