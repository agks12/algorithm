//prim
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct edg {
	int row, cost;
	bool operator<(edg right)const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		if (row > right.row)return true;
		if (row < right.row)return false;
		//if (col > right.col)return true;
		//if (col < right.col)return false;
		return false;
	}
};

struct Pair {
	int row, col;
};

int visited[2001];
Pair arr[2001];
vector<edg> v[2001];
priority_queue<edg> q;

int prim(int n,int k) {
	int sum = 0;
	int cnt = 0;
	q.push({ 0,0 });
	while (!q.empty()) {
		edg now = q.top(); q.pop();
		if (visited[now.row] == 1)continue;
		visited[now.row] = 1;
		sum += now.cost;
		cnt++;
		for (int i = 0; i < v[now.row].size(); i++) {
			edg next = v[now.row][i];
			if (next.cost < k)continue;
			q.push(next);
		}
	}
	//이거 끝나면 알아서 모든간선(n-1)연결되느듯 안될수도
	if (cnt == n)return sum;
	else return -1;
}

int main() {
	int n, K;
	cin >> n >> K;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		arr[i] = {a,b};
		if (i == 0)continue;
      	for (int k = 0; k <= i; k++) {
			int ans = ((arr[i].row - arr[k].row) * (arr[i].row - arr[k].row)) + ((arr[i].col - arr[k].col) * (arr[i].col - arr[k].col));
			if (ans < K)continue;
			v[i].push_back({ k,ans });
			v[k].push_back({ i,ans });
		}

	}
	int ans = prim(n,K);
	cout << ans;
	return 0;
}

//크루스칼
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct edg {
	int row,col, cost;
	bool operator<(edg right)const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		if (row > right.row)return true;
		if (row < right.row)return false;
		if (col > right.col)return true;
		if (col < right.col)return false;
		return false;
	}
};

struct Pair {
	int row, col;
};

int parent[2001];
int visited[2001];
Pair arr[2001];
//vector<edg> v[2001];
priority_queue<edg> q;

int Find(int num) {
	if (num == parent[num])return num;
	return Find(parent[num]);
}

int kuruskal(int n, int k) {
	int sum = 0;
	int cnt = 0;
	while (!q.empty()) {
		edg now = q.top(); q.pop();
		int rootA = Find(now.row);
		int rootB = Find(now.col);
		if (now.cost < k)continue;
		if (rootA == rootB)continue;
		parent[rootA] = rootB;
		sum += now.cost;
		cnt++;
	}
	if (cnt == n-1)return sum;//이건 n-1인데 왜 prim은 n하면 맞지?
	else return -1;
}

int main() {
	int n, K;
	cin >> n >> K;
	for (int i = 0; i <= n; i++)parent[i] = i;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		arr[i] = {a,b};
		if (i == 0)continue;
		for (int k = 0; k <= i; k++) {
			int ans = ((arr[i].row - arr[k].row) * (arr[i].row - arr[k].row)) + ((arr[i].col - arr[k].col) * (arr[i].col - arr[k].col));
			if (ans < K)continue;
			q.push({ i,k,ans });
		}
	}

	int ans = kuruskal(n,K);
	cout << ans;
	return 0;
}

//최적시간
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;

int N, K;

pair<int, int> arr[100001];
int stNode;

struct Node {
	int from;
	int to;
	int cost;

};

bool op(Node left,Node right) {
	if (left.cost < right.cost)return true;
	if (left.cost > right.cost)return false;
	return false;
}


vector<Node> v;
int parent[100001];
int visited[100001];

int Find(int num) {
	if (num == parent[num])return num;
	return parent[num] = Find(parent[num]);
}

void Union(int A, int B) {
	int rootA = Find(A);
	int rootB = Find(B);

	parent[rootA] = rootB;
}


int MST() {
	int sum = 0;
	int cnt = 0;

	for (int i = 0; i < v.size(); i++) {
		Node now = v[i];
		if (Find(now.from) == Find(now.to))continue;
		sum += now.cost;
		cnt++;
		Union(now.from, now.to);
	}

	if (cnt < N - 1)return -1;
	else return sum;

}

int main() {
	cin >> N >> K;

	for (int i = 0; i < N; i++) {
		parent[i + 1] = i + 1;
		cin >> arr[i].first >> arr[i].second;
		if (i > 0) {
			for (int j = 0; j < i; j++) {
				int Ydiff = arr[i].first - arr[j].first;
				int Xdiff = arr[i].second - arr[j].second;
				int dis = Ydiff * Ydiff + Xdiff * Xdiff;
				if (dis >= K) {
					v.push_back({ i,j,dis });
				}
			}
		}
	}

	sort(v.begin(), v.end(), op);

	int ans = MST();
	cout << ans;
}
