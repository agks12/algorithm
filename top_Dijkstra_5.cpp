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

vector<Node> v[5001];
int visited[5001];
int dist[5001];
priority_queue<Node> pq;

pair<int, int> Dijkstar(int N, int P) {
	for (int i = 1; i <= N; i++) {
		dist[i] = 1e9;
		visited[i] = 0;
	}
	pq.push({ P,0 });
	dist[P] = 0;
	while (!pq.empty()) {
		Node now = pq.top(); pq.pop();
		if (visited[now.to] == 1)continue;
		visited[now.to] = 1;
		for (int i = 0; i < v[now.to].size(); i++) {
			Node next = v[now.to][i];
			if (dist[now.to] + next.cost >= dist[next.to])continue;
			dist[next.to] = dist[now.to] + next.cost;
			pq.push({ next.to,dist[next.to] });
		}
	}
	if (dist[1] == 1e9)return {- 1, dist[N]};
	else return  { dist[1], dist[N] };
}
int main() {
	int N, M, P;
	cin >> N >> M >> P;
	for (int i = 0; i < M; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to,cost });
		v[to].push_back({ from,cost });
	}

	pair<int,int> ansPs = Dijkstar(N, P);
	pair<int,int> ansN = Dijkstar(N, 1);
	if (ansPs.first == -1)cout << "SORRY";
	else if (ansPs.first + ansPs.second > ansN.second)cout << "SORRY";
	else cout << "OKAY";

	return 0;
}
// 구 풀이
//같으면 출력
//#include<iostream>
//#include<vector>
//#include<queue>
//using namespace std;
//
//int V, M, P;
//struct node {
//	int to;
//	int cost;
//	bool operator<(node right) const {
//		if (cost > right.cost)return true;
//		if (cost < right.cost)return false;
//		if (to > right.to)return true;
//		if (to < right.to)return false;
//		return false;
//	}
//};
//
//vector<node> v[5001];
//int dist[10001];
//int visited[10001];
//
//int dkj(int start, int end) {
//	for (int i = 0; i <= V; i++) {
//		dist[i] = 10000000;
//		visited[i] = 0;
//	}
//	dist[start] = 0;
//	priority_queue<node> q;
//	q.push({ start,0 });
//	while (!q.empty()) {
//		node now = q.top(); q.pop();
//		if (visited[now.to] > 0)continue;
//		visited[now.to] = 1;
//		for (int i = 0; i < v[now.to].size(); i++) {
//			node next = v[now.to][i];
//			int nextnode = next.to;
//			int nextcost = next.cost;
//
//			if (dist[nextnode] < nextcost + dist[now.to])continue;
//			dist[nextnode] = nextcost + dist[now.to];
//			q.push({ nextnode,dist[nextnode] });
//		}
//	}
//
//	return dist[end];
//}
//
//int main()
//{
//	cin >> V >> M >> P;
//	for (int i = 0; i < M; i++) {
//		int from, to, cost;
//		cin >> from >> to >> cost;
//		v[from].push_back({ to,cost });
//		v[to].push_back({ from,cost });
//	}
//
//	if (dkj(1, V) == dkj(1, P) + dkj(P, V))cout << "OKAY";
//	else cout << "SORRY";
//
//	return 0;
//}
