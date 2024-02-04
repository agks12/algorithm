#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int n,m,nogo;
int visited[11];
vector<int> v[11];
int bfs() {
	queue<int> q;
	q.push(1);
	visited[1] = 1;
	while (!q.empty()) {
		int now = q.front(); q.pop();
		if (now == nogo)continue;
		if (now == n)return visited[n]-1;
		for (int i = 0; i < v[now].size(); i++) {
			int next = v[now][i];
			if (visited[next] >= 1)continue;
			visited[next] = visited[now]+1;
			q.push(next);
		}
	}
	return -1;
}
int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int from,to;
		cin >> from >> to;
		v[from].push_back(to);
		v[to].push_back(from);
	}
	cin >> nogo;
	int ans = bfs();
	cout << ans;
	return 0;
}
