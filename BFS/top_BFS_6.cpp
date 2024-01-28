#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Node { int to, cnt; };
vector<int> v[11];
int visited[15];
int BFS(int N, int M, int stNode, int stmin) {
	int cnt=0;
	queue<Node> q;
	q.push({stNode, 0});
	while (!q.empty()) {
		Node now = q.front(); q.pop();
		if (now.cnt > stmin)continue;
		visited[now.to] = 1;
		cnt++; // 여기해야 처음애거 들어감
		for (int i = 0; i < v[now.to].size(); i++) {
			int next = v[now.to][i];
			if (visited[next] == 1)continue;
			visited[next] = 1;
			q.push({ next,now.cnt+1 });
		}
	}
	return cnt;
}
int main() {
	int N, M; cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int from, to;
		cin >> from >> to;
		v[from].push_back(to);
		v[to].push_back(from);
	}
	int stNode, stmin; cin >> stNode >> stmin;
	int ans = BFS(N, M, stNode, stmin);
	cout << ans;
	return 0;
}
