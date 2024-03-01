#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

struct Node {
	int from,to, cost;
	bool operator<(Node right)const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		return false;
	}
};
int tc, n, arr[11][11], dist[11][11], visited[11], parent[11];
int sum;
int Min = 1e9;
vector<Node> v[11];
//priority_queue<Node> pq;

static int Find(int num) {
	if (num == parent[num])return num;
	parent[num] = Find(parent[num]);
	return parent[num];
}

static void Union(int a, int b) {
	int rootA = Find(a);
	int rootB = Find(b);
	if (rootA == rootB)return;
	parent[rootA] = rootB;
}

static void input() {
	cin >> n;
	Min = 1e9;
	for (int i = 0; i < n; i++) {
		parent[i] = i;
		visited[i] = 0;
		v[i].clear();
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			dist[i][j] = 21e8;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//pq.push({ j,arr[i][j] });
			if (i == j)continue;
			v[i].push_back({ i, j,arr[i][j] });
		}
	}
}

static void sol(int now, int level) {

	if (now == 0 && level == n) {
		if (sum < Min)Min = sum;
		return;
	}
	if (level > n)return;

	for (int i = 0; i < v[now].size(); i++) {
		int next = v[now][i].to;
		if (visited[next] == 1) continue;
		visited[next] = 1;
		if (level == 0 && next == 0)visited[next] = 0;
		sum += arr[now][next];
		sol(next,level+1);
		sum -= arr[now][next];
		visited[next] = 0;
	}
}
//시작에서 모든곳
//[1][2] [1][3]
//[2][1] [2][3]
//[3][1] [3][2]
//static void sol() {
//	priority_queue<Node> pq;
//	pq.push({ 0,0,arr[0][0] });
//	//dist[0] = arr[0][0];
//	int flag = 0;
//	dist[0][0] = arr[0][0];
//	int preNode = 0;
//	while (!pq.empty()) {
//		Node now = pq.top(); pq.pop();
//		if (visited[now.from][now.to] == 1)continue;
//		visited[now.from][now.to] = 1;
//		//if (visited[now.to] == 1)continue;
//		if (now.to == 0 && flag == 1)visited[now.from][now.to] = 1;
//		if (now.to == 0 && flag==0)flag = 1;
//		//if(now.to!= 0)visited[now.to] = 1;
//		for (int i = 0; i < v[now.to].size(); i++) {
//			Node nextNode = v[now.to][i];
//			if (dist[now.to][nextNode.to] < dist[now.from][now.to] + arr[now.to][nextNode.to])continue;
//			dist[now.to][nextNode.to] = dist[now.from][now.to] + arr[now.to][nextNode.to];
//			pq.push({ now.to, nextNode.to ,dist[now.to][nextNode.to] });
//		}
//		preNode = now.to;
//	}
//}

//static bool compare(const Node a, const Node b)
//{
//	return a.cost < b.cost; // first 값이 같지 않다면 더 큰 값이 뒤로 가게 해라!
//}

//최소값으로 이동하면 안됨 MST아님
//static int sol() {
//	int stNode = 0;
//	int cnt = 0;
//	int sum = 0;
//	while(1) {
//		sort(v[stNode].begin(), v[stNode].end(), compare);
//		if (visited[v[stNode][0].to] == 1)continue;
//		//Union(stNode, v[stNode][0].to);
//		visited[v[stNode][0].to]=1;
//		sum += v[stNode][0].cost;
//		stNode = v[stNode][0].to;
//		cnt++;
//		if (cnt == n)break;
//	}
//	return sum;
//}


int main() {
	cin >> tc;
	for (int i = 1; i <= tc; i++) {
		input();
		sol(0,0);
		cout << "#" << i << " " << Min << "\n";
	}
	return 0;
}
