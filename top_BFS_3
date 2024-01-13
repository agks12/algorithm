#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int visited[100001];
vector<int> v[100001];
queue<int> q;

void bfs(int n,int st) {
	q.push(st);
	visited[st] = 1;
	while (!q.empty()) {
		int nowNode = q.front(); q.pop();
		for (int i = 0; i < v[nowNode].size(); i++) {
			if (visited[v[nowNode][i]] == 1)continue;
			visited[v[nowNode][i]] = 1;
			q.push(v[nowNode][i]);
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int from, to;
		cin >> from >> to;
		v[from].push_back(to);
		v[to].push_back(from);
	}
	int st;
	cin >> st;
	bfs(n,st);
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		if (visited[i] == 0)continue;
		if (st == i)continue;
		sum++;
	}
	cout << sum;
	return 0;
}
