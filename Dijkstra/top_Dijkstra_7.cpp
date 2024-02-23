#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Node{ 
	int row, col, cost;
	bool operator<(Node right) const{
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		return false;
	}
};
int n, a, b;
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };
char arr[31][31];
int visited[31][31];
int dist[31][31];

// 가장많이 소모되는 지점 -> 무조건 대각선?  에서 가장 적은 소모 경로 
int djistra(int strow, int stcol){//}, int tarrow, int tarcol) {
	int max = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = 0;
			dist[i][j] = 21e8;
		}
	}
	priority_queue<Node> q;
	q.push({ strow,stcol,0 });
	dist[strow][stcol] = 0;
	while (!q.empty()) {
		Node now = q.top(); q.pop();
		if (visited[now.row][now.col] == 1)continue;
		if (max < now.cost)max = now.cost;
		visited[now.row][now.col] = 1;
		for (int i = 0; i < 4; i++) {
			int nextrow = now.row + dr[i];
			int nextcol = now.col + dc[i];
			int nowcost = 0;
			if (nextrow < 0 || nextcol < 0 || nextrow >= n || nextcol >= n)continue;
			if (arr[now.row][now.col] != arr[nextrow][nextcol])nowcost = b;
			if (arr[now.row][now.col] == arr[nextrow][nextcol])nowcost = a;
			if (dist[nextrow][nextcol] < dist[now.row][now.col] + nowcost)continue;
			dist[nextrow][nextcol] = dist[now.row][now.col] + nowcost;
			//if (max < dist[nextrow][nextcol])max = dist[nextrow][nextcol];
			q.push({ nextrow,nextcol,dist[nextrow][nextcol] });
		}
	}
	return max;
}

int main() {
	cin >> n >> a >> b;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	int max = -2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int ans = djistra(i, j);
			if (max < ans)max = ans;
		}
	}

	cout << max;
	return 0;
}
