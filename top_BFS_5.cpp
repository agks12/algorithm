#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int visited[101];
vector<int> v[101];
queue<int> q;

void bfs(int a) {
	q.push(a);
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (int i = 0; i < v[now].size(); i++) {
			int next = v[now][i];
			if (visited[next] == 1)continue;
			visited[next] = 1;
			q.push(next);
		}
	}
}

int main() {
	int n, t;
	cin >> n >> t;
	for (int i = 0; i < t; i++) {
		int from, to;
		cin >> from >> to;
		v[from].push_back(to);
		v[to].push_back(from);
	}
	int a, b;
	cin >> a >> b;
	bfs(a);
	if (visited[b] == 1)cout << "YES";
	else cout << "NO";
	return 0;
}
