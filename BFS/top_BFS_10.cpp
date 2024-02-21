#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int st, tar;
int visited[100001];
int bfs() {
	queue<pair<int, int>> q;
	q.push({st, 0});
	while (!q.empty()) {
		pair<int,int> now = q.front(); q.pop();
		if (now.first == tar)return now.second;
		for (int i = 0; i < 3; i++) {
			int next = 0;
			if (i == 0)next = now.first - 1;
			if (i == 1)next = now.first + 1;
			if (i == 2)next = now.first*2;
			if (next < 0 || next>100000)continue;
			if (visited[next] == 1)continue;
			visited[next] = 1;
			q.push({ next,now.second + 1 });
		}
	}
}
int main() {
	cin >> st >> tar;
	cout << bfs();
	return 0;
}
