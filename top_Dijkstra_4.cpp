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
int dist2[1001];
priority_queue<Node> pq;

void Dijkstar(int N, int st) {
	for (int i = 1; i <= N; i++) {
		dist[i] = 1e9;
		visited[i] = 0;
	}
	pq.push({ st,0 });
	dist[st] = 0;
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
}

int Dijkstar2(int N, int st,int P) {
	for (int i = 1; i <= N; i++) {
		dist2[i] = 1e9;
		visited[i] = 0;
	}
	pq.push({ st,0 });
	dist2[st] = 0;
	while (!pq.empty()) {
		Node now = pq.top(); pq.pop();
		if (visited[now.to] == 1)continue;
		visited[now.to] = 1;
		for (int i = 0; i < v[now.to].size(); i++) {
			Node next = v[now.to][i];
			if (dist2[now.to] + next.cost >= dist2[next.to])continue;
			dist2[next.to] = dist2[now.to] + next.cost;
			pq.push({ next.to,dist2[next.to] });
		}
	}
	return dist2[P];
}

int main() {
	int N, M, P;
	cin >> N >> M >> P;
	for (int i = 0; i < M; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to,cost });
	}

	Dijkstar(N, P);
	//p에서 한번해서 dist값
	// + 모든곳에서 dist[p]
	int max = 0;
	int maxIndex = 0;
	for (int i = 1; i <= N; i++) {
		if (i == P)continue;
		int ans = Dijkstar2(N, i,P);
		if (max < dist[i] + ans) {
			max = dist[i] + ans;
			maxIndex = i;
		}
	}
	
	cout << max;
	return 0;
}
///함수 1개로 하는데 돌리는건 2N번
//#include <iostream>
//#include <queue>
//using namespace std;
//
//int n, m, p;
//
//struct Edge {
//	int num, cost;
//};
//
//bool operator < (Edge a, Edge b) {
//	return a.cost > b.cost;
//}
//
//vector<Edge>v[1001];
//
//int dijkstra(int start, int dest) {
//	priority_queue<Edge>pq;
//	pq.push({ start, 0 });
//	int dist[1001];
//	for (int i = 0; i <= n; i++)
//		dist[i] = 2134567890;
//	dist[start] = 0;
//	while (!pq.empty()) {
//		Edge now = pq.top();
//		pq.pop();
//		for (int i = 0; i < v[now.num].size(); i++) {
//			Edge next = v[now.num][i];
//			if (dist[next.num] <= dist[now.num] + next.cost)
//				continue;
//			dist[next.num] = dist[now.num] + next.cost;
//			pq.push({ next.num, dist[next.num] });
//		}
//	}
//	return dist[dest];
//}
//
//int main() {
//	cin >> n >> m >> p;
//	for (int i = 0; i < m; i++) {
//		int from, to, cost;
//		cin >> from >> to >> cost;
//		v[from].push_back({ to, cost });
//	}
//	int ans = -2134567890;
//	for (int i = 1; i <= n; i++) {
//		int a = dijkstra(i, p);
//		int b = dijkstra(p, i);
//		if (a + b > ans)
//			ans = a + b;
//	}
//	cout << ans;
//}
