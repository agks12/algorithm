#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct cmd {
	int to;
	int cost;
};

int visited[100001];
vector<cmd> v[100001];
queue<cmd> q;

int bfs(int k) {
	int sum = 0;
	q.push({ 1,0 });
	while (!q.empty()) {
		cmd now = q.front(); q.pop();
		for (int i = 0; i < v[now.to].size(); i++) {
			cmd next = v[now.to][i];
			//now_cost + next_cost해야 경로갈때마다 쌓임
			next.cost += now.cost;
			if (visited[next.to] == 1)continue;
			if (next.cost > k)continue;
			sum++;
			q.push(next);
		}
	}
	return sum;
}

int main() {
	int N, M, K;
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to,cost });
	}

	int ans = bfs(K);
	cout << ans;

	return 0;
}
