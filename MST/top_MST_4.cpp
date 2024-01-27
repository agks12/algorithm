#include<iostream>
#include<queue>
#include <cstring>
using namespace std;

struct Pair { int row, col; };
struct Thi { 
	Pair fir;
	Pair sec; 
	int cost;
	bool operator<(Thi right)const {
		if (cost > right.cost)return true;
		if (cost < right.cost)return false;
		//if (row > right.row)return true;
		//if (row < right.row)return false;
		//if (col > right.col)return true;
		//if (col < right.col)return false;
		return false;
	}
};
int x, y;
int stX, stY;
int dr[4] = { 1,-1,0,0 };
int dc[4] = { 0,0,1,-1 };
char arr[51][51];
int visited[51][51];
int visited3[51][51];
Pair arrA[51];
priority_queue<Thi> final;
int parent[2700];

int input() {
	for (int i = 0; i <= (50 * 50 + 50); i++)parent[i] = i;
	cin >> x >> y;
	int index = 0;
	for (int i = 0; i < y; i++) cin >> arr[i];
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			visited[i][j] = 0;
			if (arr[i][j] == 'S') {
				stX = i;
				stY = j;
			}
			if (arr[i][j] == 'A') {
				arrA[index] = { i, j };
				index++;
			}
		}
	}
	return index;
}

void solution(int stX, int stY) {
	queue<Pair> q;
	q.push({ stX, stY });
	visited[stX][stY] = 1;
	int nowVisited = 1;
	int sum = 0;
	while (!q.empty()){
		Pair now = q.front(); q.pop();
		if ((now.row != stX || now.col != stY) && (arr[now.row][now.col] == 'A' || arr[now.row][now.col] == 'S')) {
			sum = visited[now.row][now.col] - nowVisited;
			final.push({{stX, stY},{ now.row, now.col }, sum});
		}
		for (int i = 0; i < 4; i++) {
			int nextRow = now.row + dr[i];
			int nextCol = now.col + dc[i];
			if (nextRow < 0 || nextCol < 0 || nextRow >= x || nextCol >= y)continue;
			if (arr[nextRow][nextCol] == '#')continue;
			if (visited[nextRow][nextCol] >= 1)continue;
			visited[nextRow][nextCol] = visited[now.row][now.col] + 1;
			q.push({ nextRow,nextCol });
		}
	}
}

int Find(int num) {
	if (num == parent[num])return num;
	return parent[num] = Find(parent[num]);
}

int Kuskal() {
	int sum = 0;
	while (!final.empty()) {
		Thi now = final.top(); final.pop();
		Pair firstDir = now.fir;
		Pair secondDir = now.sec;
		int firNum = firstDir.row * 51 + firstDir.col;
		int secNum = secondDir.row * 51 + secondDir.col;
		int rootA = Find(firNum);
		int rootB = Find(secNum);
		if (rootA == rootB)continue;
		parent[rootA] = rootB;
		sum += now.cost;
	}
	return sum;
}

int main() {
	int tc; cin >> tc;
	for (int t = 1; t <= tc; t++) {
		int sum = 0;
		int index = input();
		solution(stX, stY);
		for (int i = 0; i < y; i++) memset(visited[i], 0, sizeof(int) * x);
		for (int i = 0; i < index; i++) {
			Pair now = arrA[i];
			solution(now.row, now.col);
			for (int i = 0; i < y; i++) memset(visited[i], 0, sizeof(int) * x);
			arrA[i] = {0, 0};
		}
		int ans = Kuskal();
		cout << ans<<'\n';
	}
	return 0;
}
