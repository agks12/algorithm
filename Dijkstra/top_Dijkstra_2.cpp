#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Node {
	int to, cost;
	bool operator<(Node right)const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		if (to > right.to)return true;
		if (to < right.to)return false;
		return false;
	}
};

vector<Node> v[1001];
int visited[1001];
int dist[1001];
priority_queue<Node> pq;

int Dijkstra(int N, int A, int B, int up) {
	for (int i = 0; i <= N; i++) {
		dist[i] = 1e9;
		visited[i] = 0;
	}
	pq.push({ A,0 });
	dist[A] = 0;
	while (!pq.empty()) {
		Node now = pq.top(); pq.pop();
		if (visited[now.to] == 1)continue;
		visited[now.to] = 1;
		for (int i = 0; i < v[now.to].size(); i++) {
			Node next = v[now.to][i];
			if (dist[now.to] + next.cost + up >= dist[next.to])continue;
			dist[next.to] = dist[now.to] + next.cost + up;
			pq.push({ next.to,dist[next.to] });
		}
	}
	return dist[B];
}

int main() {
	int N, M, K, A, B;
	cin >> N >> M >> K >> A >> B;
	for (int i = 0; i < M; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to,cost });
		v[to].push_back({ from,cost });
	}
	int sumCost = 0;
	int ans = Dijkstra(N, A, B, sumCost);
	cout << ans << "\n";
	for (int i = 0; i < K; i++) {
		int up;
		cin >> up;
		sumCost += up;
		int ans = Dijkstra(N,A, B, sumCost);
		cout << ans << "\n";
	}
	return 0;
}
