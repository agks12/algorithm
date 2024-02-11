#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;

struct Pair { int bise, index; };
int n, k;
string a[2];
int visited[2][100001];
int dr[3] = { 0,0,1 };
int dc[3] = { 1,-1,k };

int bfs() {
	int nowindex = -1;
	queue<Pair> q;
	q.push({0,0});
	visited[0][0] = 1;
	while (!q.empty()) {
		Pair now = q.front(); q.pop();
		nowindex++;
		for (int i = 0; i < 3; i++) {
			int nextindex = 0;
			int nextbise = 0;
			if (i == 0) {
				nextindex = now.index + 1;
				nextbise = now.bise;
			}
			if (i == 1) {
				nextindex = now.index - 1;
				nextbise = now.bise;
			}
			if (i == 2) {
				nextindex = now.index + k;
				if (now.bise == 0)nextbise = 1;
				else nextbise = 0;
			}
			if (nextindex >= n) {
				return 1;
			}
			if (nextindex < nowindex)continue;
			if (visited[nextbise][nextindex] > 0)continue;
			if (a[nextbise][nextindex] == '0')continue;
			visited[nextbise][nextindex] = 1;
			q.push({ nextbise,nextindex });
		}
	}
	return 0;
}
int main() {
	cin >> n >> k;
	for (int i = 0; i < 2; i++) cin >> a[i];
	int ans = bfs();
	cout << ans;
	return 0;
}
