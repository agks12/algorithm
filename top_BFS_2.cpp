#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int visited[11];
vector<pair<int, int>> v[11];
queue<pair<int,int>> q;

void bfs(int n,int k) {
	q.push({ 0,0 });
	while (!q.empty()) {
		pair<int,int> nowNode = q.front(); q.pop();
		visited[nowNode.first] = 1;
		for (int i = 0; i < v[nowNode.first].size(); i++) {
			pair<int, int> nextNode = v[nowNode.first][i];
			nextNode.second += nowNode.second;
			v[nowNode.first][i].second = nextNode.second;
			if (visited[nextNode.first] == 1)continue;
			if (nextNode.second> k)continue;
			q.push(nextNode);
		}
	}
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to,cost });
	}
	
	bfs(n,k);
	//오름차순출력해야하는데 정렬필요없이 순차적으로 방문한거 출력
	for (int i = 1; i < n; i++) {
		if (visited[i] == 0)continue;
		cout << i << " ";
	}
	return 0;
}
