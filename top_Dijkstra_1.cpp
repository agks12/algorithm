#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct node {
	int to, cost;
	bool operator<(node right)const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		if (to > right.to)return true;
		if (to < right.to)return false;
		return false;
	}
};

int visited[20001];
int dist[20001];
vector<node> v[20001];
priority_queue<node> q;

void Dijkstra(int N) {
	for (int i = 0; i <= N; i++)dist[i] = 1e9;
	q.push({ 0,0 });
	dist[0] = 0;
	while (!q.empty()) {
		node now = q.top(); q.pop();
		if (visited[now.to] == 1)continue;
		visited[now.to] = 1;
		for (int i = 0; i < v[now.to].size(); i++) {
			node next = v[now.to][i];
			if (dist[now.to] + next.cost >= dist[next.to])continue;
			dist[next.to] = dist[now.to] + next.cost;
			q.push({ next.to,dist[next.to]});
		}
	}
}

int main() {
	int N,T;
	cin >> N >> T;
	for (int i = 0; i < T; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to,cost });
	}

	Dijkstra(N);

	if (dist[N - 1] == 1e9)cout << "impossible";
	else cout << dist[N - 1];

	return 0;
}
