//prim
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct node {
	int to, cost;
	bool operator<(node right)const {
		if (cost > right.cost) return true;
		if (cost < right.cost) return false;
		if (to > right.to) return true;
		if (to < right.to) return false;
		return false;
	}
};
char MW[1001];
int dist[1001];
int visited[1001];
vector<node> v[1001];
int MST(int n) {
	priority_queue<node> pq;
	int cntNode = 0;
	int sum = 0;
	pq.push({ 1,0 });
	dist[1] = 0;
	while (!pq.empty()) {
		node now = pq.top(); pq.pop();
		if (visited[now.to] == 1)continue;//시작 따지면 from
		visited[now.to] = 1;
		cntNode++;
		sum += now.cost;
		for (int i = 0; i < v[now.to].size(); i++) {
			node next = v[now.to][i];
			if (visited[next.to] == 1)continue;
			if (MW[now.to] == MW[next.to])continue;
			//if (dist[now.to] + next.cost > dist[next.to])continue;
			//dist[next.to] = dist[now.to] + next.cost;
			//위에 주석 하면 그냥 다이스트라
			pq.push({ next });
		}
	}
	if (cntNode == n) return  sum;
	else return -1;
}
int main() {
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> MW[i];
		dist[i] = 1e9;
	}
	for (int i = 0; i < m; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		v[from].push_back({ to,cost });
		v[to].push_back({ from,cost });
	}
	int ans = MST(n);
	cout << ans;
	
	return 0;
}


// kruskal
#include<iostream>
#include<queue>
using namespace std;

struct node {
	int from, to, cost;
	bool operator<(node right)const {
		if (cost > right.cost) return true;
		if (cost < right.cost) return false;
		if (from > right.from) return true;
		if (from < right.from) return false;
		if (to > right.to) return true;
		if (to < right.to) return false;
		return false;
	}
};

char MW[1001];
int parent[1001];
priority_queue<node> pq;
int Find(int num) {
	if (parent[num] == num)return num;
	return parent[num] = Find(parent[num]);
}
void Union(int a, int b) {
	if (a == b)return;
	parent[a] = b;
}
int MST(int n) {
	int sum = 0;
	int cntNode = 0;
	while (!pq.empty()) {
		node now = pq.top(); pq.pop();
		int rootA = Find(now.from);
		int rootB = Find(now.to);
		if (rootA == rootB)continue;
		if (MW[now.from] == MW[now.to])continue;
		parent[rootA] = rootB; //간단해서 유니온 함수 안쓰고 함
		sum += now.cost;
		cntNode++;
	}
	if (cntNode == n - 1)return sum; //유니온 n-1번하면 n개 연결됨
	else return -1;
}
int main() {
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		parent[i] = i;
		cin >> MW[i];
	}
	for (int i = 0; i < m; i++) {
		int from, to, cost;
		cin >> from >> to >> cost;
		pq.push({ from,to,cost });
	}
	int ans = MST(n);
	cout << ans;
	return 0;
}
