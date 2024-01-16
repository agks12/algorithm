#include<iostream>
#include<vector>
#include<queue>
using namespace std;
//MST(Minimum Spanning Tree) -> ST는 간선 최소(n-1)개인 경우
// MST는 간선 최소 + 최소 가중치

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

int visited[10001];
vector<Node> v[10001];
priority_queue<Node> pq;

int prim(int n) {
	int sum = 0;
	pq.push({ 1,0 });
	while (!pq.empty()) {
		Node now = pq.top(); pq.pop();
		if (visited[now.to] == 1)continue;
		visited[now.to] = 1;
		sum += now.cost;//가중치 합구하기
		for (int i = 0; i < v[now.to].size(); i++) {
			Node next = v[now.to][i];
			pq.push(next);//여기에서 최소값 구분하는(다익스트라같은
			//거 필요없음 어차피 모든 노드있는 간선(N-1)필요하므로 모든것에서 최소로가나봄
		}
	}
	return sum;
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		v[a].push_back({ b,c });
		v[b].push_back({ a,c });
	}

	int ans = prim(n);
	cout << ans;

	return 0;
}
