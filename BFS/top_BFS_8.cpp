#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct Pair{ int index, level; };
int visited[100001];
int st,en;
int bfs() {
	int next = 0;
	queue<Pair> q;
	visited[st] = 1;
	q.push({st, 0});
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		if (now.index == en)return now.level;
		for (int i = 0; i < 4; i++) {
			if (i == 0) next = now.index * 2;
			if (i == 1) next = now.index / 2;
			if (i == 2) next = now.index + 1;
			if (i == 3) next = now.index - 1;
			if (next < 0 || next>100000)continue;
			if (visited[next] > 0)continue;
			visited[next] = 1;
			q.push({ next,now.level+1});
		}
	}
}
int main() {
	cin >> st >> en;
	int ans = bfs();
	cout << ans;
	return 0;
}
