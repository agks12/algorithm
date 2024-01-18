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
//크루스칼
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Node {
	int from, to, cost;
	bool operator<(Node right)const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		if (to > right.to)return true;
		if (to < right.to)return false;
		if (from > right.from)return true;
		if (from < right.from)return false;
		return false;
	}
};

//MST => 가중치기준으로 sort해서 작은거 부터 연결하면 N-1개 연결되었을때가 정답 자동으로 최소로 연결된거
// 이게 kruskal 방식 
priority_queue<Node> pq;
int parent[10001];

int Find(int num) {
	if (num == parent[num])return num;
	return Find(parent[num]);
}
//Union 간략화 함
int kuruskal(int n) {
	for (int i = 0; i <= n; i++)parent[i] = i;
	int sum = 0;
	while (!pq.empty()) {
		Node now = pq.top(); pq.pop();
		int rootA = Find(now.from);
		int rootB = Find(now.to);
		if (rootA == rootB)continue;
		sum += now.cost;
		parent[rootA] = rootB;
	}
	return sum;
}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		pq.push({ a,b,c });
	}
	int ans = kuruskal(n);
	cout << ans;

	return 0;
}
