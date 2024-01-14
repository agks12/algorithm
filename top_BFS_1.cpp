#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int arr[11][11];
int visited[11] ;
vector<int> v[11];
queue<int> q;

void bfs(int n) {
	q.push(0);

	while (!q.empty()) {
		int nowNode = q.front(); q.pop();
		cout << nowNode << " ";
		for (int i = 0; i < v[nowNode].size(); i++) {
			int nextNode = v[nowNode][i];
			if (visited[nextNode] == 1)continue;
			visited[nextNode] = 1;
			q.push(nextNode);
		}
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int to;
			cin >> to;
			if (to == 0)continue;
			v[i].push_back(j);
		}
	}

	visited[0] = 1;
	bfs(n);

	return 0;
}
